/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GY_NRTST_Pin GPIO_PIN_2
#define GY_NRTST_GPIO_Port GPIOE
#define GY_INT_Pin GPIO_PIN_3
#define GY_INT_GPIO_Port GPIOE
#define SW1_Pin GPIO_PIN_4
#define SW1_GPIO_Port GPIOE
#define SW2_Pin GPIO_PIN_5
#define SW2_GPIO_Port GPIOE
#define SW3_Pin GPIO_PIN_6
#define SW3_GPIO_Port GPIOE
#define OUT1_Pin GPIO_PIN_0
#define OUT1_GPIO_Port GPIOC
#define OUT2_Pin GPIO_PIN_1
#define OUT2_GPIO_Port GPIOC
#define OUT3_Pin GPIO_PIN_2
#define OUT3_GPIO_Port GPIOC
#define OUT4_Pin GPIO_PIN_3
#define OUT4_GPIO_Port GPIOC
#define IN1_Pin GPIO_PIN_1
#define IN1_GPIO_Port GPIOA
#define IN2_Pin GPIO_PIN_2
#define IN2_GPIO_Port GPIOA
#define IN3_Pin GPIO_PIN_3
#define IN3_GPIO_Port GPIOA
#define M1_MOTOR_PW_Pin GPIO_PIN_4
#define M1_MOTOR_PW_GPIO_Port GPIOA
#define M2_MOTOR_PW_Pin GPIO_PIN_5
#define M2_MOTOR_PW_GPIO_Port GPIOA
#define IN4_Pin GPIO_PIN_6
#define IN4_GPIO_Port GPIOA
#define LED3_Pin GPIO_PIN_7
#define LED3_GPIO_Port GPIOA
#define SPI2_INT_Pin GPIO_PIN_4
#define SPI2_INT_GPIO_Port GPIOC
#define BUZZ_Pin GPIO_PIN_5
#define BUZZ_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_1
#define LED2_GPIO_Port GPIOB
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define RF_TRIG_Pin GPIO_PIN_7
#define RF_TRIG_GPIO_Port GPIOE
#define RF_D1_Pin GPIO_PIN_8
#define RF_D1_GPIO_Port GPIOE
#define RF_D2_Pin GPIO_PIN_9
#define RF_D2_GPIO_Port GPIOE
#define RF_D3_Pin GPIO_PIN_10
#define RF_D3_GPIO_Port GPIOE
#define RF_D4_Pin GPIO_PIN_11
#define RF_D4_GPIO_Port GPIOE
#define M2_SLEEP_Pin GPIO_PIN_12
#define M2_SLEEP_GPIO_Port GPIOE
#define M1_SLEEP_Pin GPIO_PIN_13
#define M1_SLEEP_GPIO_Port GPIOE
#define M2_DRVOFF_Pin GPIO_PIN_14
#define M2_DRVOFF_GPIO_Port GPIOE
#define M1_DRVOFF_Pin GPIO_PIN_15
#define M1_DRVOFF_GPIO_Port GPIOE
#define DE3_Pin GPIO_PIN_10
#define DE3_GPIO_Port GPIOD
#define M2_FAULT_Pin GPIO_PIN_11
#define M2_FAULT_GPIO_Port GPIOD
#define M2_FGOUT_Pin GPIO_PIN_12
#define M2_FGOUT_GPIO_Port GPIOD
#define M2_DIR_Pin GPIO_PIN_14
#define M2_DIR_GPIO_Port GPIOD
#define M2_BREAK_Pin GPIO_PIN_15
#define M2_BREAK_GPIO_Port GPIOD
#define M1_FGOUT_Pin GPIO_PIN_6
#define M1_FGOUT_GPIO_Port GPIOC
#define M1_DIR_Pin GPIO_PIN_8
#define M1_DIR_GPIO_Port GPIOC
#define M1_BREAK_Pin GPIO_PIN_9
#define M1_BREAK_GPIO_Port GPIOC
#define M1_FAULT_Pin GPIO_PIN_3
#define M1_FAULT_GPIO_Port GPIOD
#define PWRKEY_Pin GPIO_PIN_4
#define PWRKEY_GPIO_Port GPIOD
#define DE2_Pin GPIO_PIN_7
#define DE2_GPIO_Port GPIOD
#define LTE_SLEEP_Pin GPIO_PIN_5
#define LTE_SLEEP_GPIO_Port GPIOB
#define TOF_SHUT2_Pin GPIO_PIN_8
#define TOF_SHUT2_GPIO_Port GPIOB
#define TOF_SHUT1_Pin GPIO_PIN_9
#define TOF_SHUT1_GPIO_Port GPIOB
#define LED4_Pin GPIO_PIN_0
#define LED4_GPIO_Port GPIOE
#define TOF_INT_Pin GPIO_PIN_1
#define TOF_INT_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
