/**
 * \copyright Copyright (c) 2021, Buildstorm Pvt Ltd
 *
 * \file lib_ble.h
 * \brief A BLE library file
 *
 */

#ifndef _LIB_BLE_H_
#define _LIB_BLE_H_

/* Includes ------------------------------------------------------------------*/

#include "lib_utils.h"
#include "lib_config.h"

#define MAX_BLE_USER_PACKETS 2
#define SIZE_BLE_USER_PACKET_NAME 4
#define SIZE_BLE_USER_PACKET_DATA 128

typedef enum
{
    STATE_BLE_IDLE,
    STATE_BLE_DISCONNECTED,
    STATE_BLE_CONNECTED,
    STATE_BLE_AUTHENTICATED,
    STATE_BLE_MAX
} bleState_et;

typedef enum
{
    BLE_OKAY,
    BLE_BUFF_EMPTY,
    BLE_BUFF_EXCEEDS_LIMIT,
    BLE_WRITE_FULL,
    BLE_WRITE_FAILED,
    BLE_DISCONNECTED,
    BLE_ERROR_MAX,
} bleWrtStatus_et;

typedef enum
{
    BLE_RESP_SUCCESS,
    BLE_RESP_IN_PROGRESS,
    BLE_RESP_CONFIG_DONE,
    BLE_RESP_ACCESS_DENIED,
    BLE_RESP_TIMEOUT,
    BLE_RESP_MISSING_ELEMENTS,
    BLE_RESP_WIFI_WRONG_PWD,
    BLE_RESP_WIFI_WRONG_SSID,
    BLE_RESP_INVALID_RQST,
    BLE_RESP_MISSING_PACKETS,
    BLE_RESP_CRC_FAILED,
    BLE_RESP_DEVICE_BUSY,
    BLE_RESP_FAILED_UNKNOWN_REASON,
    BLE_RESP_DEV_REG_RQST = 55,
    BLE_RESP_INVALID_JSON = 99,
} bleResponseCodes_et;

typedef void (*bleCallBack_t)(char *pPacketStr, char *pDataStr);

bool BLE_init();
bool BLE_isConnected();
void BLE_disconnect();
bool BLE_packetRegister(char *pPacketStr, bleCallBack_t callbackHandler);
bleWrtStatus_et BLE_packetSendData(char *pPacketStr, char *pDataStr, uint8_t code_u8);
bleWrtStatus_et BLE_packetSendAck(char *pPacketStr, uint8_t code_u8);
void BLE_printStatus();
const char *BLE_getStateString();
uint32_t BLE_getLastActiveTime();

#endif