
/**
 * @file hw_can.c
 * @brief Implementation of CAN communication functions.
 * @author SUNG
 * @date 2026-01-11
 * @details This file handles initialization, filtering, and Tx/Rx for CAN1 using a global handle.
 */

#include "hw_can.h"

/* 전역 변수 핸들 정의 */
CAN_HandleTypeDef hcan;

/**
 * @brief CAN1 Initialization Function
 * @details main.c에서 추출된 설정값으로 CAN 주변장치를 초기화합니다.
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_CAN_Init(void)
{
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 16;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_1TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;

  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* 필터 설정 적용 */
  HW_CAN_ConfigFilter();

  /* CAN 모듈 시작 */
  if (HAL_CAN_Start(&hcan) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* 수신 인터럽트(FIFO0 메시지 대기) 활성화 */
  if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
 * @brief Configures CAN filters to receive all incoming messages.
 * @note 필터 뱅크 0을 사용하며, 모든 ID를 통과시키도록 마스크를 0으로 설정합니다.
 */
void HW_CAN_ConfigFilter(void)
{
  CAN_FilterTypeDef sFilterConfig;

  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.SlaveStartFilterBank = 14;

  if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
  {
    /* 초기화 실패 시 시스템 에러 핸들러 호출 */
    Error_Handler();
  }
}

/**
 * @brief Transmits a CAN message using Standard ID.
 * @param id Standard CAN ID (11-bit)
 * @param pData Pointer to data buffer (max 8 bytes)
 * @param len Data length code (DLC)
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef HW_CAN_Transmit(uint32_t id, uint8_t *pData, uint8_t len)
{
  CAN_TxHeaderTypeDef TxHeader;
  uint32_t TxMailbox;

  /* 전송 헤더 설정 */
  TxHeader.StdId = id;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.DLC = len;
  TxHeader.TransmitGlobalTime = DISABLE;

  /* 전송 가능한 메일박스가 있는지 확인 후 전송 요청 */
  if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) > 0)
  {
    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, pData, &TxMailbox) != HAL_OK)
    {
      return HAL_ERROR;
    }
    return HAL_OK;
  }

  return HAL_BUSY;
}

/**
 * @brief CAN Rx FIFO 0 message pending callback.
 * @param hcan_ptr CAN handle pointer
 * @note 이 함수는 HAL 드라이버 내부에서 인터럽트 발생 시 호출되는 콜백 함수입니다.
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan_ptr)
{
  CAN_RxHeaderTypeDef RxHeader;
  uint8_t RxData[8];

  /* 수신된 메시지 읽기 */
  if (HAL_CAN_GetRxMessage(hcan_ptr, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
  {
    /* * [SUNG] 수신 데이터 처리 로직을 여기에 구현하세요.
     * 예: if (RxHeader.StdId == CAN_ID_STATUS) { ... }
     */
  }
}
