
/**
 * @file hw_spi.c
 * @brief Implementation of SPI communication functions.
 * @author SUNG
 * @date 2026-01-11
 */

#include "hw_spi.h"

/* 전역 변수 핸들 정의 */
SPI_HandleTypeDef hspi2;

/**
 * @brief SPI2 Initialization Function
 * @details Master mode, 8-bit, CPOL Low, CPHA 1Edge 설정을 반영합니다.
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_SPI2_Init(void)
{
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_HARD_OUTPUT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;

  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    return HAL_ERROR;
  }
  return HAL_OK;
}

/**
 * @brief SPI Full Duplex Transmit and Receive
 * @details 동시에 데이터를 보내고 받습니다.
 */
HAL_StatusTypeDef HW_SPI_TransmitReceive(uint8_t *pTxData, uint8_t *pRxData, uint16_t size)
{
  return HAL_SPI_TransmitReceive(&hspi2, pTxData, pRxData, size, 100);
}

/**
 * @brief SPI Transmit Only
 */
HAL_StatusTypeDef HW_SPI_Transmit(uint8_t *pData, uint16_t size)
{
  return HAL_SPI_Transmit(&hspi2, pData, size, 100);
}

/**
 * @brief SPI Receive Only
 */
HAL_StatusTypeDef HW_SPI_Receive(uint8_t *pData, uint16_t size)
{
  /* 송신 라인에 더미(0xFF)를 채워 클럭을 생성하며 수신합니다. */
  return HAL_SPI_Receive(&hspi2, pData, size, 100);
}
