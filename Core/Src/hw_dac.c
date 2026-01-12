
/**
 * @file hw_dac.c
 * @brief Implementation of DAC communication functions.
 * @author SUNG
 * @date 2026-01-11
 * @details This file handles initialization and output control for DAC1/2.
 */

#include "hw_dac.h"

/* 전역 변수 핸들 정의 */
DAC_HandleTypeDef hdac;

/**
 * @brief DAC Initialization Function
 * @details main.c의 설정을 기반으로 2개 채널을 초기화합니다.
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_DAC_Init(void)
{
  DAC_ChannelConfTypeDef sConfig = {0};

  /** DAC Initialization
   */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /** DAC channel OUT1 config
   */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /** DAC channel OUT2 config
   */
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* 초기화 완료 후 채널 활성화 (필요에 따라 Start 함수를 별도로 호출 가능) */
  HW_DAC_Start(DAC_CHANNEL_1);
  HW_DAC_Start(DAC_CHANNEL_2);

  return HAL_OK;
}

/**
 * @brief DAC 채널에 특정 디지털 값을 입력하여 아날로그 전압을 출력합니다.
 * @param channel DAC_CHANNEL_1 또는 DAC_CHANNEL_2
 * @param value 12비트 해상도 (0 ~ 4095)
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_DAC_SetValue(uint32_t channel, uint32_t value)
{
  /* 입력값이 12비트 범위를 초과하지 않도록 제한 */
  if (value > 4095) value = 4095;

  /* 12-bit Right Aligned 방식으로 설정 값 전송 */
  if (HAL_DAC_SetValue(&hdac, channel, DAC_ALIGN_12B_R, value) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
 * @brief 특정 DAC 채널의 출력을 활성화합니다.
 * @param channel DAC_CHANNEL_1 또는 DAC_CHANNEL_2
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_DAC_Start(uint32_t channel)
{
  return HAL_DAC_Start(&hdac, channel);
}
