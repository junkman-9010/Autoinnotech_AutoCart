
/**
 * @file hw_uart.h
 * @brief UART peripheral hardware abstraction layer header (5 Channels).
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_UART_H
#define __HW_UART_H

#include "main.h"

/* 전역 변수 핸들 선언 */
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;

/* 초기화 함수 프로토타입 */
void HW_USART1_UART_Init(void);
void HW_USART2_UART_Init(void);
void HW_USART3_UART_Init(void);
void HW_UART4_Init(void);
void HW_UART5_Init(void);

/* 제어 함수 프로토타입 */
HAL_StatusTypeDef HW_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t len);
HAL_StatusTypeDef HW_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t len);

#endif /* __HW_UART_H */

/**
 * @file hw_uart.h
 * @brief UART peripheral hardware abstraction layer header (5 Channels).
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_UART_H
#define __HW_UART_H

#include "main.h"

/* 전역 변수 핸들 선언 */
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;

/* 초기화 함수 프로토타입 */
void HW_USART1_UART_Init(void);
void HW_USART2_UART_Init(void);
void HW_USART3_UART_Init(void);
void HW_UART4_Init(void);
void HW_UART5_Init(void);

/* 제어 함수 프로토타입 */
HAL_StatusTypeDef HW_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t len);
HAL_StatusTypeDef HW_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t len);

#endif /* __HW_UART_H */

