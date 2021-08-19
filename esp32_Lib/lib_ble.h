/***************************************************************************************************
                                   BuildStorm.com
 ****************************************************************************************************
 * File:   lib_ble.h
 * Version: 1.0
 * Author: Saheblal Bagwan
 * Description: Contains The API's for application BLE read/write.
                1. It handles the authentication.
                2. BLE packeting
                3. Json support for device configuration
                

Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
A copy of EULA is available for you https://buildstorm.com/eula
**************************************************************************************************/
#ifndef _LIB_BLE_H_
#define _LIB_BLE_H_

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "esp_system.h"
#include "esp_types.h"
#include "lib_config.h"
#include "lib_device.h"
#include "lib_crc8.h"
#include "drv_ble.h"

#include <stdbool.h>
#include "nimble/ble.h"
#include "modlog/modlog.h"

struct ble_hs_cfg;
struct ble_gatt_register_ctxt;

typedef enum{
 STATE_BLE_IDLE,
 STATE_BLE_DISCONNECTED,   
 STATE_BLE_CONNECTED,
 STATE_BLE_AUTHENTICATED,
 STATE_BLE_MAX
}bleStatus_et;

typedef enum
{
    BLE_OKAY,
    BLE_READ_EMPTY,
    BLE_WRITE_FULL,
    BLE_ERROR_MAX,
} bleWrtStatus_et;



typedef enum
{
    PKT_INDEX_START_ = 0,
    PKT_INDEX_DATA = 1,
    PKT_INDEX_CRC = 17,
    PKT_INDEX_MAX = PKT_INDEX_CRC + 1
} packetIndex_et;

typedef enum
{
    PKT_STATE_IDLE,
    PKT_STATE_START,
    PKT_STATE_PROCESSING,
    PKT_STATE_DONE
} packetState_et;

typedef struct
{
    uint8_t byte[PKT_INDEX_MAX];
} pkt_st;

typedef struct
{
    uint16_t index_u16;
    uint16_t len_u16;
    uint8_t bleChar_u8;
    uint8_t pktId_u8;
    uint8_t state_u8;
    uint8_t data[BLE_PAYLOAD_SIZE_MAX];
} packetHandle_st;

typedef enum
{
   BLE_RESP_SUCCESS,
   BLE_RESP_DEV_CONFIG_IN_PROGRESS,
   BLE_RESP_DEV_CONFIG_DONE,
   BLE_RESP_ACCESS_DENIED,
   BLE_RESP_TIMEOUT,
   BLE_RESP_MISSING_ELEMENTS,
   BLE_RESP_WIFI_WRONG_PWD,
   BLE_RESP_WIFI_WRONG_SSID,
   BLE_RESP_OTA_IN_PROGRESS,
   BLE_RESP_OTA_FIRMWARE_VERSION_SAME,
   BLE_RESP_OTA_INVALID_VERSION,
   BLE_RESP_OTA_INVALID_URL,
   BLE_RESP_OTA_SUCCESS,
   BLE_RESP_OTA_FAILED,
   BLE_RESP_INVALID_RQST,
   BLE_RESP_DEV_REG_RQST=55,
   BLE_RESP_INVALID_JSON = 99,
}bleResponseCodes_et;


void BLE_init();
void BLE_sync();
bool BLE_isConnected();
bool BLE_isRunning();
void BLE_disconnect();
bleWrtStatus_et BLE_Write(bleChars_et bleChar, char *sendBuff);
void BLE_printStatus();
const char *BLE_stateString();
#endif