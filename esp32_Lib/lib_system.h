/***************************************************************************************************
                                   BuildStorm.com
 ****************************************************************************************************
 * File:   lib_system.h
 * Version: 1.0
 * Author: Saheblal Bagwan
 * Description: Manages the library functnailty.
                - Takes care of initialization of the library modules.
                - System_init has to be called before calling any library modules.
                - System task takes care of hanlding all the library funcationality.
                

Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
A copy of EULA is available for you https://buildstorm.com/eula
**************************************************************************************************/
#ifndef _LIB_SYSTEM_H_
#define _LIB_SYSTEM_H_
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "lib_config.h"
#include "lib_ota.h"
#include "stdutils.h"
#include "lib_device.h"
#include "lib_flash.h"
#include "lib_wifi.h"
#include "lib_aws.h"
#include "lib_jobs.h"
#include "lib_mqtt.h"
#include "lib_ble.h"
#include "lib_menu.h"
#include "lib_gpio.h"

/* Macros -----------------------------------------------------------------*/
#define MS_TO_RTOS_TICKS(x) ((x) / portTICK_PERIOD_MS)
#define TASK_DELAY_MS(x) vTaskDelay(MS_TO_RTOS_TICKS((x) > portTICK_PERIOD_MS ? (x) : portTICK_PERIOD_MS))


 
typedef enum
{
    SYSTEM_MODE_TEST,
    SYSTEM_MODE_NORMAL,
    SYSTEM_MODE_CONFIG,
    SYSTEM_MODE_OTA,
    SYSTEM_MODE_ABORT,
    SYSTEM_MODE_MAX
} systemMode_et;

void SYSTEM_init();
void SYSTEM_setMode(systemMode_et sysMode);
systemMode_et SYSTEM_getMode();
const char* SYSTEM_getModeString();
void SYSTEM_startOta(char *otaUrl);
void SYSTEM_restart(uint32_t waitTime);
void SYSTEM_abort(char *abortMsg, uint32_t errorCode);

uint32_t millis();

#endif