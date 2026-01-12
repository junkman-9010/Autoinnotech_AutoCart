
/**
 * @file    TOF400C_VL53L1X.h
 * @brief   VL53L1X ToF Sensor Driver (Dual Sensor Support)
 * @author  SUNG
 * @date    2026-01-11
 */

#ifndef INC_TOF400C_VL53L1X_H_
#define INC_TOF400C_VL53L1X_H_

#include "main.h"

/**
 * @struct TOF_Config_t
 * @brief 각 TOF 센서의 하드웨어 정보를 담는 구조체
 */
typedef struct {
    I2C_HandleTypeDef *hi2c;    // 연결된 I2C 핸들러
    GPIO_TypeDef *XSHUT_Port;   // XSHUT 제어 포트
    uint16_t XSHUT_Pin;         // XSHUT 제어 핀
    uint8_t DevAddr;            // 변경 후 할당될 I2C 주소
    uint16_t Distance;          // 측정된 거리 데이터 (mm)
} TOF_Config_t;

/* 초기화 및 주소 설정 */
HAL_StatusTypeDef TOF_Init(TOF_Config_t *config, I2C_HandleTypeDef *hi2c, GPIO_TypeDef *port, uint16_t pin, uint8_t newAddr);

/* 거리 측정 시작/정지 */
HAL_StatusTypeDef TOF_StartRanging(TOF_Config_t *config);
HAL_StatusTypeDef TOF_StopRanging(TOF_Config_t *config);

/* 데이터 읽기 (Polling 방식) */
HAL_StatusTypeDef TOF_ReadDistance(TOF_Config_t *config);

#endif /* INC_TOF400C_VL53L1X_H_ */

/**
 * @file    TOF400C_VL53L1X.h
 * @brief   VL53L1X ToF Sensor Driver (Dual Sensor Support)
 * @author  SUNG
 * @date    2026-01-11
 */

#ifndef INC_TOF400C_VL53L1X_H_
#define INC_TOF400C_VL53L1X_H_

#include "main.h"

/**
 * @struct TOF_Config_t
 * @brief 각 TOF 센서의 하드웨어 정보를 담는 구조체
 */
typedef struct {
    I2C_HandleTypeDef *hi2c;    // 연결된 I2C 핸들러
    GPIO_TypeDef *XSHUT_Port;   // XSHUT 제어 포트
    uint16_t XSHUT_Pin;         // XSHUT 제어 핀
    uint8_t DevAddr;            // 변경 후 할당될 I2C 주소
    uint16_t Distance;          // 측정된 거리 데이터 (mm)
} TOF_Config_t;

/* 초기화 및 주소 설정 */
HAL_StatusTypeDef TOF_Init(TOF_Config_t *config, I2C_HandleTypeDef *hi2c, GPIO_TypeDef *port, uint16_t pin, uint8_t newAddr);

/* 거리 측정 시작/정지 */
HAL_StatusTypeDef TOF_StartRanging(TOF_Config_t *config);
HAL_StatusTypeDef TOF_StopRanging(TOF_Config_t *config);

/* 데이터 읽기 (Polling 방식) */
HAL_StatusTypeDef TOF_ReadDistance(TOF_Config_t *config);

#endif /* INC_TOF400C_VL53L1X_H_ */

