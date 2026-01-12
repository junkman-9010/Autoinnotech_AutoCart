
/**
 * @file hw_rtc.c
 * @brief Implementation of RTC functions for time and date management.
 * @author SUNG
 * @date 2026-01-11
 */

#include "hw_rtc.h"

/* 전역 변수 핸들 정의 */
RTC_HandleTypeDef hrtc;

/**
 * @brief RTC Initialization Function
 * @details RTC 장치를 초기화하고 시간 포맷을 24시간제로 설정합니다.
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_RTC_Init(void)
{
  /** Initialize RTC Only
   */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;

  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* * 참고: RTC 날짜/시간 초기 설정이 필요한 경우
   * 아래 HW_RTC_SetDateTime 함수를 호출하여 초기값을 기입할 수 있습니다.
   */

  return HAL_OK;
}

/**
 * @brief RTC 시간 및 날짜 설정 함수
 * @details BCD 포맷이 아닌 Binary 포맷(RTC_FORMAT_BIN)을 사용하여 설정을 간소화했습니다.
 */
HAL_StatusTypeDef HW_RTC_SetDateTime(RTC_TimeTypeDef *sTime, RTC_DateTypeDef *sDate)
{
  if (HAL_RTC_SetTime(&hrtc, sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (HAL_RTC_SetDate(&hrtc, sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
 * @brief 현재 시간과 날짜를 읽어오는 함수
 * @note 중요: HAL 라이브러리 특성상 시간(Time)을 읽은 후 반드시 날짜(Date)를 읽어야
 * Shadow 레지스터의 락(Lock)이 해제되어 다음 읽기가 정상적으로 수행됩니다.
 */
HAL_StatusTypeDef HW_RTC_GetDateTime(RTC_TimeTypeDef *sTime, RTC_DateTypeDef *sDate)
{
  if (HAL_RTC_GetTime(&hrtc, sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (HAL_RTC_GetDate(&hrtc, sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
