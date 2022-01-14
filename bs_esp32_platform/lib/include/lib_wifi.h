/*******************************************************************************
* Copyright (c) 2021, Buildstorm Pvt Ltd
*
* Filename:     lib_wifi.h
*
* Author:       Amruta
* email:        amruta@buildstorm.com
*
* Description:
*               Contains wrapper functions to handle WiFi functionalities.
*******************************************************************************/

#ifndef _LIB_WIFI_H_
#define _LIB_WIFI_H_

/* Includes ------------------------------------------------------------------*/

#include "lib_config.h"
#include "stdutils.h"

/* Macros -----------------------------------------------------------------*/

#define ENABLE_WIFI_VERIFICATION TRUE

typedef enum
{
    STATE_WIFI_IDLE,
    STATE_WIFI_SCAN,
    STATE_WIFI_START,
    STATE_WIFI_DISCONNECTED,
    STATE_WIFI_CONNECTED,
    STATE_WIFI_MAX,
} wifiStates_et;

typedef struct
{
    char ssid[LENGTH_WIFI_CRED_SSID];
    char password[LENGTH_WIFI_CRED_PASSWORD];
} wifiCred_st;

/* Function declarations ----------------------------------------------------*/

bool WIFI_isConnected();
char *WIFI_getIpAddress();
uint8_t WIFI_getSignalStrength();
int8_t WIFI_getRssi();
void WIFI_printStatus();
const char *WIFI_getStateString();
uint16_t WIFI_getApList(char *pBuffer);

#endif