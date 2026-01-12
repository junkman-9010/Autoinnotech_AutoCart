
/**
 * @file hw_rtc.h
 * @brief RTC peripheral hardware abstraction layer header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_RTC_H
#define __HW_RTC_H

#include "main.h"

/* 전역 변수 핸들 선언 */
extern RTC_HandleTypeDef hrtc;

/**
 * @brief RTC 인터페이스 초기화
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_RTC_Init(void);

/**
 * @brief RTC 시간 및 날짜 설정
 * @param sTime 시간 구조체 포인터 (Hours, Minutes, Seconds)
 * @param sDate 날짜 구조체 포인터 (Year, Month, Date, WeekDay)
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_RTC_SetDateTime(RTC_TimeTypeDef *sTime, RTC_DateTypeDef *sDate);

/**
 * @brief RTC로부터 현재 시간 및 날짜 읽기
 * @param sTime 시간 정보를 저장할 구조체 포인터
 * @param sDate 날짜 정보를 저장할 구조체 포인터
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_RTC_GetDateTime(RTC_TimeTypeDef *sTime, RTC_DateTypeDef *sDate);

#endif /* __HW_RTC_H */

/**
 * @file hw_rtc.h
 * @brief RTC peripheral hardware abstraction layer header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_RTC_H
#define __HW_RTC_H

#include "main.h"

/* 전역 변수 핸들 선언 */
extern RTC_HandleTypeDef hrtc;

/**
 * @brief RTC 인터페이스 초기화
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_RTC_Init(void);

/**
 * @brief RTC 시간 및 날짜 설정
 * @param sTime 시간 구조체 포인터 (Hours, Minutes, Seconds)
 * @param sDate 날짜 구조체 포인터 (Year, Month, Date, WeekDay)
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_RTC_SetDateTime(RTC_TimeTypeDef *sTime, RTC_DateTypeDef *sDate);

/**
 * @brief RTC로부터 현재 시간 및 날짜 읽기
 * @param sTime 시간 정보를 저장할 구조체 포인터
 * @param sDate 날짜 정보를 저장할 구조체 포인터
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_RTC_GetDateTime(RTC_TimeTypeDef *sTime, RTC_DateTypeDef *sDate);

#endif /* __HW_RTC_H */

