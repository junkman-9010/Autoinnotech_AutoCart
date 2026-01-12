
/**
 * @file hw_system.h
 * @brief System clock and core configuration header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_SYSTEM_H
#define __HW_SYSTEM_H

#include "main.h"

/**
 * @brief 시스템 클럭 설정 (HSE 기반 72MHz 설정)
 * @retval None
 */
void SystemClock_Config(void);

/**
 * @brief 시스템 에러 발생 시 처리 루틴
 * @retval None
 */
void System_ErrorHandler(void);

/**
 * @brief 시스템 밀리초 단위 딜레이
 * @param Delay 딜레이 시간 (ms)
 */
void System_Delay(uint32_t Delay);

/**
 * @brief 시스템 가동 후 경과 시간(ms) 반환
 * @retval uint32_t 현재 틱 값
 */
uint32_t System_GetTick(void);

#endif /* __HW_SYSTEM_H */

/**
 * @file hw_system.h
 * @brief System clock and core configuration header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_SYSTEM_H
#define __HW_SYSTEM_H

#include "main.h"

/**
 * @brief 시스템 클럭 설정 (HSE 기반 72MHz 설정)
 * @retval None
 */
void SystemClock_Config(void);

/**
 * @brief 시스템 에러 발생 시 처리 루틴
 * @retval None
 */
void System_ErrorHandler(void);

/**
 * @brief 시스템 밀리초 단위 딜레이
 * @param Delay 딜레이 시간 (ms)
 */
void System_Delay(uint32_t Delay);

/**
 * @brief 시스템 가동 후 경과 시간(ms) 반환
 * @retval uint32_t 현재 틱 값
 */
uint32_t System_GetTick(void);

#endif /* __HW_SYSTEM_H */

