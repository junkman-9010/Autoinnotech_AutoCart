
/**
 * @file hw_gpio.h
 * @brief GPIO peripheral hardware abstraction layer header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_GPIO_H
#define __HW_GPIO_H

#include "main.h"

/* --- LED 제어 편의 기능 --- */
#define LED1_ON()      HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_RESET)
#define LED1_OFF()     HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_SET)
#define LED1_TOGGLE()  HAL_GPIO_TogglePin(GPIOB, LED1_Pin)

#define LED2_ON()      HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PIN_RESET)
#define LED2_OFF()     HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PIN_SET)
#define LED2_TOGGLE()  HAL_GPIO_TogglePin(GPIOB, LED2_Pin)

/* --- Buzzer 제어 --- */
#define BUZZER_ON()    HAL_GPIO_WritePin(GPIOC, BUZZ_Pin, GPIO_PIN_SET)
#define BUZZER_OFF()   HAL_GPIO_WritePin(GPIOC, BUZZ_Pin, GPIO_PIN_RESET)

/**
 * @brief GPIO 모든 포트 및 핀 초기화
 * @retval None
 */
void HW_GPIO_Init(void);

/**
 * @brief 특정 LED의 상태를 설정 (1: On, 0: Off)
 * @param led_num LED 번호 (1~4)
 * @param state 상태
 */
void HW_GPIO_SetLED(uint8_t led_num, uint8_t state);

#endif /* __HW_GPIO_H */

/**
 * @file hw_gpio.h
 * @brief GPIO peripheral hardware abstraction layer header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_GPIO_H
#define __HW_GPIO_H

#include "main.h"

/* --- LED 제어 편의 기능 --- */
#define LED1_ON()      HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_RESET)
#define LED1_OFF()     HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_SET)
#define LED1_TOGGLE()  HAL_GPIO_TogglePin(GPIOB, LED1_Pin)

#define LED2_ON()      HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PIN_RESET)
#define LED2_OFF()     HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PIN_SET)
#define LED2_TOGGLE()  HAL_GPIO_TogglePin(GPIOB, LED2_Pin)

/* --- Buzzer 제어 --- */
#define BUZZER_ON()    HAL_GPIO_WritePin(GPIOC, BUZZ_Pin, GPIO_PIN_SET)
#define BUZZER_OFF()   HAL_GPIO_WritePin(GPIOC, BUZZ_Pin, GPIO_PIN_RESET)

/**
 * @brief GPIO 모든 포트 및 핀 초기화
 * @retval None
 */
void HW_GPIO_Init(void);

/**
 * @brief 특정 LED의 상태를 설정 (1: On, 0: Off)
 * @param led_num LED 번호 (1~4)
 * @param state 상태
 */
void HW_GPIO_SetLED(uint8_t led_num, uint8_t state);

#endif /* __HW_GPIO_H */

