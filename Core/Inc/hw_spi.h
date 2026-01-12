
/**
 * @file hw_spi.h
 * @brief SPI peripheral hardware abstraction layer header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_SPI_H
#define __HW_SPI_H

#include "main.h"

/* 전역 변수 핸들 선언 */
extern SPI_HandleTypeDef hspi2;

/**
 * @brief SPI2 인터페이스 초기화
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_SPI2_Init(void);

/**
 * @brief SPI를 통해 데이터를 송수신합니다. (Full Duplex)
 * @param pTxData 송신 데이터 버퍼 포인터
 * @param pRxData 수신 데이터 버퍼 포인터
 * @param size 데이터 크기
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_SPI_TransmitReceive(uint8_t *pTxData, uint8_t *pRxData, uint16_t size);

/**
 * @brief SPI 데이터를 송신만 합니다.
 * @param pData 송신 데이터 포인터
 * @param size 데이터 크기
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_SPI_Transmit(uint8_t *pData, uint16_t size);

/**
 * @brief SPI 데이터를 수신만 합니다.
 * @param pData 수신 데이터 저장 포인터
 * @param size 데이터 크기
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_SPI_Receive(uint8_t *pData, uint16_t size);

#endif /* __HW_SPI_H */

/**
 * @file hw_spi.h
 * @brief SPI peripheral hardware abstraction layer header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_SPI_H
#define __HW_SPI_H

#include "main.h"

/* 전역 변수 핸들 선언 */
extern SPI_HandleTypeDef hspi2;

/**
 * @brief SPI2 인터페이스 초기화
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_SPI2_Init(void);

/**
 * @brief SPI를 통해 데이터를 송수신합니다. (Full Duplex)
 * @param pTxData 송신 데이터 버퍼 포인터
 * @param pRxData 수신 데이터 버퍼 포인터
 * @param size 데이터 크기
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_SPI_TransmitReceive(uint8_t *pTxData, uint8_t *pRxData, uint16_t size);

/**
 * @brief SPI 데이터를 송신만 합니다.
 * @param pData 송신 데이터 포인터
 * @param size 데이터 크기
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_SPI_Transmit(uint8_t *pData, uint16_t size);

/**
 * @brief SPI 데이터를 수신만 합니다.
 * @param pData 수신 데이터 저장 포인터
 * @param size 데이터 크기
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_SPI_Receive(uint8_t *pData, uint16_t size);

#endif /* __HW_SPI_H */

