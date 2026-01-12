
/**
 * @file    modbus-rtu.c
 * @brief   Modbus RTU Master/Slave logic implementation
 */

#include "modbus-rtu.h"
#include <string.h>

/* CRC-16 (Modbus) 계산 */
uint16_t modbus_rtu_CRC16(uint8_t *pBuffer, uint16_t len) {
    uint16_t crc = 0xFFFF;
    for (uint16_t pos = 0; pos < len; pos++) {
        crc ^= (uint16_t)pBuffer[pos];
        for (int i = 8; i != 0; i--) {
            if ((crc & 0x0001) != 0) { crc >>= 1; crc ^= 0xA001; }
            else { crc >>= 1; }
        }
    }
    return crc;
}

/* 데이터 레지스터 접근 내부 함수 */
static HAL_StatusTypeDef modbus_rtu_Get_Data(Modbus_rtu_RegisterRange_t *ranges, uint8_t count, uint16_t addr, uint16_t *val) {
    for (uint8_t i = 0; i < count; i++) {
        if (addr >= ranges[i].StartAddr && addr <= ranges[i].EndAddr) {
            *val = ranges[i].pData[addr - ranges[i].StartAddr];
            return HAL_OK;
        }
    }
    return HAL_ERROR;
}

static HAL_StatusTypeDef modbus_rtu_Set_Data(Modbus_rtu_RegisterRange_t *ranges, uint8_t count, uint16_t addr, uint16_t val) {
    for (uint8_t i = 0; i < count; i++) {
        if (addr >= ranges[i].StartAddr && addr <= ranges[i].EndAddr) {
            ranges[i].pData[addr - ranges[i].StartAddr] = val;
            return HAL_OK;
        }
    }
    return HAL_ERROR;
}

/* [Master] 요청 패킷 전송 */
HAL_StatusTypeDef modbus_rtu_Master_Send(RS485_Config_t *config, Modbus_rtu_Packet_t *pkt) {
    uint8_t frame[256];
    uint16_t idx = 0;
    frame[idx++] = pkt->Address;
    frame[idx++] = pkt->FunctionCode;
    memcpy(&frame[idx], pkt->Data, pkt->DataLen);
    idx += pkt->DataLen;
    uint16_t crc = modbus_rtu_CRC16(frame, idx);
    frame[idx++] = (uint8_t)(crc & 0xFF);
    frame[idx++] = (uint8_t)((crc >> 8) & 0xFF);
    return HW_RS485_Transmit(config, frame, idx, 100);
}

/* [Slave] 수신 패킷 파싱 및 검증 */
uint8_t modbus_rtu_Slave_Parse(uint8_t *pBuffer, uint16_t Len, Modbus_rtu_Packet_t *outPkt) {
    if (Len < 4) return 0;
    uint16_t rec_crc = (pBuffer[Len - 1] << 8) | pBuffer[Len - 2];
    if (rec_crc != modbus_rtu_CRC16(pBuffer, Len - 2)) return 0;
    outPkt->Address = pBuffer[0];
    outPkt->FunctionCode = pBuffer[1];
    outPkt->DataLen = Len - 4;
    memcpy(outPkt->Data, &pBuffer[2], outPkt->DataLen);
    return 1;
}

/* [Slave] 전체 Function Code 응답 처리 */
void modbus_rtu_Slave_Process(RS485_Config_t *config, Modbus_rtu_Packet_t *rxPkt, Modbus_rtu_RegisterRange_t *ranges, uint8_t rangeCount) {
    uint8_t resFrame[256];
    uint16_t resLen = 0;
    uint16_t startAddr = (rxPkt->Data[0] << 8) | rxPkt->Data[1];
    uint16_t quantity = (rxPkt->Data[2] << 8) | rxPkt->Data[3];

    resFrame[resLen++] = rxPkt->Address;
    resFrame[resLen++] = rxPkt->FunctionCode;

    switch (rxPkt->FunctionCode) {
        case MODBUS_RTU_FC_READ_COILS:
        case MODBUS_RTU_FC_READ_DISCRETE_INPUTS: {
            uint8_t byteCount = (quantity + 7) / 8;
            resFrame[resLen++] = byteCount;
            memset(&resFrame[resLen], 0, byteCount);
            for (uint16_t i = 0; i < quantity; i++) {
                uint16_t val = 0;
                if (modbus_rtu_Get_Data(ranges, rangeCount, startAddr + i, &val) == HAL_OK && val)
                    resFrame[resLen + (i / 8)] |= (1 << (i % 8));
            }
            resLen += byteCount; break;
        }
        case MODBUS_RTU_FC_READ_HOLDING_REGISTERS:
        case MODBUS_RTU_FC_READ_INPUT_REGISTERS: {
            resFrame[resLen++] = (uint8_t)(quantity * 2);
            for (uint16_t i = 0; i < quantity; i++) {
                uint16_t val = 0; modbus_rtu_Get_Data(ranges, rangeCount, startAddr + i, &val);
                resFrame[resLen++] = (uint8_t)(val >> 8); resFrame[resLen++] = (uint8_t)(val & 0xFF);
            }
            break;
        }
        case MODBUS_RTU_FC_WRITE_SINGLE_COIL:
        case MODBUS_RTU_FC_WRITE_SINGLE_REGISTER: {
            uint16_t val = (rxPkt->FunctionCode == MODBUS_RTU_FC_WRITE_SINGLE_COIL) ?
                           ((rxPkt->Data[2] == 0xFF) ? 1 : 0) : ((rxPkt->Data[2] << 8) | rxPkt->Data[3]);
            modbus_rtu_Set_Data(ranges, rangeCount, startAddr, val);
            memcpy(&resFrame[resLen], rxPkt->Data, 4); resLen += 4; break;
        }
        case MODBUS_RTU_FC_WRITE_MULTIPLE_COILS: {
            for (uint16_t i = 0; i < quantity; i++) {
                uint16_t val = (rxPkt->Data[5 + (i / 8)] >> (i % 8)) & 0x01;
                modbus_rtu_Set_Data(ranges, rangeCount, startAddr + i, val);
            }
            memcpy(&resFrame[resLen], rxPkt->Data, 4); resLen += 4; break;
        }
        case MODBUS_RTU_FC_WRITE_MULTIPLE_REGISTERS: {
            for (uint16_t i = 0; i < quantity; i++) {
                uint16_t val = (rxPkt->Data[5 + i * 2] << 8) | rxPkt->Data[6 + i * 2];
                modbus_rtu_Set_Data(ranges, rangeCount, startAddr + i, val);
            }
            memcpy(&resFrame[resLen], rxPkt->Data, 4); resLen += 4; break;
        }
        default:
            resLen = 0; resFrame[resLen++] = rxPkt->Address;
            resFrame[resLen++] = rxPkt->FunctionCode | 0x80;
            resFrame[resLen++] = MODBUS_RTU_EX_ILLEGAL_FUNCTION; break;
    }

    uint16_t crc = modbus_rtu_CRC16(resFrame, resLen);
    resFrame[resLen++] = (uint8_t)(crc & 0xFF);
    resFrame[resLen++] = (uint8_t)((crc >> 8) & 0xFF);
    HW_RS485_Transmit(config, resFrame, resLen, 100);
}
