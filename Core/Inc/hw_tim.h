
/**
 * @file hw_tim.h
 * @brief Timer peripheral hardware abstraction layer header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_TIM_H
#define __HW_TIM_H

#include "main.h"

/* 전역 변수 핸들 선언 */
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;

// extern을 붙여서 '실체는 다른 곳에 있다'고 알립니다.
extern volatile uint8_t timer_100ms_flag;


/* 초기화 함수 프로토타입 */
void HW_TIM1_Init(void);
void HW_TIM2_Init(void);
//void HW_TIM3_Init(void);
void HW_TIM4_Init(void);
void HW_TIM8_Init(void);

/* 제어 함수 프로토타입 */
HAL_StatusTypeDef HW_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t channel);
void HW_TIM_SetPWM_Duty(TIM_HandleTypeDef *htim, uint32_t channel, uint32_t pulse);
HAL_StatusTypeDef HW_TIM_IC_Start(TIM_HandleTypeDef *htim, uint32_t channel);

#endif /* __HW_TIM_H */
