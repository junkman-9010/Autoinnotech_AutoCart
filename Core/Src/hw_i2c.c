
/**
 * @file hw_i2c.c
 * @brief Implementation of I2C communication functions.
 * @author SUNG
 * @date 2026-01-11
 */

#include "hw_i2c.h"

/* 전역 변수 핸들 정의 */
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

/**
 * @brief I2C1 Initialization Function
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_I2C1_Init(void)
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    return HAL_ERROR;
  }
  return HAL_OK;
}

/**
 * @brief I2C2 Initialization Function
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_I2C2_Init(void)
{
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    return HAL_ERROR;
  }
  return HAL_OK;
}

/**
 * @brief I2C 레지스터 읽기 (Blocking Mode)
 * @details 장치 주소는 내부적으로 Left-shift 처리하여 사용합니다.
 */
HAL_StatusTypeDef HW_I2C_ReadReg(I2C_HandleTypeDef *hi2c, uint16_t devAddr, uint16_t regAddr, uint8_t *pData, uint16_t len)
{
  /* I2C 주소는 보통 7비트이므로 HAL 함수 사용 시 1비트 시프트가 필요할 수 있음 */
  return HAL_I2C_Mem_Read(hi2c, (devAddr << 1), regAddr, I2C_MEMADD_SIZE_8BIT, pData, len, 100);
}

/**
 * @brief I2C 레지스터 쓰기 (Blocking Mode)
 */
HAL_StatusTypeDef HW_I2C_WriteReg(I2C_HandleTypeDef *hi2c, uint16_t devAddr, uint16_t regAddr, uint8_t *pData, uint16_t len)
{
  return HAL_I2C_Mem_Write(hi2c, (devAddr << 1), regAddr, I2C_MEMADD_SIZE_8BIT, pData, len, 100);
}

HAL_StatusTypeDef HW_I2C_ReadReg16(I2C_HandleTypeDef *hi2c, uint16_t devAddr, uint16_t regAddr, uint8_t *pData, uint16_t len)
{
  // devAddr을 7-bit로 받아서 내부에서 시프트, 레지스터 사이즈는 16BIT로 설정
  return HAL_I2C_Mem_Read(hi2c, (devAddr << 1), regAddr, I2C_MEMADD_SIZE_16BIT, pData, len, 100);
}

HAL_StatusTypeDef HW_I2C_WriteReg16(I2C_HandleTypeDef *hi2c, uint16_t devAddr, uint16_t regAddr, uint8_t *pData, uint16_t len)
{
  return HAL_I2C_Mem_Write(hi2c, (devAddr << 1), regAddr, I2C_MEMADD_SIZE_16BIT, pData, len, 100);
}
