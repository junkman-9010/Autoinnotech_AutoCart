
/**
 * @file hw_system.c
 * @brief Implementation of system core configurations.
 * @author SUNG
 * @date 2026-01-11
 */

#include "hw_system.h"

/**
 * @brief System Clock Configuration
 * @details HSE(8MHz)를 소스로 사용하여 PLL을 통해 72MHz 시스템 클럭을 생성합니다.
 * USB 클럭(48MHz) 및 RTC 클럭(LSI) 설정이 포함됩니다.
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** RCC Oscillator 초기화
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    System_ErrorHandler();
  }

  /** CPU, AHB, APB 버스 클럭 설정
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                              | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    System_ErrorHandler();
  }

  /** 주변장치(RTC, USB) 클럭 설정
   */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC | RCC_PERIPHCLK_USB;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    System_ErrorHandler();
  }

  /** MCO(Master Clock Output) 설정 - PA8 핀으로 시스템 클럭 출력
   */
  HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);
}

/**
 * @brief 시스템 오류 발생 시 무한 루프 및 디버깅을 위한 핸들러
 */
void System_ErrorHandler(void)
{
  /* 사용자 구현: 에러 LED 점등 또는 로그 출력 가능 */
  __disable_irq();
  while (1)
  {
  }
}

/**
 * @brief HAL_Delay의 래핑 함수
 */
void System_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/**
 * @brief 현재 시스템 틱 반환
 */
uint32_t System_GetTick(void)
{
  return HAL_GetTick();
}
