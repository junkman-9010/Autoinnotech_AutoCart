
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

//	// 센서 1 초기화: XSHUT=PA0, 주소=0x54로 설정
//	TOF_Init(&tof_left, &hi2c2, GPIOA, GPIO_PIN_0, 0x54);
//	// 센서 2 초기화: XSHUT=PA1, 주소=0x56으로 설정
//	TOF_Init(&tof_right, &hi2c2, GPIOA, GPIO_PIN_1, 0x56);

	// *** 이 코드가 없으면 Distance 값이 0에서 변하지 않습니다 ***
//	TOF_StartRanging(&tof_left);
//	TOF_StartRanging(&tof_right);

	HAL_GPIO_WritePin(TOF_SHUT1_GPIO_Port, TOF_SHUT1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(TOF_SHUT2_GPIO_Port, TOF_SHUT2_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);

	// 2. 직접 Ranging Start 명령 전송 (0x29 주소의 0x0087 레지스터에 0x40 쓰기)
	uint8_t start_cmd = 0x40;
	if (HW_I2C_WriteReg16(&hi2c2, 0x29, 0x0087, &start_cmd, 1) == HAL_OK) {
		char *msg = "Direct Start OK (0x29)\r\n";
		HW_RS485_Transmit(&rs485_ch3, (uint8_t*) msg, strlen(msg), 100);
	} else {
		char *msg = "Direct Start Fail!\r\n";
		HW_RS485_Transmit(&rs485_ch3, (uint8_t*) msg, strlen(msg), 100);
	}

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
			timer_100ms_flag = 0; // 플래그 초기화 (중요)

			// 1. TOF 센서로부터 거리 데이터 읽기
//			TOF_ReadDistance(&tof_left);
//			TOF_ReadDistance(&tof_right);

			// 2. 데이터를 문자열로 포맷팅
			// 예: "L: 0150mm, R: 1200mm\r\n"
			uint8_t raw_data[2] = { 0, 0 };

			// 1. 0x29 주소의 0x0096(Distance) 레지스터에서 2바이트 직접 읽기
			if (HW_I2C_ReadReg16(&hi2c2, 0x29, 0x0096, raw_data, 2) == HAL_OK) {
				// 바이트 결합 (MSB << 8 | LSB)
				direct_distance = (uint16_t) ((raw_data[0] << 8) | raw_data[1]);

				// 2. 다음 측정을 위해 인터럽트 클리어 (0x0086 레지스터에 0x01 쓰기) 필수!
				uint8_t clear_val = 0x01;
				HW_I2C_WriteReg16(&hi2c2, 0x29, 0x0086, &clear_val, 1);

				// 3. RS485 출력
				int len = sprintf(tx_msg, "Direct(0x29) Dist: %d mm\r\n",
						direct_distance);
				HW_RS485_Transmit(&rs485_ch3, (uint8_t*) tx_msg, len, 100);
			} else {
				// 통신 실패 시
				char *err = "Direct Read Fail\r\n";
				HW_RS485_Transmit(&rs485_ch3, (uint8_t*) err, strlen(err), 100);
			}

			// LED1 토글 동작 수행
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
