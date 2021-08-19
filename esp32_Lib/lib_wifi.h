/***************************************************************************************************
                                   BuildStorm.com
 ****************************************************************************************************
*
* Filename:     lib_wifi.h
*
* Author:       Amruta
* email:        amruta@buildstorm.com
*
* Description:
*               Contains wrapper functions to handle WiFi functionalities.
                
Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
A copy of EULA is available for you https://buildstorm.com/eula
**************************************************************************************************/

#ifndef _LIB_WIFI_H_
#define _LIB_WIFI_H_

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "lib_config.h"
#include "stdutils.h"
#include "lib_device.h"
#include "lib_flash.h"
#include "lib_defines.h"

/* Macros -----------------------------------------------------------------*/
typedef enum
{
    STATE_WIFI_IDLE,
    STATE_WIFI_DISCONNECTED,
    STATE_WIFI_CONNECTED,
    STATE_WIFI_WRONG_PWD,
    STATE_WIFI_WRONG_SSID,
    STATE_WIFI_MAX,
} wifiStates_et;

typedef struct
{
    char ssid[LENGTH_WIFI_CRED_SSID];
    char password[LENGTH_WIFI_CRED_PASSWORD];
} wifiCred_st;


/* Function declarations ----------------------------------------------------*/

void WIFI_init(char *ssidPtr, char *pwdPtr);
void WIFI_start(void);
void WIFI_stop();
void WIFI_restart();
bool WIFI_isConnected();
char *WIFI_getIpAddress();
uint16_t WIFI_getApList(char *buff);
uint8_t WIFI_getSignalStrength();
void WIFI_sync();
void WIFI_printStatus();
const char* WIFI_stateString();

#endif