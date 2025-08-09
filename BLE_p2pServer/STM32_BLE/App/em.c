/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    EM.c
  * @author  MCD Application Team
  * @brief   EM definition.
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

/* Includes ------------------------------------------------------------------*/
#include <app_common.h>
#include "ble.h"
#include "em.h"
#include "em_app.h"
#include "ble_evt.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

typedef struct{
  uint16_t  EmSvcHdle;				/**< Em Service Handle */
  uint16_t  RqCharHdle;			/**< RQ Characteristic Handle */
  uint16_t  RsCharHdle;			/**< RS Characteristic Handle */
/* USER CODE BEGIN Context */
  /* Place holder for Characteristic Descriptors Handle*/

/* USER CODE END Context */
}EM_Context_t;

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private macros ------------------------------------------------------------*/
#define CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET        2
#define CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET             1
#define RQ_SIZE        128	/* Request Characteristic size */
#define RS_SIZE        128	/* Response Characteristic size */
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

static EM_Context_t EM_Context;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
/* USER CODE BEGIN PFD */

/* USER CODE END PFD */

/* Private functions ----------------------------------------------------------*/

/*
 * UUIDs for Energy Meter service
 */
#define EM_UUID			0x8f,0xe5,0xb3,0xd5,0x2e,0x7f,0x4a,0x98,0x2a,0x48,0x7a,0xcc,0x40,0xee,0x00,0x00
#define RQ_UUID			0x19,0xed,0x82,0xae,0xed,0x21,0x4c,0x9d,0x41,0x45,0x22,0x8e,0x41,0xee,0x00,0x00
#define RS_UUID			0x19,0xed,0x82,0xae,0xed,0x21,0x4c,0x9d,0x41,0x45,0x22,0x8e,0x42,0xee,0x00,0x00

BLE_GATT_SRV_CCCD_DECLARE(rs, CFG_BLE_NUM_RADIO_TASKS, BLE_GATT_SRV_CCCD_PERM_DEFAULT,
                          BLE_GATT_SRV_OP_MODIFIED_EVT_ENABLE_FLAG);

/* USER CODE BEGIN DESCRIPTORS DECLARATION */

/* USER CODE END DESCRIPTORS DECLARATION */

uint8_t rq_val_buffer[RQ_SIZE];

static ble_gatt_val_buffer_def_t rq_val_buffer_def = {
  .op_flags = BLE_GATT_SRV_OP_MODIFIED_EVT_ENABLE_FLAG | BLE_GATT_SRV_OP_VALUE_VAR_LENGTH_FLAG,
  .val_len = RQ_SIZE,
  .buffer_len = sizeof(rq_val_buffer),
  .buffer_p = rq_val_buffer
};

uint8_t rs_val_buffer[RS_SIZE];

static ble_gatt_val_buffer_def_t rs_val_buffer_def = {
  .op_flags = BLE_GATT_SRV_OP_MODIFIED_EVT_ENABLE_FLAG | BLE_GATT_SRV_OP_VALUE_VAR_LENGTH_FLAG,
  .val_len = RS_SIZE,
  .buffer_len = sizeof(rs_val_buffer),
  .buffer_p = rs_val_buffer
};

/* Energy Meter service RQ (write without response), RS (notification) characteristics definition */
static const ble_gatt_chr_def_t em_chars[] = {
	{
        .properties = BLE_GATT_SRV_CHAR_PROP_WRITE_NO_RESP,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .min_key_size = 0x10,
        .uuid = BLE_UUID_INIT_128(RQ_UUID),
        .val_buffer_p = &rq_val_buffer_def
    },
	{
        .properties = BLE_GATT_SRV_CHAR_PROP_NOTIFY,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .min_key_size = 0x10,
        .uuid = BLE_UUID_INIT_128(RS_UUID),
        .descrs = {
            .descrs_p = &BLE_GATT_SRV_CCCD_DEF_NAME(rs),
            .descr_count = 1U,
        },
        .val_buffer_p = &rs_val_buffer_def
    },
};

/* Energy Meter service definition */
static const ble_gatt_srv_def_t em_service = {
   .type = BLE_GATT_SRV_PRIMARY_SRV_TYPE,
   .uuid = BLE_UUID_INIT_128(EM_UUID),
   .chrs = {
       .chrs_p = (ble_gatt_chr_def_t *)em_chars,
       .chr_count = 2U,
   },
};

/* USER CODE BEGIN PF */

/* USER CODE END PF */

/**
 * @brief  Event handler
 * @param  p_Event: Address of the buffer holding the p_Event
 * @retval Ack: Return whether the p_Event has been managed or not
 */
static BLEEVT_EvtAckStatus_t EM_EventHandler(aci_blecore_event *p_evt)
{
  BLEEVT_EvtAckStatus_t return_value = BLEEVT_NoAck;
  aci_gatt_srv_attribute_modified_event_rp0 *p_attribute_modified;
  aci_gatt_srv_write_event_rp0   *p_write;
  EM_NotificationEvt_t notification;
  /* USER CODE BEGIN Service2_EventHandler_1 */

  /* USER CODE END Service2_EventHandler_1 */

  switch(p_evt->ecode)
  {
    case ACI_GATT_SRV_ATTRIBUTE_MODIFIED_VSEVT_CODE:
    {
      /* USER CODE BEGIN EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_BEGIN */

      /* USER CODE END EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_BEGIN */
      p_attribute_modified = (aci_gatt_srv_attribute_modified_event_rp0*)p_evt->data;
      notification.ConnectionHandle         = p_attribute_modified->Connection_Handle;
      notification.AttributeHandle          = p_attribute_modified->Attr_Handle;
      notification.DataTransfered.Length    = p_attribute_modified->Attr_Data_Length;
      notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
      if(p_attribute_modified->Attr_Handle == (EM_Context.RsCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
      {
        return_value = BLEEVT_Ack;
        /* USER CODE BEGIN Service2_Char_2 */

        /* USER CODE END Service2_Char_2 */
        switch(p_attribute_modified->Attr_Data[0])
		{
          /* USER CODE BEGIN Service2_Char_2_attribute_modified */

          /* USER CODE END Service2_Char_2_attribute_modified */

          /* Disabled Notification management */
        case (!BLE_GATT_SRV_CCCD_NOTIFICATION):
          /* USER CODE BEGIN Service2_Char_2_Disabled_BEGIN */

          /* USER CODE END Service2_Char_2_Disabled_BEGIN */
          notification.EvtOpcode = EM_RS_NOTIFY_DISABLED_EVT;
          EM_Notification(&notification);
          /* USER CODE BEGIN Service2_Char_2_Disabled_END */

          /* USER CODE END Service2_Char_2_Disabled_END */
          break;

          /* Enabled Notification management */
        case BLE_GATT_SRV_CCCD_NOTIFICATION:
          /* USER CODE BEGIN Service2_Char_2_COMSVC_Notification_BEGIN */

          /* USER CODE END Service2_Char_2_COMSVC_Notification_BEGIN */
          notification.EvtOpcode = EM_RS_NOTIFY_ENABLED_EVT;
          EM_Notification(&notification);
          /* USER CODE BEGIN Service2_Char_2_COMSVC_Notification_END */

          /* USER CODE END Service2_Char_2_COMSVC_Notification_END */
          break;

        default:
          /* USER CODE BEGIN Service2_Char_2_default */

          /* USER CODE END Service2_Char_2_default */
          break;
        }
      }  /* if(p_attribute_modified->Attr_Handle == (EM_Context.RsCharHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/

      else if(p_attribute_modified->Attr_Handle == (EM_Context.RqCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
      {
        return_value = BLEEVT_Ack;

        notification.EvtOpcode = EM_RQ_WRITE_NO_RESP_EVT;
        /* USER CODE BEGIN Service2_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
        APP_DBG_MSG("-- GATT : MODBUS CONFIGURATION RECEIVED\n");
               notification.DataTransfered.Length = p_attribute_modified->Attr_Data_Length;
               notification.DataTransfered.p_Payload = p_attribute_modified->Attr_Data;
        /* USER CODE END Service2_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
        EM_Notification(&notification);
      } /* if(p_attribute_modified->Attr_Handle == (EM_Context.RqCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/

      /* USER CODE BEGIN EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_END */

      /* USER CODE END EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_END */
      break;/* ACI_GATT_SRV_ATTRIBUTE_MODIFIED_VSEVT_CODE */
    }
    case ACI_GATT_SRV_READ_VSEVT_CODE :
    {
      /* USER CODE BEGIN EVT_BLUE_GATT_SRV_READ_BEGIN */

      /* USER CODE END EVT_BLUE_GATT_SRV_READ_BEGIN */

      /* USER CODE BEGIN EVT_BLUE_GATT_SRV_READ_END */

      /* USER CODE END EVT_EVT_BLUE_GATT_SRV_READ_END */
      break;/* ACI_GATT_SRV_READ_VSEVT_CODE */
    }
    case ACI_GATT_SRV_WRITE_VSEVT_CODE:
    {
      /* USER CODE BEGIN EVT_BLUE_SRV_GATT_BEGIN */

      /* USER CODE END EVT_BLUE_SRV_GATT_BEGIN */
      p_write = (aci_gatt_srv_write_event_rp0*)p_evt->data;
      if(p_write->Attribute_Handle == (EM_Context.RqCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
      {
        return_value = BLEEVT_Ack;
        /*USER CODE BEGIN Service2_Char_1_ACI_GATT_SRV_WRITE_VSEVT_CODE */
//#warning user shall call aci_gatt_srv_write_resp() function if allowed
        /*USER CODE END Service2_Char_1_ACI_GATT_SRV_WRITE_VSEVT_CODE*/
      } /*if(p_write->Attribute_Handle == (EM_Context.RqCharHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/

      /* USER CODE BEGIN EVT_BLUE_GATT_SRV_WRITE_END */

      /* USER CODE END EVT_BLUE_GATT_SRV_WRITE_END */
      break;/* ACI_GATT_SRV_WRITE_VSEVT_CODE */
    }
    case ACI_GATT_TX_POOL_AVAILABLE_VSEVT_CODE:
    {
      aci_gatt_tx_pool_available_event_rp0 *p_tx_pool_available_event;
      p_tx_pool_available_event = (aci_gatt_tx_pool_available_event_rp0 *) p_evt->data;
      UNUSED(p_tx_pool_available_event);

      /* USER CODE BEGIN ACI_GATT_TX_POOL_AVAILABLE_VSEVT_CODE */

      /* USER CODE END ACI_GATT_TX_POOL_AVAILABLE_VSEVT_CODE */
      break;/* ACI_GATT_TX_POOL_AVAILABLE_VSEVT_CODE*/
    }
    case ACI_ATT_EXCHANGE_MTU_RESP_VSEVT_CODE:
    {
      aci_att_exchange_mtu_resp_event_rp0 *p_exchange_mtu;
      p_exchange_mtu = (aci_att_exchange_mtu_resp_event_rp0 *)  p_evt->data;
      UNUSED(p_exchange_mtu);

      /* USER CODE BEGIN ACI_ATT_EXCHANGE_MTU_RESP_VSEVT_CODE */

      /* USER CODE END ACI_ATT_EXCHANGE_MTU_RESP_VSEVT_CODE */
      break;/* ACI_ATT_EXCHANGE_MTU_RESP_VSEVT_CODE */
    }
    /* USER CODE BEGIN BLECORE_EVT */

    /* USER CODE END BLECORE_EVT */
  default:
    /* USER CODE BEGIN EVT_DEFAULT */

    /* USER CODE END EVT_DEFAULT */
    break;
  }

  /* USER CODE BEGIN Service2_EventHandler_2 */

  /* USER CODE END Service2_EventHandler_2 */

  return(return_value);
}/* end EM_EventHandler */

/* Public functions ----------------------------------------------------------*/

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void EM_Init(void)
{
  tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
  UNUSED(EM_Context);

  /* USER CODE BEGIN InitService2Svc_1 */

  /* USER CODE END InitService2Svc_1 */

  /**
   *  Register the event handler to the BLE controller
   */
  BLEEVT_RegisterGattEvtHandler(EM_EventHandler);

  ret = aci_gatt_srv_add_service((ble_gatt_srv_def_t *)&em_service);

  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail   : aci_gatt_srv_add_service command: EM, error code: 0x%x \n", ret);
  }
  else
  {
    APP_DBG_MSG("  Success: aci_gatt_srv_add_service command: EM \n");
  }

  EM_Context.EmSvcHdle = aci_gatt_srv_get_service_handle((ble_gatt_srv_def_t *) &em_service);
  EM_Context.RqCharHdle = aci_gatt_srv_get_char_decl_handle((ble_gatt_chr_def_t *)&em_chars[0]);
  EM_Context.RsCharHdle = aci_gatt_srv_get_char_decl_handle((ble_gatt_chr_def_t *)&em_chars[1]);

  /* USER CODE BEGIN InitService1Svc_2 */

  /* USER CODE END InitService1Svc_2 */

  if (ret != BLE_STATUS_SUCCESS)
  {
    APP_DBG_MSG("  Fail registering EM handlers\n");
  }

  return;
}

/**
 * @brief  Characteristic update
 * @param  CharOpcode: Characteristic identifier
 * @param  pData: pointer to the new data to be written in the characteristic
 *
 */
tBleStatus EM_UpdateValue(EM_CharOpcode_t CharOpcode, EM_Data_t *pData)
{
  tBleStatus ret = BLE_STATUS_SUCCESS;

  /* USER CODE BEGIN Service2_App_Update_Char_1 */

  /* USER CODE END Service2_App_Update_Char_1 */

  switch(CharOpcode)
  {
    case EM_RQ:
      memcpy(rq_val_buffer, pData->p_Payload, MIN(pData->Length, sizeof(rq_val_buffer)));
      /* USER CODE BEGIN Service2_Char_Value_1*/

      /* USER CODE END Service2_Char_Value_1*/
      break;

    default:
      break;
  }

  /* USER CODE BEGIN Service2_App_Update_Char_2 */

  /* USER CODE END Service2_App_Update_Char_2 */

  return ret;
}

/**
 * @brief  Characteristic notification
 * @param  CharOpcode: Characteristic identifier
 * @param  pData: pointer to the data to be notified to the client
 * @param  ConnectionHandle: connection handle identifying the client to be notified.
 *
 */
tBleStatus EM_NotifyValue(EM_CharOpcode_t CharOpcode, EM_Data_t *pData, uint16_t ConnectionHandle)
{
  tBleStatus ret = BLE_STATUS_INVALID_PARAMS;
  /* USER CODE BEGIN Service2_App_Notify_Char_1 */

  /* USER CODE END Service2_App_Notify_Char_1 */

  switch(CharOpcode)
  {

    case EM_RS:
      memcpy(rs_val_buffer, pData->p_Payload, MIN(pData->Length, sizeof(rs_val_buffer)));
      ret = aci_gatt_srv_notify(ConnectionHandle,
                                BLE_GATT_UNENHANCED_ATT_L2CAP_CID,
                                EM_Context.RsCharHdle + 1,
                                GATT_NOTIFICATION,
                                pData->Length, /* charValueLen */
                                (uint8_t *)pData->p_Payload);
      if (ret != BLE_STATUS_SUCCESS)
      {
        APP_DBG_MSG("  Fail   : aci_gatt_srv_notify RS command, error code: 0x%2X\n", ret);
      }
      else
      {
        APP_DBG_MSG("  Success: aci_gatt_srv_notify RS command\n");
      }
      /* USER CODE BEGIN Service2_Char_Value_2*/

      /* USER CODE END Service2_Char_Value_2*/
      break;

    default:
      break;
  }

  /* USER CODE BEGIN Service2_App_Notify_Char_2 */

  /* USER CODE END Service2_App_Notify_Char_2 */

  return ret;
}
