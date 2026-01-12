
/**
 * @file hw_usb.h
 * @brief USB peripheral hardware abstraction layer header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_USB_H
#define __HW_USB_H

#include "main.h"

/* 전역 변수 핸들 선언 */
extern PCD_HandleTypeDef hpcd_USB_FS;

/**
 * @brief USB Full Speed 주변장치 초기화
 */
void HW_USB_PCD_Init(void);

/**
 * @brief USB 장치 연결 시작
 */
HAL_StatusTypeDef HW_USB_Start(void);

/**
 * @brief USB 장치 연결 중지
 */
HAL_StatusTypeDef HW_USB_Stop(void);

#endif /* __HW_USB_H */

/**
 * @file hw_usb.h
 * @brief USB peripheral hardware abstraction layer header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_USB_H
#define __HW_USB_H

#include "main.h"

/* 전역 변수 핸들 선언 */
extern PCD_HandleTypeDef hpcd_USB_FS;

/**
 * @brief USB Full Speed 주변장치 초기화
 */
void HW_USB_PCD_Init(void);

/**
 * @brief USB 장치 연결 시작
 */
HAL_StatusTypeDef HW_USB_Start(void);

/**
 * @brief USB 장치 연결 중지
 */
HAL_StatusTypeDef HW_USB_Stop(void);

#endif /* __HW_USB_H */

