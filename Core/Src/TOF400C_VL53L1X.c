
/**
 * @file    TOF400C_VL53L1X.c
 * @brief   SUNG's hw_i2c library integration version
 */

#include "TOF400C_VL53L1X.h"
#include "hw_i2c.h" // SUNG님의 I2C 라이브러리 포함

/* VL53L1X 내부 레지스터 (모두 16비트 주소) */
#define VL53L1_I2C_SLAVE__DEVICE_ADDRESS      0x0001
#define VL53L1_SYSTEM__INTERRUPT_CLEAR        0x0086
#define VL53L1_SYSTEM__MODE_START             0x0087
#define VL53L1_RESULT__FINAL_RANGE_MEASURED_DISTANCE 0x0096
#define VL53_I2C_DEFAULT_ADDR                 0x52 // 7-bit 기본 주소

/**
 * @brief 센서 초기화 및 I2C 주소 변경
 */
HAL_StatusTypeDef TOF_Init(TOF_Config_t *config, I2C_HandleTypeDef *hi2c, GPIO_TypeDef *port, uint16_t pin, uint8_t newAddr) {
    uint8_t temp_data;

    config->hi2c = hi2c;
    config->XSHUT_Port = port;
    config->XSHUT_Pin = pin;
    config->DevAddr = newAddr;
    config->Distance = 0;

    // 1. 하드웨어 리셋 (XSHUT Low)
    HAL_GPIO_WritePin(config->XSHUT_Port, config->XSHUT_Pin, GPIO_PIN_RESET);
    HAL_Delay(200); // 안정적인 리셋을 위해 시간 충분히 부여

    // 2. 해당 센서만 활성화 (XSHUT High)
    HAL_GPIO_WritePin(config->XSHUT_Port, config->XSHUT_Pin, GPIO_PIN_SET);
    HAL_Delay(200); // 센서 부팅 시간 (Boot-up time) 대기

    // 3. I2C 주소 변경 (반드시 16비트 레지스터 쓰기 함수 사용)
    // SUNG님의 HW_I2C_WriteReg16은 내부에서 (addr << 1)을 수행함
    temp_data = newAddr;
    if (HW_I2C_WriteReg16(config->hi2c, VL53_I2C_DEFAULT_ADDR, VL53L1_I2C_SLAVE__DEVICE_ADDRESS, &temp_data, 1) != HAL_OK) {
        return HAL_ERROR; // 여기서 실패하면 통신 배선이나 센서 전원 확인 필요
    }

    HAL_Delay(10); // 주소 변경 후 안정화 시간

    // 4. 새 주소로 장치가 응답하는지 확인
    if (HAL_I2C_IsDeviceReady(config->hi2c, (config->DevAddr << 1), 3, 100) != HAL_OK) {
        return HAL_ERROR;
    }

    // 5. 초기 인터럽트 클리어 (시스템 준비)
    temp_data = 0x01;
    HW_I2C_WriteReg16(config->hi2c, config->DevAddr, VL53L1_SYSTEM__INTERRUPT_CLEAR, &temp_data, 1);

    return HAL_OK;
}

/**
 * @brief 거리 측정 시작
 */
HAL_StatusTypeDef TOF_StartRanging(TOF_Config_t *config) {
    uint8_t data = 0x40; // Continuous mode
    return HW_I2C_WriteReg16(config->hi2c, config->DevAddr, VL53L1_SYSTEM__MODE_START, &data, 1);
}

/**
 * @brief 거리 데이터 읽기
 */
HAL_StatusTypeDef TOF_ReadDistance(TOF_Config_t *config) {
    uint8_t data[2];

    // 16비트 레지스터 주소 0x0096에서 2바이트 읽기
    if (HW_I2C_ReadReg16(config->hi2c, config->DevAddr, VL53L1_RESULT__FINAL_RANGE_MEASURED_DISTANCE, data, 2) == HAL_OK) {
        config->Distance = (uint16_t)((data[0] << 8) | data[1]);

        // 다음 측정을 위해 인터럽트 클리어 필수
        uint8_t clear_val = 0x01;
        HW_I2C_WriteReg16(config->hi2c, config->DevAddr, VL53L1_SYSTEM__INTERRUPT_CLEAR, &clear_val, 1);
        return HAL_OK;
    }
    return HAL_ERROR;
}
