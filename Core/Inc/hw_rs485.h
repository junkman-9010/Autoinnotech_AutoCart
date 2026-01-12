
/**
 * @file    hw_rs485.h
 * @brief   RS485 통신 제어 (TX/RX 전환 핀 관리 포함)
 * @author  SUNG
 * @date    Jan 11, 2026
 */

#ifndef INC_HW_RS485_H_
#define INC_HW_RS485_H_

#include "main.h"

/**
 * @struct RS485_Config_t
 * @brief RS485 포트별 설정을 담는 구조체 (범용성 확보)
 */
typedef struct {
    UART_HandleTypeDef *huart;    // 연결된 UART 핸들러 (예: &huart3)
    GPIO_TypeDef *DE_Port;        // DE/RE 제어 포트 (예: GPIOD)
    uint16_t DE_Pin;              // DE/RE 제어 핀 (예: GPIO_PIN_10)
} RS485_Config_t;

/* RS485 인스턴스 설정: 핸들과 핀 정보를 매핑합니다. */
void HW_RS485_Init_Config(RS485_Config_t *config, UART_HandleTypeDef *huart, GPIO_TypeDef *port, uint16_t pin);

/* 데이터 송신: 송신 모드 전환 -> 데이터 전송 -> TC 대기 -> 수신 모드 복귀를 한 번에 처리 */
HAL_StatusTypeDef HW_RS485_Transmit(RS485_Config_t *config, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/* 모드 수동 전환이 필요할 경우를 위한 함수 */
void HW_RS485_Set_RxMode(RS485_Config_t *config);
void HW_RS485_Set_TxMode(RS485_Config_t *config);

#endif /* INC_HW_RS485_H_ */

/**
 * @file    hw_rs485.h
 * @brief   RS485 통신 제어 (TX/RX 전환 핀 관리 포함)
 * @author  SUNG
 * @date    Jan 11, 2026
 */

#ifndef INC_HW_RS485_H_
#define INC_HW_RS485_H_

#include "main.h"

/**
 * @struct RS485_Config_t
 * @brief RS485 포트별 설정을 담는 구조체 (범용성 확보)
 */
typedef struct {
    UART_HandleTypeDef *huart;    // 연결된 UART 핸들러 (예: &huart3)
    GPIO_TypeDef *DE_Port;        // DE/RE 제어 포트 (예: GPIOD)
    uint16_t DE_Pin;              // DE/RE 제어 핀 (예: GPIO_PIN_10)
} RS485_Config_t;

/* RS485 인스턴스 설정: 핸들과 핀 정보를 매핑합니다. */
void HW_RS485_Init_Config(RS485_Config_t *config, UART_HandleTypeDef *huart, GPIO_TypeDef *port, uint16_t pin);

/* 데이터 송신: 송신 모드 전환 -> 데이터 전송 -> TC 대기 -> 수신 모드 복귀를 한 번에 처리 */
HAL_StatusTypeDef HW_RS485_Transmit(RS485_Config_t *config, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/* 모드 수동 전환이 필요할 경우를 위한 함수 */
void HW_RS485_Set_RxMode(RS485_Config_t *config);
void HW_RS485_Set_TxMode(RS485_Config_t *config);

#endif /* INC_HW_RS485_H_ */

