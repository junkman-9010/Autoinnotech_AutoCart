/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include <string.h>

/* 하드웨어 및 모듈 헤더 */
#include "hw_can.h"
#include "hw_dac.h"
#include "hw_gpio.h"
#include "hw_i2c.h"
#include "hw_rtc.h"
#include "hw_spi.h"
#include "hw_system.h"
#include "hw_tim.h"
#include "hw_uart.h"
#include "hw_usb.h"
#include "hw_rs485.h"
#include "modbus-rtu.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum {
    TOF_STATE_IDLE,       // 측정 대기 상태
    TOF_STATE_READY_WAIT  // 측정 시작 후 INT 핀 대기 상태
} TOF_Step_t;

/* Private define ------------------------------------------------------------*/
#define TOF_ADDR (0x29 << 1)
#define SLAVE_MAP_COUNT (sizeof(slave_map) / sizeof(slave_map[0]))

/* Private variables ---------------------------------------------------------*/
uint16_t modbus_reg_A[11] = { 0, };
uint16_t modbus_reg_B[9] = { 0, };
Modbus_rtu_RegisterRange_t slave_map[] = { { 0, 10, modbus_reg_A }, { 102, 110, modbus_reg_B } };

RS485_Config_t rs485_ch3;
uint8_t tof_initialized = 0;
TOF_Step_t tof_step = TOF_STATE_IDLE;
uint32_t tof_timeout_tick = 0;

/* Private function prototypes -----------------------------------------------*/
void TOF_Simple_Init(void);
void TOF_Start_Ranging(void);

/* Main program --------------------------------------------------------------*/
int main(void) {
    HAL_Init();
    SystemClock_Config();

    /* 주변장치 초기화 */
    HW_GPIO_Init();
    HW_RTC_Init();
    HW_DAC_Init();
    HW_I2C1_Init();
    HW_I2C2_Init();
    HW_SPI2_Init();
    HW_TIM1_Init();
    HW_TIM2_Init();
    HW_TIM8_Init();
    HW_USART1_UART_Init();
    HW_USART2_UART_Init();
    HW_USART3_UART_Init();
    HW_UART4_Init();
    HW_UART5_Init();
    HW_CAN_Init();
    HW_TIM4_Init();
    HW_USB_PCD_Init();

    /* USER CODE BEGIN 2 */
    // RS485 초기화
    HW_RS485_Init_Config(&rs485_ch3, &huart3, DE3_GPIO_Port, DE3_Pin);

    // 모터 드라이버 및 초기 핀 설정
    HAL_GPIO_WritePin(M1_SLEEP_GPIO_Port, M1_SLEEP_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(M2_SLEEP_GPIO_Port, M2_SLEEP_Pin, GPIO_PIN_SET);

    // PWM 시작 및 출력 허용
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
    __HAL_TIM_MOE_ENABLE(&htim8);

    // 센서 활성화 및 초기화
    HAL_GPIO_WritePin(TOF_SHUT1_GPIO_Port, TOF_SHUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
    TOF_Simple_Init();

    // 100ms 타이머 인터럽트 시작
    HAL_TIM_Base_Start_IT(&htim2);
    /* USER CODE END 2 */

    while (1) {
        /* [STEP 1] 100ms 주기적 측정 요청 */
        if (timer_100ms_flag == 1) {
            timer_100ms_flag = 0;

            if (!tof_initialized) {
                TOF_Simple_Init();
            }

            // 센서가 IDLE 상태일 때만 새로운 측정 시작
            if (tof_initialized && tof_step == TOF_STATE_IDLE) {
                TOF_Start_Ranging();
                tof_step = TOF_STATE_READY_WAIT;
                tof_timeout_tick = HAL_GetTick(); // 타임아웃 감시용
            }

            // PWM 제어 및 LED 토글 유지
			uint32_t duty_20_percent = 720;
            HW_TIM_SetPWM_Duty(&htim4, TIM_CHANNEL_2, duty_20_percent);
            HW_TIM_SetPWM_Duty(&htim8, TIM_CHANNEL_2, duty_20_percent);
            HAL_GPIO_TogglePin(GPIOB, LED1_Pin);
        }

        /* [STEP 2] TOF_INT 핀(PE1) 상태 실시간 체크 */
        if (tof_step == TOF_STATE_READY_WAIT) {
            // 센서가 측정을 완료하여 INT 핀을 Low로 내렸는지 확인
            if (HAL_GPIO_ReadPin(GPIOE, TOF_INT_Pin) == GPIO_PIN_RESET) {
                uint8_t range_data[2];
                // 거리 값 읽기 (0x0096)
                if (HAL_I2C_Mem_Read(&hi2c2, TOF_ADDR, 0x0096, I2C_MEMADD_SIZE_16BIT, range_data, 2, 100) == HAL_OK) {
                    uint16_t distance = (range_data[0] << 8) | range_data[1];
                    char tof_msg[64];
                    sprintf(tof_msg, "Distance: %d mm\r\n", distance);
                    HW_RS485_Transmit(&rs485_ch3, (uint8_t*)tof_msg, strlen(tof_msg), 50);
                }

                // 인터럽트 클리어 (반드시 수행해야 핀이 다시 High로 복귀)
                uint8_t clear_int = 0x01;
                HAL_I2C_Mem_Write(&hi2c2, TOF_ADDR, 0x0086, I2C_MEMADD_SIZE_16BIT, &clear_int, 1, 10);

                tof_step = TOF_STATE_IDLE;
            }
            // 안전장치: 150ms 동안 응답 없으면 IDLE로 복귀 (배선 이탈 등 대비)
            else if (HAL_GetTick() - tof_timeout_tick > 150) {
                tof_step = TOF_STATE_IDLE;
            }
        }
    }
}

/* USER CODE BEGIN 4 */
void TOF_Simple_Init(void) {
    uint8_t data = 0;
    HAL_StatusTypeDef status;
    char debug_msg[64];

    // Model ID 확인 (VL53L1X = 0xEA)
    status = HAL_I2C_Mem_Read(&hi2c2, TOF_ADDR, 0x010F, I2C_MEMADD_SIZE_16BIT, &data, 1, 100);

    if (status == HAL_OK && data == 0xEA) {
        // 기본 부팅 및 초기화 (0x0087에 0x01을 써서 시스템 가동)
        uint8_t start_cmd = 0x01;
        if (HAL_I2C_Mem_Write(&hi2c2, TOF_ADDR, 0x0087, I2C_MEMADD_SIZE_16BIT, &start_cmd, 1, 100) == HAL_OK) {
            tof_initialized = 1;
            sprintf(debug_msg, "[TOF] Init Success (ID: 0x%02X)\r\n", data);
        } else {
            sprintf(debug_msg, "[TOF] Config Write Failed!\r\n");
        }
    } else {
        sprintf(debug_msg, "[TOF] Search Failed! Status: %d, ID: 0x%02X\r\n", status, data);
    }
    HW_RS485_Transmit(&rs485_ch3, (uint8_t*)debug_msg, strlen(debug_msg), 50);
}

void TOF_Start_Ranging(void) {
    uint8_t start_cmd = 0x01;
    if (HAL_I2C_Mem_Write(&hi2c2, TOF_ADDR, 0x0087, I2C_MEMADD_SIZE_16BIT, &start_cmd, 1, 100) != HAL_OK) {
        char *err = "[TOF] Start Failed!\r\n";
        HW_RS485_Transmit(&rs485_ch3, (uint8_t*)err, strlen(err), 50);
    }
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
