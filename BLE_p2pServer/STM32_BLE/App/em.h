/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    EM.h
  * @author  MCD Application Team
  * @brief   Header for EM.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef EM_H
#define EM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ble_status.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported defines ----------------------------------------------------------*/
/* USER CODE BEGIN ED */

/* USER CODE END ED */

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  EM_RQ,
  EM_RS,

  /* USER CODE BEGIN Service2_CharOpcode_t */

  /* USER CODE END Service2_CharOpcode_t */

  EM_CHAROPCODE_LAST
} EM_CharOpcode_t;

typedef enum
{
  EM_RQ_WRITE_NO_RESP_EVT,
  EM_RS_NOTIFY_ENABLED_EVT,
  EM_RS_NOTIFY_DISABLED_EVT,

  /* USER CODE BEGIN Service2_OpcodeEvt_t */

  /* USER CODE END Service2_OpcodeEvt_t */

  EM_BOOT_REQUEST_EVT
} EM_OpcodeEvt_t;

typedef struct
{
  uint8_t *p_Payload;
  uint8_t Length;

  /* USER CODE BEGIN Service2_Data_t */

  /* USER CODE END Service2_Data_t */

} EM_Data_t;

typedef struct
{
  EM_OpcodeEvt_t       EvtOpcode;
  EM_Data_t             DataTransfered;
  uint16_t                ConnectionHandle;
  uint16_t                AttributeHandle;
  uint8_t                 ServiceInstance;

  /* USER CODE BEGIN Service2_NotificationEvt_t */

  /* USER CODE END Service2_NotificationEvt_t */

} EM_NotificationEvt_t;

/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macros -----------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions ------------------------------------------------------- */
void EM_Init(void);
void EM_Notification(EM_NotificationEvt_t *p_Notification);
tBleStatus EM_UpdateValue(EM_CharOpcode_t CharOpcode, EM_Data_t *pData);
tBleStatus EM_NotifyValue(EM_CharOpcode_t CharOpcode, EM_Data_t *pData, uint16_t ConnectionHandle);
/* USER CODE BEGIN EF */

/* USER CODE END EF */

#ifdef __cplusplus
}
#endif

#endif /*EM_H */
