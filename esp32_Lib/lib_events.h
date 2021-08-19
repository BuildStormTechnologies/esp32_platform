/***************************************************************************************************
                                   BuildStorm.com
****************************************************************************************************
* Filename:     lib_events.h
*
* Author:       Amruta
* email:        amruta@buildstorm.com
*
* Description:
*               Contains wrapper functions to handle events functionalities.

* Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

* The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
* A copy of EULA is available for you https://buildstorm.com/eula
*****************************************************************************************************/

#ifndef _LIB_EVENTS_H_
#define _LIB_EVENTS_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    EVT_APP_FLASH_REINIT,
    EVT_APP_FLASH_SAVE_CONFIG,
    EVT_APP_FLASH_SAVE_STATUS,
    EVT_APP_FLASH_FACTORY_RESET,
    EVT_APP_FLASH_MAX,

    EVT_APP_DEVICE_REBOOT,
    EVT_APP_DEVICE_OTA_START,
    EVT_APP_DEVICE_REINIT,
    EVT_APP_DEVICE_MAX,

    EVT_APP_BLE_START_INDEX,
    EVT_APP_BLE_SEND_REGISTERATION_REQUEST,
    EVT_APP_BLE_SEND_CONFIG_STATUS,
    EVT_APP_BLE_OTA_SUCCESS,
    EVT_APP_BLE_OTA_FAILED,
    EVT_APP_BLE_MAX,

    EVT_APP_MQTT_START,
    EVT_APP_MQTT_CONNECTED,
    EVT_APP_MQTT_DISCONNECTED,
    EVT_APP_MQTT_STOP,
    EVT_APP_MQTT_RESET,
    EVT_APP_MQTT_RESTART,
    EVT_APP_MQTT_MAX,
    EVT_APP_MAX
} deviceEvents_et;

/* Function declarations ----------------------------------------------------*/
void EVENTS_init();
void EVENTS_clear(uint8_t eventId_u8);
bool EVENTS_get(uint8_t eventId_u8);
void EVENTS_set(uint8_t eventId_u8);

#endif