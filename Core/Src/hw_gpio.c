
/**
 * @file hw_gpio.c
 * @brief Implementation of GPIO configurations and controls.
 * @author SUNG
 * @date 2026-01-11
 */

#include "hw_gpio.h"

/**
 * @brief GPIO Initialization Function
 * @details LED, SW, Motor Control, Sensor I/O 등 모든 핀을 초기화합니다.
 */
void HW_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /* 출력 핀 초기 레벨 설정 */
  HAL_GPIO_WritePin(GPIOC, OUT1_Pin|OUT2_Pin|OUT3_Pin|OUT4_Pin|BUZZ_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, LED1_Pin|LED2_Pin|BOOT1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, BOOT1_Pin|LTE_SLEEP_Pin|TOF_SHUT2_Pin|TOF_SHUT1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOE, M2_DRVOFF_Pin|M1_DRVOFF_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOE, LED4_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOD, DE3_Pin|PWRKEY_Pin|DE2_Pin, GPIO_PIN_RESET);

  /* --- INPUT Pins 설정 (SW, RF, TOF, IMU 등) --- */
  GPIO_InitStruct.Pin = GY_NRTST_Pin|GY_INT_Pin|SW1_Pin|SW2_Pin|SW3_Pin
                          |RF_TRIG_Pin|RF_D1_Pin|RF_D2_Pin|RF_D3_Pin|RF_D4_Pin|TOF_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = IN1_Pin|IN2_Pin|IN3_Pin|IN4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = SPI2_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SPI2_INT_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = M2_FAULT_Pin|M1_FAULT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* --- OUTPUT Pins 설정 (LED, Buzzer, Control Pins) --- */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  // Port C Outputs
  GPIO_InitStruct.Pin = OUT1_Pin|OUT2_Pin|OUT3_Pin|OUT4_Pin|BUZZ_Pin;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  // Port B Outputs
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|BOOT1_Pin|LTE_SLEEP_Pin|TOF_SHUT2_Pin|TOF_SHUT1_Pin;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // Port E Outputs
  GPIO_InitStruct.Pin = M2_DRVOFF_Pin|M1_DRVOFF_Pin|LED4_Pin;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  // Port D Outputs
  GPIO_InitStruct.Pin = DE3_Pin|PWRKEY_Pin|DE2_Pin;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  // Port A LED3 (하나의 핀 예시)
  GPIO_InitStruct.Pin = LED3_Pin;
  HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);

  /* MCO (PA8) 설정 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/**
 * @brief 특정 번호의 LED를 제어합니다.
 * @param led_num 1:LED1, 2:LED2, 3:LED3, 4:LED4
 * @param state 1이면 ON, 0이면 OFF
 */
void MX_GPIO_SetLED(uint8_t led_num, uint8_t state)
{
  GPIO_PinState pin_state = (state) ? GPIO_PIN_RESET : GPIO_PIN_SET; // Active Low 기준

  switch(led_num)
  {
    case 1: HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, pin_state); break;
    case 2: HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, pin_state); break;
    case 3: HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, pin_state); break;
    case 4: HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, pin_state); break;
    default: break;
  }
}
