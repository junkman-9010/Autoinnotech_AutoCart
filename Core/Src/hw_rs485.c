
/**
 * @file    hw_rs485.c
 * @brief   RS485 통신 제어 로직 구현
 * @author  SUNG
 */

#include "hw_rs485.h"

/**
 * @brief RS485 구성 정보를 초기화하고 핀을 수신 모드로 둡니다.
 */
void HW_RS485_Init_Config(RS485_Config_t *config, UART_HandleTypeDef *huart, GPIO_TypeDef *port, uint16_t pin)
{
    config->huart = huart;
    config->DE_Port = port;
    config->DE_Pin = pin;

    // 초기 상태는 항상 수신 모드(Low)
    HW_RS485_Set_RxMode(config);
}

/**
 * @brief 송신 모드로 전환합니다.
 */
void HW_RS485_Set_TxMode(RS485_Config_t *config)
{
    HAL_GPIO_WritePin(config->DE_Port, config->DE_Pin, GPIO_PIN_SET);
}

/**
 * @brief 수신 모드로 전환합니다.
 */
void HW_RS485_Set_RxMode(RS485_Config_t *config)
{
    HAL_GPIO_WritePin(config->DE_Port, config->DE_Pin, GPIO_PIN_RESET);
}

/**
 * @brief 범용 RS485 송신 함수
 */
HAL_StatusTypeDef HW_RS485_Transmit(RS485_Config_t *config, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    HAL_StatusTypeDef status;

    if (config == NULL || config->huart == NULL) return HAL_ERROR;

    // 1. 송신 모드 전환
    HW_RS485_Set_TxMode(config);

    // 2. 데이터 송신
    status = HAL_UART_Transmit(config->huart, pData, Size, Timeout);

    // 3. 하드웨어 전송 완료(TC) 대기 (데이터 잘림 방지 필수!)
    while(__HAL_UART_GET_FLAG(config->huart, UART_FLAG_TC) == RESET);

    // 4. 수신 모드로 즉시 복구
    HW_RS485_Set_RxMode(config);

    return status;
}
