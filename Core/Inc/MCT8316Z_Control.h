#ifndef __MCT8316Z_CONTROL_H
#define __MCT8316Z_CONTROL_H

#include "main.h"

// Timer1 설정에 따른 최대 Duty 값 (Period 설정값)
#define MCT8316Z_PWM_MAX_DUTY   1000

typedef struct {
    TIM_HandleTypeDef *htim; // Timer1 핸들
    uint32_t channel;        // PWM 채널 (예: TIM_CHANNEL_1)
    uint16_t speed;          // 현재 설정된 속도 (0~1000)
} MCT8316_PWM_t;

// 함수 프로토타입
void MCT8316_PWM_Init(MCT8316_PWM_t *dev, TIM_HandleTypeDef *htim, uint32_t channel);
void MCT8316_PWM_SetSpeed(MCT8316_PWM_t *dev, uint16_t duty);
void MCT8316_PWM_Stop(MCT8316_PWM_t *dev);

#endif
