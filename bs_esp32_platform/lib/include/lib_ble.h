#ifndef _LIB_BLE_H_
#define _LIB_BLE_H_

/* Includes ------------------------------------------------------------------*/

#include "lib_utils.h"
#include "lib_config.h"


#define MAX_BLE_USER_PACKETS 2
#define SIZE_BLE_USER_PACKET_NAME 4

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

typedef void (*bleCallBack_t)(char *pPacketStr, char *pDataStr);

bool BLE_init();
bool BLE_isConnected();
void BLE_disconnect();
bleWrtStatus_et BLE_write(char *pDataStr);
bool BLE_packetRegister(char *pPacketStr, bleCallBack_t callbackHandler);
void BLE_printStatus();
const char *BLE_getStateString();
uint32_t BLE_getLastActiveTime();

#endif