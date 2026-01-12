
/**
 * @file    modbus-rtu.h
 * @brief   Modbus RTU Master/Slave Dual Library
 * @author  SUNG
 * @date    2026-01-11
 */

#ifndef INC_MODBUS_RTU_H_
#define INC_MODBUS_RTU_H_

#include "hw_rs485.h"

/* Modbus Standard Function Codes */
#define MODBUS_RTU_FC_READ_COILS                0x01
#define MODBUS_RTU_FC_READ_DISCRETE_INPUTS      0x02
#define MODBUS_RTU_FC_READ_HOLDING_REGISTERS    0x03
#define MODBUS_RTU_FC_READ_INPUT_REGISTERS      0x04
#define MODBUS_RTU_FC_WRITE_SINGLE_COIL         0x05
#define MODBUS_RTU_FC_WRITE_SINGLE_REGISTER     0x06
#define MODBUS_RTU_FC_WRITE_MULTIPLE_COILS      0x0F
#define MODBUS_RTU_FC_WRITE_MULTIPLE_REGISTERS  0x10

/* Modbus Exception Codes */
#define MODBUS_RTU_EX_ILLEGAL_FUNCTION          0x01
#define MODBUS_RTU_EX_ILLEGAL_DATA_ADDRESS      0x02

/**
 * @struct Modbus_rtu_Packet_t
 * @brief Modbus 패킷 데이터 구조체
 */
typedef struct {
    uint8_t  Address;
    uint8_t  FunctionCode;
    uint8_t  Data[252];
    uint16_t DataLen;
} Modbus_rtu_Packet_t;

/**
 * @struct Modbus_rtu_RegisterRange_t
 * @brief 슬레이브의 특정 주소 영역 관리 구조체
 */
typedef struct {
    uint16_t StartAddr;
    uint16_t EndAddr;
    uint16_t *pData;
} Modbus_rtu_RegisterRange_t;

/* 공통 함수 */
uint16_t modbus_rtu_CRC16(uint8_t *pBuffer, uint16_t len);

/* Master 함수 */
HAL_StatusTypeDef modbus_rtu_Master_Send(RS485_Config_t *config, Modbus_rtu_Packet_t *pkt);

/* Slave 함수 */
uint8_t modbus_rtu_Slave_Parse(uint8_t *pBuffer, uint16_t Len, Modbus_rtu_Packet_t *outPkt);
void modbus_rtu_Slave_Process(RS485_Config_t *config, Modbus_rtu_Packet_t *rxPkt, Modbus_rtu_RegisterRange_t *ranges, uint8_t rangeCount);

#endif /* INC_MODBUS_RTU_H_ */

/**
 * @file    modbus-rtu.h
 * @brief   Modbus RTU Master/Slave Dual Library
 * @author  SUNG
 * @date    2026-01-11
 */

#ifndef INC_MODBUS_RTU_H_
#define INC_MODBUS_RTU_H_

#include "hw_rs485.h"

/* Modbus Standard Function Codes */
#define MODBUS_RTU_FC_READ_COILS                0x01
#define MODBUS_RTU_FC_READ_DISCRETE_INPUTS      0x02
#define MODBUS_RTU_FC_READ_HOLDING_REGISTERS    0x03
#define MODBUS_RTU_FC_READ_INPUT_REGISTERS      0x04
#define MODBUS_RTU_FC_WRITE_SINGLE_COIL         0x05
#define MODBUS_RTU_FC_WRITE_SINGLE_REGISTER     0x06
#define MODBUS_RTU_FC_WRITE_MULTIPLE_COILS      0x0F
#define MODBUS_RTU_FC_WRITE_MULTIPLE_REGISTERS  0x10

/* Modbus Exception Codes */
#define MODBUS_RTU_EX_ILLEGAL_FUNCTION          0x01
#define MODBUS_RTU_EX_ILLEGAL_DATA_ADDRESS      0x02

/**
 * @struct Modbus_rtu_Packet_t
 * @brief Modbus 패킷 데이터 구조체
 */
typedef struct {
    uint8_t  Address;
    uint8_t  FunctionCode;
    uint8_t  Data[252];
    uint16_t DataLen;
} Modbus_rtu_Packet_t;

/**
 * @struct Modbus_rtu_RegisterRange_t
 * @brief 슬레이브의 특정 주소 영역 관리 구조체
 */
typedef struct {
    uint16_t StartAddr;
    uint16_t EndAddr;
    uint16_t *pData;
} Modbus_rtu_RegisterRange_t;

/* 공통 함수 */
uint16_t modbus_rtu_CRC16(uint8_t *pBuffer, uint16_t len);

/* Master 함수 */
HAL_StatusTypeDef modbus_rtu_Master_Send(RS485_Config_t *config, Modbus_rtu_Packet_t *pkt);

/* Slave 함수 */
uint8_t modbus_rtu_Slave_Parse(uint8_t *pBuffer, uint16_t Len, Modbus_rtu_Packet_t *outPkt);
void modbus_rtu_Slave_Process(RS485_Config_t *config, Modbus_rtu_Packet_t *rxPkt, Modbus_rtu_RegisterRange_t *ranges, uint8_t rangeCount);

#endif /* INC_MODBUS_RTU_H_ */

