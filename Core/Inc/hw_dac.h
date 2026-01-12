
/**
 * @file hw_dac.h
 * @brief DAC peripheral hardware abstraction layer header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_DAC_H
#define __HW_DAC_H

#include "main.h"

/* 전역 변수 핸들 선언 (외부 모듈 참조용) */
extern DAC_HandleTypeDef hdac;

/**
 * @brief DAC 인터페이스 초기화
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_DAC_Init(void);

/**
 * @brief DAC 채널 전압 출력 설정 (12-bit Right Aligned)
 * @param channel DAC_CHANNEL_1 또는 DAC_CHANNEL_2
 * @param value 출력값 (0 ~ 4095)
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_DAC_SetValue(uint32_t channel, uint32_t value);

/**
 * @brief DAC 출력을 시작합니다.
 * @param channel DAC_CHANNEL_1 또는 DAC_CHANNEL_2
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_DAC_Start(uint32_t channel);

#endif /* __HW_DAC_H */

/**
 * @file hw_dac.h
 * @brief DAC peripheral hardware abstraction layer header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_DAC_H
#define __HW_DAC_H

#include "main.h"

/* 전역 변수 핸들 선언 (외부 모듈 참조용) */
extern DAC_HandleTypeDef hdac;

/**
 * @brief DAC 인터페이스 초기화
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_DAC_Init(void);

/**
 * @brief DAC 채널 전압 출력 설정 (12-bit Right Aligned)
 * @param channel DAC_CHANNEL_1 또는 DAC_CHANNEL_2
 * @param value 출력값 (0 ~ 4095)
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_DAC_SetValue(uint32_t channel, uint32_t value);

/**
 * @brief DAC 출력을 시작합니다.
 * @param channel DAC_CHANNEL_1 또는 DAC_CHANNEL_2
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_DAC_Start(uint32_t channel);

#endif /* __HW_DAC_H */

