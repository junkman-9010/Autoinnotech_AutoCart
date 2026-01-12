
/**
 * @file hw_can.h
 * @brief CAN peripheral hardware abstraction layer header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_CAN_H
#define __HW_CAN_H

#include "main.h"

/* 전역 변수 핸들 선언 (외부 모듈 참조용) */
extern CAN_HandleTypeDef hcan;

/* CAN 식별자 정의 예시 */
#define CAN_ID_STATUS    0x100
#define CAN_ID_CONTROL   0x200

/**
 * @brief CAN 인터페이스 초기화 및 활성화
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_CAN_Init(void);

/**
 * @brief CAN 메시지 전송 함수
 * @param id 전송할 CAN ID (Standard ID)
 * @param pData 전송할 데이터 포인터 (최대 8바이트)
 * @param len 데이터 길이 (0~8)
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_CAN_Transmit(uint32_t id, uint8_t *pData, uint8_t len);

/**
 * @brief CAN 필터 설정 (모든 메시지 수신 허용 또는 특정 ID 필터링)
 * @retval None
 */
void HW_CAN_ConfigFilter(void);

#endif /* __HW_CAN_H */

/**
 * @file hw_can.h
 * @brief CAN peripheral hardware abstraction layer header.
 * @author SUNG
 * @date 2026-01-11
 */

#ifndef __HW_CAN_H
#define __HW_CAN_H

#include "main.h"

/* 전역 변수 핸들 선언 (외부 모듈 참조용) */
extern CAN_HandleTypeDef hcan;

/* CAN 식별자 정의 예시 */
#define CAN_ID_STATUS    0x100
#define CAN_ID_CONTROL   0x200

/**
 * @brief CAN 인터페이스 초기화 및 활성화
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_CAN_Init(void);

/**
 * @brief CAN 메시지 전송 함수
 * @param id 전송할 CAN ID (Standard ID)
 * @param pData 전송할 데이터 포인터 (최대 8바이트)
 * @param len 데이터 길이 (0~8)
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_CAN_Transmit(uint32_t id, uint8_t *pData, uint8_t len);

/**
 * @brief CAN 필터 설정 (모든 메시지 수신 허용 또는 특정 ID 필터링)
 * @retval None
 */
void HW_CAN_ConfigFilter(void);

#endif /* __HW_CAN_H */

