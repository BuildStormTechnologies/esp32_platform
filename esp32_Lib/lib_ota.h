/***************************************************************************************************
                                   BuildStorm.com
 ****************************************************************************************************
*
* Filename:     lib_ota.h
*
* Author:       Amruta
* email:        amruta@buildstorm.com
*
* Description:
*               Contains wrapper functions to handle OTA functionalities.

Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
A copy of EULA is available for you https://buildstorm.com/eula
**************************************************************************************************/

#ifndef _LIB_OTA_H_
#define _LIB_OTA_H_

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include "esp_system.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_err.h"
#include "lwip/inet.h"
#include "lwip/ip_addr.h"
#include "lwip/ip4_addr.h"
#include "lwip/dns.h"
#include "lib_config.h"
#include "lib_flash.h"
#include "lib_wifi.h"


typedef enum
{
    OTA_STATUS_READY,
    OTA_STATUS_STARTED,
    OTA_STATUS_SUCCESSFULL,
    OTA_STATUS_RECEIVE_DATA_ERROR,
    OTA_STATUS_HTTP_CREAT_SERVER_FAILED,
    OTA_STATUS_HTTP_INIT_CONNECT_FAILED,
    OTA_STATUS_HTTP_OPEN_CONNECT_FAILED,
    OTA_STATUS_WRITE_FAILED,
    OTA_STATUS_BEGIN_FAILED,
    OTA_STATUS_END_FAILED,
    OTA_STATUS_NO_PACKET,
    OTA_STATUS_SET_PARTITION_FAILED,
    OTA_STATUS_FAILED_UNKOWN_REASON,
    OTA_STATUS_MAX
} otaStatus_et;

typedef enum
{
    OTA_MODE_WEB,
    OTA_MODE_LOCAL,
    OTA_MODE_MAX
} otaMode_et;

typedef struct
{
    esp_err_t error;
    otaStatus_et status;
    uint8_t previousPartition;
} otaStruct_st;

typedef enum
{
    STATE_OTA_IDLE,
    STATE_OTA_INIT,
    STATE_OTA_HTTP_CONNECT,
    STATE_OTA_BEGIN,
    STATE_OTA_IN_PROGRESS,
    STATE_OTA_SUCCESS,
    STATE_OTA_FAILED,
    STATE_OTA_MAX
} otaState_et;

/* Macros -----------------------------------------------------------------*/
#define OTA_LISTEN_PORT 8032
#define OTA_BUFFER_SIZE 1024
#define OTA_REQUEST_SIZE 200
#define TCP_SERVER_LISTENQ 2
#define OTA_SERVER_HEADER "Accept: */*\r\n"              \
                          "Content-Length: 0\r\n"        \
                          "Content-Type: text/plain\r\n" \
                          "Connection: Closed\r\n\r\n"

/*---------------------------structures-------------------------------------*/

/* Function declarations ----------------------------------------------------*/
void OTA_sync();
uint8_t OTA_getCurrentPartition();
uint8_t OTA_getMode();
void OTA_setMode(uint8_t);
void OTA_setUrl(char *);
const char *OTA_getOtaStatusStr(otaStatus_et status);
otaStatus_et OTA_getCurrentOtaStatus();
otaState_et OTA_getState();

#endif