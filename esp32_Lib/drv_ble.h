/***************************************************************************************************
                                   BuildStorm.com
 ****************************************************************************************************
 * File:   drv_ble.h
 * Version: 1.0
 * Author: Saheblal Bagwan
 * Description: Contains The API's for BLE driver initialization and BLE read/write.
                

Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
A copy of EULA is available for you https://buildstorm.com/eula
**************************************************************************************************/

#ifndef _DRV_BLE_H_
#define _DRV_BLE_H_

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "esp_system.h"
#include "esp_types.h"
#include "lib_config.h"
//#include "lib_device.h"
//#include "lib_crc8.h"


#include "nimble/ble.h"
#include "modlog/modlog.h"

typedef struct{
 uint8_t eventId_u8;
 uint8_t connHandle_u8;
 uint8_t charHandle_u8;
 uint8_t *dataPtr;
 uint8_t len_u8; 
}bleDrvEventData_st;

typedef enum{
    EVT_DRV_BLE_DISCONNECT,
    EVT_DRV_BLE_CONNECT,
    EVT_DRV_BLE_RX_DATA,
    EVT_DRV_BLE_MAX
}bleDrvEvents_et;

typedef enum
{
    BLE_CHAR_AUTH,
    BLE_CHAR_CONFIG,
    BLE_CHAR_STATUS,
    BLE_CHAR_DATA,
    BLE_CHAR_MAX
} bleChars_et;

typedef struct{
  uint8_t charHandle_u8;
  uint8_t connHandle_u8;
  uint8_t dataPtr[18];
  uint8_t dataLen_u8;
}bleDrvPacket_st;

struct ble_hs_cfg;
struct ble_gatt_register_ctxt;

/** GATT server. */
#define GATT_SVR_SVC_ALERT_UUID 0x1811
#define GATT_SVR_CHR_SUP_NEW_ALERT_CAT_UUID 0x2A47
#define GATT_SVR_CHR_NEW_ALERT 0x2A46
#define GATT_SVR_CHR_SUP_UNR_ALERT_CAT_UUID 0x2A48
#define GATT_SVR_CHR_UNR_ALERT_STAT_UUID 0x2A45
#define GATT_SVR_CHR_ALERT_NOT_CTRL_PT 0x2A44

typedef void (*bleDrvEventCb_t)(bleDrvEventData_st *drvEvent);

void ble_drvInit();
void ble_drvRegisterCallBack(bleDrvEventCb_t);
void ble_drvStartAdv();
void ble_drvStopAdv();
void ble_drvDisconnect();
int ble_drvWrite(bleDrvEventData_st *drvPkt_ps);

#endif