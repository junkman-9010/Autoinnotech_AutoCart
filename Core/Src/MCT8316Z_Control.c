#include "MCT8316Z_Control.h"

/**
 * @brief MCT8316Z PWM 제어 초기화
 */
void MCT8316_PWM_Init(MCT8316_PWM_t *dev, TIM_HandleTypeDef *htim, uint32_t channel) {
    dev->htim = htim;
    dev->channel = channel;
    dev->speed = 0;

    // Timer1 PWM 시작
    HAL_TIM_PWM_Start(dev->htim, dev->channel);
}

/**
 * @brief 모터 속도 설정 (PWM Duty 제어)
 * @param duty 0 ~ 1000 (0% ~ 100%)
 */
void MCT8316_PWM_SetSpeed(MCT8316_PWM_t *dev, uint16_t duty) {
    if (duty > MCT8316Z_PWM_MAX_DUTY) duty = MCT8316Z_PWM_MAX_DUTY;

    dev->speed = duty;

    // Timer1의 CCR 레지스터에 값 반영 (속도 변경)
    __HAL_TIM_SET_COMPARE(dev->htim, dev->channel, duty);
}

/**
 * @brief 모터 정지
 */
void MCT8316_PWM_Stop(MCT8316_PWM_t *dev) {
    MCT8316_PWM_SetSpeed(dev, 0);
}
