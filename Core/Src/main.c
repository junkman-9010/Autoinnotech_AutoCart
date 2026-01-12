/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

// C언어 기본 모듈
#include <stdio.h>
#include <string.h>

// 하드웨어 기본 모듈
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

// 추가되는 기능 모듈
#include "hw_rs485.h"
#include "modbus-rtu.h"

//#include "TOF400C_VL53L1X.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SLAVE_MAP_COUNT (sizeof(slave_map) / sizeof(slave_map[0]))

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// 1. 데이터 저장소 및 맵 설정
uint16_t modbus_reg_A[11] = { 0, }; // 0~10번지
uint16_t modbus_reg_B[9] = { 0, };  // 102~110번지

Modbus_rtu_RegisterRange_t slave_map[] = { { 0, 10, modbus_reg_A }, { 102, 110,
		modbus_reg_B } };

RS485_Config_t rs485_ch3; // 채널 3용 인스턴스
//Modbus_rtu_Packet_t modbus_packet;

Modbus_rtu_Packet_t rx_packet;
uint8_t rx_buf[256];      // 데이터 수신 버퍼
uint16_t rx_len = 0;      // 수신된 데이터 길이

// 문자열 조립을 위한 버퍼 추가
uint16_t direct_distance = 0; // 직접 읽어온 거리 저장
char tx_msg[64];

//uint8_t test_payload[] = "RS485 GENERIC TEST\r\n";

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
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
	// 범용 초기화 함수 사용: huart3와 main.h에 정의된 DE3 핀을 연결
	HW_RS485_Init_Config(&rs485_ch3, &huart3, DE3_GPIO_Port, DE3_Pin);


	HAL_GPIO_WritePin(DE3_GPIO_Port, DE3_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(M1_DIR_GPIO_Port, M1_DIR_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M2_DIR_GPIO_Port, M2_DIR_Pin, GPIO_PIN_RESET);

//	HAL_GPIO_WritePin(M1_SLEEP_GPIO_Port, M1_SLEEP_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(M2_SLEEP_GPIO_Port, M2_SLEEP_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(M1_SLEEP_GPIO_Port, M1_SLEEP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(M2_SLEEP_GPIO_Port, M2_SLEEP_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(M1_DRVOFF_GPIO_Port, M1_DRVOFF_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M2_DRVOFF_GPIO_Port, M2_DRVOFF_Pin, GPIO_PIN_RESET);

	// [STEP 2] PWM 시작
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2); // PD13
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2); // PC7

	// TIM8은 고급 타이머이므로 출력을 물리적으로 허용해줘야 합니다.
	__HAL_TIM_MOE_ENABLE(&htim8);


	HAL_GPIO_WritePin(TOF_SHUT1_GPIO_Port, TOF_SHUT1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(TOF_SHUT2_GPIO_Port, TOF_SHUT2_Pin, GPIO_PIN_RESET);

	// TIM2 인터럽트 시작 (이 코드가 있어야 콜백이 실행됩니다)
	HAL_TIM_Base_Start_IT(&htim2);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

//		// --- RS485 송신 프로세스 시작 ---
//		// 범용 송신 함수 호출
//		HW_RS485_Transmit(&rs485_ch3, test_payload, sizeof(test_payload) - 1,
//				100);
//        HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
//		// --- [STEP 1] 데이터 수신 확인 (간단한 폴링) ---
//		// UART3에 데이터가 들어왔는지 확인 (Blocking 없이 한 바이트씩 체크)
//		if (HAL_UART_Receive(&huart3, &rx_buf[rx_len], 1, 0) == HAL_OK) {
//			rx_len++;
//			// 패킷 끝을 감지하기 위한 간단한 로직 (실제로는 타임아웃 처리가 필요함)
//		}
//
//		// --- [STEP 2] 수신된 패킷 처리 ---
//		// 예시로 rx_len이 일정 이상 모였을 때(또는 특정 조건) 분석 시작
//		if (rx_len >= 8) { // Modbus RTU 최소 길이는 8바이트 (Addr+FC+Addr(2)+Qty(2)+CRC(2))
//
//			// 1. 패킷 파싱 및 CRC 검증
//			if (modbus_rtu_Slave_Parse(rx_buf, rx_len, &rx_packet)) {
//
//				// 2. 내 주소 확인 (Slave ID를 1번으로 가정)
//				if (rx_packet.Address == 0x01) {
//
//					// 3. 데이터 맵(0-10, 102-110)을 참조하여 응답 전송
//					modbus_rtu_Slave_Process(&rs485_ch3, &rx_packet, slave_map,
//					SLAVE_MAP_COUNT);
//
//					// 동작 확인용 LED 토글
//					HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
//				}
//			}
//
//			// 처리 완료 후 버퍼 초기화
//			rx_len = 0;
//			memset(rx_buf, 0, sizeof(rx_buf));
//		}
		// 100ms 플래그가 세워졌는지 확인
		if (timer_100ms_flag == 1) {
			timer_100ms_flag = 0; // 플래그 초기화

			// --- [1] I2C2 장치 스캔 및 RS485 전송 ---
			char scan_result[32];
			HAL_StatusTypeDef res;
			uint8_t found_any = 0;

			// RS485로 스캔 시작 알림 (선택 사항)
			// HW_RS485_Transmit(&rs485_ch3, (uint8_t*)"Scan:", 5, 10);

			for (uint16_t i = 1; i < 128; i++) {
				// i << 1 은 7비트 주소를 HAL 규격(8비트)으로 변환
				res = HAL_I2C_IsDeviceReady(&hi2c2, (uint16_t) (i << 1), 2, 2);
				if (res == HAL_OK) {
					sprintf(scan_result, "I2C2: 0x%02X\r\n", i);
					HW_RS485_Transmit(&rs485_ch3, (uint8_t*) scan_result,
							strlen(scan_result), 500);
					found_any = 1;
				}
			}

			if (!found_any) {
				char *none_msg = "I2C2: None\r\n";
				HW_RS485_Transmit(&rs485_ch3, (uint8_t*) none_msg,
						strlen(none_msg), 100);
			}

			// --- [2] 기존 PWM 및 LED 동작 유지 ---
			uint32_t duty_20_percent = 720; // 3600 * 0.20
			HW_TIM_SetPWM_Duty(&htim4, TIM_CHANNEL_2, duty_20_percent);
			HW_TIM_SetPWM_Duty(&htim8, TIM_CHANNEL_2, duty_20_percent);

			// 동작 확인용 LED1 토글
			HAL_GPIO_TogglePin(GPIOB, LED1_Pin);
		}

	}
	/* USER CODE END 3 */
}

/* USER CODE BEGIN 4 */

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
