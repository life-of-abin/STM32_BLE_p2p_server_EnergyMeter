/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    em_app.c
  * @author  Your Name / MCD Application Team
  * @brief   EM_app application definition - BLE RS485 Modbus server.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed as AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_common.h"
#include "app_ble.h"
#include "ble.h"
#include "em_app.h"
#include "em.h"
#include "stm32_seq.h"
#include <string.h> // for memcpy

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

typedef enum
{
  Rs_NOTIFICATION_OFF,
  Rs_NOTIFICATION_ON,
  /* USER CODE BEGIN Service2_APP_SendInformation_t */

  /* USER CODE END Service2_APP_SendInformation_t */
  EM_APP_SENDINFORMATION_LAST
} EM_APP_SendInformation_t;

typedef struct
{
  EM_APP_SendInformation_t     Rs_Notification_Status;
  /* USER CODE BEGIN Service2_APP_Context_t */

  /* USER CODE END Service2_APP_Context_t */
  uint16_t              ConnectionHandle;
} EM_APP_Context_t;

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint8_t request[256] = {0};
uint16_t reqLen =0;
static void modbusProcess(void);
static void notifyBleTask(void);

/* USER CODE END PD */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */
extern UART_HandleTypeDef hlpuart1;
/* USER CODE END EV */

/* Private macros ------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
static EM_APP_Context_t EM_APP_Context;
uint8_t a_EM_UpdateCharData[247];  // Max payload buffer
static EM_Data_t bleNotifyData;     // Buffer for BLE notify data

/* Private function prototypes -----------------------------------------------*/
static void EM_Rs_SendNotification(void);
static uint16_t Modbus_CRC16(uint8_t *buffer, uint16_t length);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/

/* Modbus CRC16 calculation function */
static uint16_t Modbus_CRC16(uint8_t *buffer, uint16_t length)
{
  uint16_t crc = 0xFFFF;
  for (uint16_t pos = 0; pos < length; pos++)
  {
    crc ^= (uint16_t)buffer[pos];
    for (int i = 8; i != 0; i--)
    {
      if ((crc & 0x0001) != 0)
      {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
      {
        crc >>= 1;
      }
    }
  }
  return crc;
}


/**
 * @brief Handle BLE notifications and process incoming Modbus RTU requests dynamically.
 *
 * Assumptions:
 * - The incoming request (p_Notification->DataTransfered.p_Payload) contains:
 *   Slave Addr(1) + Function Code(1) + Starting Addr(2) + Register Count(2)
 * - Length of incoming payload is at least 6 bytes.
 * - You want to send this request over RS485 with appended CRC.
 * - Then receive response dynamically based on requested register count.
 */
void EM_Notification(EM_NotificationEvt_t *p_Notification)
{
  switch(p_Notification->EvtOpcode)
  {
    case EM_RQ_WRITE_NO_RESP_EVT:
      APP_DBG_MSG("-- EM_RQ_WRITE_NO_RESP_EVT\n");
      for(uint8_t i=0; i < p_Notification->DataTransfered.Length; i++) {
        APP_DBG_MSG("%02X ", p_Notification->DataTransfered.p_Payload[i]);
        request[i]=p_Notification->DataTransfered.p_Payload[i];
      }
      APP_DBG_MSG("\n");
      reqLen= p_Notification->DataTransfered.Length;

      // Schedule Modbus processing task
      UTIL_SEQ_SetTask( 1<<CFG_TASK_MODBUS_ID, CFG_SEQ_PRIO_0);
      break;

    case EM_RS_NOTIFY_ENABLED_EVT:
      // Optional: handle notification enable event
      EM_APP_Context.Rs_Notification_Status = Rs_NOTIFICATION_ON;
      break;

    case EM_RS_NOTIFY_DISABLED_EVT:
      // Optional: handle notification disable event
      EM_APP_Context.Rs_Notification_Status = Rs_NOTIFICATION_OFF;
      break;

    default:
      break;
  }
  return;
}

void EM_APP_EvtRx(EM_APP_ConnHandleNotEvt_t *p_Notification)
{
  switch(p_Notification->EvtOpcode)
  {
    case EM_CONN_HANDLE_EVT:
      EM_APP_Context.ConnectionHandle = p_Notification->ConnectionHandle;
      break;

    case EM_DISCON_HANDLE_EVT:
      EM_APP_Context.ConnectionHandle = 0xFFFF;
      break;

    default:
      break;
  }
  return;
}

void EM_APP_Init(void)
{
  EM_APP_Context.ConnectionHandle = 0xFFFF;
  EM_Init();

  UTIL_SEQ_RegTask( 1U << CFG_TASK_MODBUS_ID, UTIL_SEQ_RFU, modbusProcess);
  UTIL_SEQ_RegTask( 1U << CFG_TASK_NOTIFY_BLE_ID, UTIL_SEQ_RFU, notifyBleTask);

  return;
}

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/
__USED void EM_Rs_SendNotification(void)
{
  EM_APP_SendInformation_t notification_on_off = EM_APP_Context.Rs_Notification_Status;
  EM_Data_t em_notification_data;

  em_notification_data.p_Payload = (uint8_t*)a_EM_UpdateCharData;
  em_notification_data.Length = 0;

  if (notification_on_off != Rs_NOTIFICATION_OFF && EM_APP_Context.ConnectionHandle != 0xFFFF)
  {
    EM_NotifyValue(EM_RS, &em_notification_data, EM_APP_Context.ConnectionHandle);
  }
  return;
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS*/
static void modbusProcess(void)
{
    // Append CRC16 at the end of request (2 bytes)
    uint16_t crc = Modbus_CRC16(request, reqLen);
    request[reqLen] = crc & 0xFF;           // CRC Low byte
    request[reqLen + 1] = (crc >> 8) & 0xFF; // CRC High byte
    reqLen += 2; // Now total request length including CRC

    // Debug print full request with CRC
    APP_DBG_MSG("RS485 Request: ");
    for (int i = 0; i < reqLen; i++)
      APP_DBG_MSG("%02X ", request[i]);
    APP_DBG_MSG("\n");

    // Send request via UART RS485
    if (HAL_UART_Transmit(&hlpuart1, request, reqLen, 1000) == HAL_OK)
    {
      APP_DBG_MSG("RS485 Request Sent\n");
    }
    else
    {
      APP_DBG_MSG("RS485 Transmit Error\n");
    }

    // Calculate expected response length dynamically:
    // Typical Modbus RTU Read Holding Registers response:
    // Byte 0: Slave Address
    // Byte 1: Function Code (0x03)
    // Byte 2: Byte count = RegisterCount * 2
    // Bytes 3..N: Data bytes (RegisterCount * 2 bytes)
    // Last 2 bytes: CRC16

    // Extract number of registers requested
    uint16_t registerCount = ((uint16_t)request[4] << 8) | request[5];
    uint16_t respLen = 5 + (registerCount * 2);  // 1+1+1+data+2 CRC = 5 + N*2

    // Sanity check on register count to avoid large buffer overflow
    if (registerCount == 0 || registerCount > 120) // Modbus max registers at once ~125
    {
      APP_DBG_MSG("Invalid Register Count: %d\n", registerCount);
      return;
    }

    // Buffer for response
    uint8_t response[256] = {0};

    // Receive response (blocking with timeout)
    if (HAL_UART_Receive(&hlpuart1, response, respLen, 1000) == HAL_OK)
    {
      APP_DBG_MSG("RS485 Response: ");
      for (int i = 0; i < respLen; i++)
        APP_DBG_MSG("%02X ", response[i]);
      APP_DBG_MSG("\n");

      // CRC check on response
      uint16_t rx_crc = (response[respLen - 1] << 8) | response[respLen - 2];
      uint16_t calc_crc = Modbus_CRC16(response, respLen - 2);

      if (rx_crc == calc_crc)
      {
        APP_DBG_MSG("CRC OK\n");

        // Copy the data bytes part (starting from byte 3, length = registerCount * 2)
        if ((registerCount * 2) <= sizeof(a_EM_UpdateCharData))
        {
          memcpy(a_EM_UpdateCharData, &response[3], registerCount * 2);

          bleNotifyData.p_Payload = a_EM_UpdateCharData;
          bleNotifyData.Length = registerCount * 2;

          // Schedule BLE notify task
          UTIL_SEQ_SetTask(1U << CFG_TASK_NOTIFY_BLE_ID, CFG_SEQ_PRIO_0);
        }
        else
        {
          APP_DBG_MSG("Data too large for BLE buffer\n");
        }
      }
      else
      {
        APP_DBG_MSG("CRC Error\n");
      }
    }
    else
    {
      APP_DBG_MSG("RS485 Receive Timeout/Error\n");
    }
}

static void notifyBleTask(void)
{
    if (EM_APP_Context.Rs_Notification_Status == Rs_NOTIFICATION_ON &&
        EM_APP_Context.ConnectionHandle != 0xFFFF)
    {
        tBleStatus status = EM_NotifyValue(EM_RS, &bleNotifyData, EM_APP_Context.ConnectionHandle);
        APP_DBG_MSG("BLE Notify Status: 0x%02X\n", status);
    }
    else
    {
        APP_DBG_MSG("Notification disabled or no BLE connection\n");
    }
}
/* USER CODE END FD_LOCAL_FUNCTIONS*/
