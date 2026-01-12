
/**
 * @file hw_usb.c
 * @brief Implementation of USB PCD (Peripheral Control Driver) functions.
 * @author SUNG
 * @date 2026-01-11
 */

#include "hw_usb.h"

/* 전역 변수 핸들 정의 */
PCD_HandleTypeDef hpcd_USB_FS;

/**
 * @brief USB_OTG_FS Initialization Function
 * @details 장치 모드로 설정하며, 엔드포인트 8개를 기본으로 구성합니다.
 */
void HW_USB_PCD_Init(void)
{
  hpcd_USB_FS.Instance = USB;
  hpcd_USB_FS.Init.dev_endpoints = 8;
  hpcd_USB_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_FS.Init.battery_charging_enable = DISABLE;

  if (HAL_PCD_Init(&hpcd_USB_FS) != HAL_OK)
  {
    /* 시스템 에러 핸들러 호출 가능 */
    Error_Handler();
  }
}

/**
 * @brief USB 가동 (LL layer start)
 */
HAL_StatusTypeDef HW_USB_Start(void)
{
  return HAL_PCD_Start(&hpcd_USB_FS);
}

/**
 * @brief USB 중지 (LL layer stop)
 */
HAL_StatusTypeDef HW_USB_Stop(void)
{
  return HAL_PCD_Stop(&hpcd_USB_FS);
}

/**
 * @brief USB 인터럽트 콜백 예시 (Data Out)
 */
void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  /* [SUNG] USB 데이터 수신 시 처리 로직 */
}
