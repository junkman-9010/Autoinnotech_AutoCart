
/**
 * @file hw_i2c.h
 * @brief I2C peripheral hardware abstraction layer header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_I2C_H
#define __HW_I2C_H

#include "main.h"

/* 전역 변수 핸들 선언 */
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

/**
 * @brief I2C1 인터페이스 초기화
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_I2C1_Init(void);

/**
 * @brief I2C2 인터페이스 초기화
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_I2C2_Init(void);

/**
 * @brief I2C 장치로부터 데이터를 읽어옵니다.(8Bit)
 * @param hi2c I2C 핸들 (hi2c1 또는 hi2c2)
 * @param devAddr 장치 주소 (7-bit)
 * @param regAddr 레지스터 주소
 * @param pData 수신 데이터 버퍼 포인터
 * @param len 읽어올 데이터 길이
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_I2C_ReadReg(I2C_HandleTypeDef *hi2c, uint16_t devAddr, uint16_t regAddr, uint8_t *pData, uint16_t len);

/**
 * @brief I2C 장치에 데이터를 씁니다.(8Bit)
 * @param hi2c I2C 핸들 (hi2c1 또는 hi2c2)
 * @param devAddr 장치 주소 (7-bit)
 * @param regAddr 레지스터 주소
 * @param pData 송신 데이터 버퍼 포인터
 * @param len 쓸 데이터 길이
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_I2C_WriteReg(I2C_HandleTypeDef *hi2c, uint16_t devAddr, uint16_t regAddr, uint8_t *pData, uint16_t len);


/**
 * @brief I2C 장치로부터 데이터를 읽어옵니다.(16Bit)
 * @param hi2c I2C 핸들 (hi2c1 또는 hi2c2)
 * @param devAddr 장치 주소 (7-bit)
 * @param regAddr 레지스터 주소
 * @param pData 수신 데이터 버퍼 포인터
 * @param len 읽어올 데이터 길이
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_I2C_ReadReg16(I2C_HandleTypeDef *hi2c, uint16_t devAddr, uint16_t regAddr, uint8_t *pData, uint16_t len);


/**
 * @brief I2C 장치에 데이터를 씁니다.(16Bit)
 * @param hi2c I2C 핸들 (hi2c1 또는 hi2c2)
 * @param devAddr 장치 주소 (7-bit)
 * @param regAddr 레지스터 주소
 * @param pData 송신 데이터 버퍼 포인터
 * @param len 쓸 데이터 길이
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_I2C_WriteReg16(I2C_HandleTypeDef *hi2c, uint16_t devAddr, uint16_t regAddr, uint8_t *pData, uint16_t len);

#endif /* __HW_I2C_H */

/**
 * @file hw_i2c.h
 * @brief I2C peripheral hardware abstraction layer header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_I2C_H
#define __HW_I2C_H

#include "main.h"

/* 전역 변수 핸들 선언 */
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

/**
 * @brief I2C1 인터페이스 초기화
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_I2C1_Init(void);

/**
 * @brief I2C2 인터페이스 초기화
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_I2C2_Init(void);

/**
 * @brief I2C 장치로부터 데이터를 읽어옵니다.(8Bit)
 * @param hi2c I2C 핸들 (hi2c1 또는 hi2c2)
 * @param devAddr 장치 주소 (7-bit)
 * @param regAddr 레지스터 주소
 * @param pData 수신 데이터 버퍼 포인터
 * @param len 읽어올 데이터 길이
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_I2C_ReadReg(I2C_HandleTypeDef *hi2c, uint16_t devAddr, uint16_t regAddr, uint8_t *pData, uint16_t len);

/**
 * @brief I2C 장치에 데이터를 씁니다.(8Bit)
 * @param hi2c I2C 핸들 (hi2c1 또는 hi2c2)
 * @param devAddr 장치 주소 (7-bit)
 * @param regAddr 레지스터 주소
 * @param pData 송신 데이터 버퍼 포인터
 * @param len 쓸 데이터 길이
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_I2C_WriteReg(I2C_HandleTypeDef *hi2c, uint16_t devAddr, uint16_t regAddr, uint8_t *pData, uint16_t len);


/**
 * @brief I2C 장치로부터 데이터를 읽어옵니다.(16Bit)
 * @param hi2c I2C 핸들 (hi2c1 또는 hi2c2)
 * @param devAddr 장치 주소 (7-bit)
 * @param regAddr 레지스터 주소
 * @param pData 수신 데이터 버퍼 포인터
 * @param len 읽어올 데이터 길이
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_I2C_ReadReg16(I2C_HandleTypeDef *hi2c, uint16_t devAddr, uint16_t regAddr, uint8_t *pData, uint16_t len);


/**
 * @brief I2C 장치에 데이터를 씁니다.(16Bit)
 * @param hi2c I2C 핸들 (hi2c1 또는 hi2c2)
 * @param devAddr 장치 주소 (7-bit)
 * @param regAddr 레지스터 주소
 * @param pData 송신 데이터 버퍼 포인터
 * @param len 쓸 데이터 길이
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_I2C_WriteReg16(I2C_HandleTypeDef *hi2c, uint16_t devAddr, uint16_t regAddr, uint8_t *pData, uint16_t len);

#endif /* __HW_I2C_H */

