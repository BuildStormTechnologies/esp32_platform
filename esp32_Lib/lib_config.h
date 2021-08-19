/***************************************************************************************************
                                   BuildStorm.com
****************************************************************************************************
*
* Filename:     lib_config.h
*
* Author:       Amruta
* email:        amruta@buildstorm.com
*
* Description:
*               Contains macros for the application configuration'

* Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

* The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
* A copy of EULA is available for you https://buildstorm.com/eula
*****************************************************************************************************/

#ifndef _LIB_CONFIG_H_
#define _LIB_CONFIG_H_

#include <stdbool.h>
#include <stdint.h>
#include "lib_print.h"

#define LIB_VERSION "1.0.0"

#include "stdbool.h"
#include "stdint.h"

//---------------------------Debug CONFIG---------------------------/

typedef enum
{
    PRINT_LEVEL_NONE = 0,
    PRINT_LEVEL_ERROR = 1,
    PRINT_LEVEL_INFO = 2,
    PRINT_LEVEL_DEBUG = 3,
    PRINT_LEVEL_MAX = 4
} logLevels_et;

#define LOG_LEVEL_MAPPING  \
    {                      \
        'n', 'e', 'i', 'd' \
    }
#define GLOBAL_LOG_LEVEL PRINT_LEVEL_ERROR 
#define LOG_PASS_CODE "[12345678]"
typedef enum
{
    LIB_MODULE_MAIN_MENU,
    LIB_MODULE_WIFI,
    LIB_MODULE_BLE,
    LIB_MODULE_MQTT,
    LIB_MODULE_AWS,
    LIB_MODULE_SYSTEM,
    LIB_MODULE_JOBS,
    LIB_MODULE_GPIO,
    LIB_MODULE_FLASH,
    DRV_MODULE_BLE,
    LIB_MODULE_JSON,
    LIB_MODULE_MAX
} menusLibModule_et;


#define LENGTH_PRODUCT_ID      32
//---------------------------WIFI CONFIG------------------------------/
#define TIME_WIFI_NEXT_SCAN    2000
#define TIME_WIFI_SCAN_END     4000
#define TIME_MILLIS_ROLLOVER   0xFF000000 // in milli seconds (max millis

#define LENGTH_WIFI_CRED_SSID     32
#define LENGTH_WIFI_CRED_PASSWORD 64
#define LENGTH_MAC_ADDRESS        13
#define LENGTH_CHIP_ID LENGTH_MAC_ADDRESS
#define LENGTH_IP_ADDRESS         16 // "192.168.192.168"

#define TIMEOUT_WIFI_RECONNECT 10000        // in milli seconds
#define TIMEOUT_WIFI_RESTART   30000        // in milli seconds
#define TIMEOUT_DEVICE_REBOOT  120000       // in milli seconds

//--------------------------MQTT CONFIG--------------------------------/
#define MQTT_TOPIC_OTA    "topicOTA/ESP32"

#define LENGTH_MQTT_TOPIC         100
#define LENGTH_MQTT_PAYLOAD       1024
#define MQTT_MAX_SUBSCRIBE_TOPICS 4

#define LENGTH_MQTT_URI      128
#define LENGTH_MQTT_USERNAME 32
#define LENGTH_MQTT_PASSWORD 32

#define MQTT_PUB_RING_BUFFER_SIZE  5
#define MQTT_RCVD_RING_BUFFER_SIZE 3

#define JSON_MAX_PACKET_KEYS 3 // packet typ, dat, did(deviceID).
#define MQTT_MAX_PACKET_KEYS 3 // packet typ, dat, did(deviceID).

//------------------------AWS Config-----------------------------------/
#define LENGTH_AWS_TOPIC           100
#define LENGTH_AWS_PAYLOAD         1024 
#define AWS_MAX_SUBSCRIBE_TOPICS   5

#define AWS_PUB_RING_BUFFER_SIZE   5
#define AWS_RCVD_RING_BUFFER_SIZE  4

#define LENGTH_AWS_SHADOW_KEY    20     
#define LENGTH_AWS_SHADOW_BUFFER 32
#define MAX_AWS_SHADOWS_ELEMETS  5

#define LENGTH_THING_NAME_MAX     32u
#define LENGTH_ROOT_CA_MAX        1300u
#define LENGTH_CERTIFICATE_MAX    1400u
#define LENGTH_PRIVATE_KEY_MAX    1800u

//--------------------------BLE CONFIG--------------------------------/
#define BLE_PAYLOAD_SIZE_MAX 250
#define BLE_AUTH_CODE "BLE_AUTH_CODE"

#define TIMEOUT_BLE_AUTH 30000

#define BLE_SEND_RING_BUFFER_SIZE 5
#define BLE_RCVD_RING_BUFFER_SIZE 3

//-------------------------TASK CONFIG--------------------------/
#define TASK_SYSTEM_PRIORITY   5
#define TASK_SYSTEM_STACK_SIZE (6 * 1024)        // reduce it to 4096

#define TASK_MQTT_PRIORITY 6
#define TASK_MQTT_STACK_SIZE (6 * 1024) // reduce it to 4096

//------------------------OTA CONFIG--------------------------------/
#define LENGTH_OTA_URL 512
#define LENGTH_OTA_STATUS_STRING 32

#endif
