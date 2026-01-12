
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
/**
 * @file hw_gpio.c
 * @brief Implementation of GPIO configurations and controls based on SUNG's Pin Map.
 * @author SUNG
 * @date 2026-01-11
 */

#include "hw_gpio.h"

/**
 * @brief GPIO Initialization Function
 * @details 모든 정의된 핀들을 입력/출력/교체기능 모드로 초기화합니다.
 */
void HW_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* 1. GPIO 클럭 활성화 */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_AFIO_CLK_ENABLE(); // 리맵 및 인터럽트용

  /* 2. 출력 핀 초기 레벨 설정 (안전을 위해 초기화 전 설정) */
  // 모터 드라이버: SLEEP 해제(High), 나머지는 정지상태(Low)
  HAL_GPIO_WritePin(GPIOE, M1_SLEEP_Pin | M2_SLEEP_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOE, M1_DRVOFF_Pin | M2_DRVOFF_Pin, GPIO_PIN_RESET);

  // 모터 방향 및 브레이크 (Port C & D)
  HAL_GPIO_WritePin(GPIOC, M1_DIR_Pin | M1_BREAK_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOD, M2_DIR_Pin | M2_BREAK_Pin, GPIO_PIN_RESET);

  // LED: Active Low 기준으로 초기 상태 OFF(Set)
  HAL_GPIO_WritePin(GPIOB, LED1_Pin | LED2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOE, LED4_Pin, GPIO_PIN_SET);

  // 기타 제어 핀
  HAL_GPIO_WritePin(GPIOC, OUT1_Pin|OUT2_Pin|OUT3_Pin|OUT4_Pin|BUZZ_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOD, DE3_Pin|PWRKEY_Pin|DE2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, BOOT1_Pin|LTE_SLEEP_Pin|TOF_SHUT2_Pin|TOF_SHUT1_Pin, GPIO_PIN_RESET);

  /* 3. INPUT Pins 설정 */
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  // Port E Inputs (센서, 스위치, RF 등)
  GPIO_InitStruct.Pin = GY_NRTST_Pin|GY_INT_Pin|SW1_Pin|SW2_Pin|SW3_Pin
                          |RF_TRIG_Pin|RF_D1_Pin|RF_D2_Pin|RF_D3_Pin|RF_D4_Pin|TOF_INT_Pin;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  // Port A Inputs
  GPIO_InitStruct.Pin = IN1_Pin|IN2_Pin|IN3_Pin|IN4_Pin;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // Port C & D (인터럽트/상태 입력)
  GPIO_InitStruct.Pin = SPI2_INT_Pin | M1_FGOUT_Pin;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = M1_FAULT_Pin | M2_FAULT_Pin | M2_FGOUT_Pin;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* 4. OUTPUT Pins 설정 (Push-Pull) */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  // Port C Outputs
  GPIO_InitStruct.Pin = OUT1_Pin|OUT2_Pin|OUT3_Pin|OUT4_Pin|BUZZ_Pin|M1_DIR_Pin|M1_BREAK_Pin;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  // Port B Outputs
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|BOOT1_Pin|LTE_SLEEP_Pin|TOF_SHUT2_Pin|TOF_SHUT1_Pin;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // Port E Outputs
  GPIO_InitStruct.Pin = M2_SLEEP_Pin|M1_SLEEP_Pin|M2_DRVOFF_Pin|M1_DRVOFF_Pin|LED4_Pin;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  // Port D Outputs (PD13은 타이머에서 AF_PP로 설정하므로 여기서 제외!)
  GPIO_InitStruct.Pin = DE3_Pin|PWRKEY_Pin|DE2_Pin|M2_DIR_Pin|M2_BREAK_Pin;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  // Port A LED3
  GPIO_InitStruct.Pin = LED3_Pin;
  HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);

  /* 5. MCO (PA8) 설정 */
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
