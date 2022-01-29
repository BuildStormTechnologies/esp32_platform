/*******************************************************************************
* Copyright (c) 2021, Buildstorm Pvt Ltd
*
* Filename:     lib_config.h
*
* Author:       Amruta
* email:        amruta@buildstorm.com
*
* Description:
*               Contains macros for the application
*******************************************************************************/

/** 
 * \file lib_config.h
 * \brief Configuration header file.
 */

#ifndef _LIB_CONFIG_H_
#define _LIB_CONFIG_H_

#include "esp_types.h"
#include "lib_utils.h"

#define LIB_VERSION "1.1.0"

//---------------------------Debug CONFIG---------------------------/

/**
 * @enum logLevels_et
 * @brief Levels of debug messages for printing.
 */
typedef enum
{
    PRINT_LEVEL_NONE = 0,    /*!< Does not print any log messages */
    PRINT_LEVEL_ERROR = 1,   /*!< Prints Error level log messages alone */
    PRINT_LEVEL_VERBOSE = 1, /*!< Prints log messages of both Error & Verbose level */
    PRINT_LEVEL_DEMO = 2,    /*!< Prints demo logs, used for better logging of demos examples */
    PRINT_LEVEL_INFO = 3,    /*!< Prints log messages of Error, Verbose & Info level */
    PRINT_LEVEL_DEBUG = 4,   /*!< Prints log messages of all levels */
    PRINT_LEVEL_MAX = 5      /*!< Total number of log levels */
} logLevels_et;

#define LOG_LEVEL_MAPPING       \
    {                           \
        'n', 'e', '0', 'i', 'd' \
    }
#define GLOBAL_LOG_LEVEL PRINT_LEVEL_ERROR
#define LOG_PASS_CODE_STR "[12345678]" // TODO: expose to user ????

/**
 * @enum menusLibModule_et
 * @brief An enum to represent Library modules.
 */
typedef enum
{
    LIB_MODULE_MAIN_MENU,
    LIB_MODULE_SYSTEM,
    LIB_MODULE_BLE,
    LIB_MODULE_WIFI,
    LIB_MODULE_MQTT,
    LIB_MODULE_AWS,
    LIB_MODULE_JOBS,
    LIB_MODULE_GPIO,
    LIB_MODULE_FLASH,
    DRV_MODULE_BLE,
    LIB_MODULE_JSON,
    LIB_MODULE_HTTP,
    LIB_MODULE_OTA,
    LIB_MODULE_UART,
    LIB_MODULE_MAX
} menusLibModule_et;

//---------------------------WIFI CONFIG------------------------------/
#define TIME_WIFI_NEXT_SCAN 2000 // in milli seconds
#define TIME_WIFI_SCAN_END 4000  // in milli seconds

#define TIMEOUT_WIFI_RECONNECT 10000 // in milli seconds
#define TIMEOUT_WIFI_RESTART 30000   // in milli seconds

#define LENGTH_WIFI_CRED_SSID 32
#define LENGTH_WIFI_CRED_PASSWORD 64
#define LENGTH_MAC_ADDRESS 13
#define LENGTH_IP_ADDRESS 16 // "192.168.192.168"

//--------------------------DEVICE CONFIG--------------------------------/
#define LENGTH_CHIP_ID LENGTH_MAC_ADDRESS
#define LENGTH_DEVICE_NAME 32
#define LENGTH_PRODUCT_ID LENGTH_DEVICE_NAME

#define TIME_MILLIS_ROLLOVER 0xFF000000 // in milli seconds (max millis

//--------------------------HTTP CONFIG--------------------------------/
#define LENGTH_HTTP_URL 150
#define LENGTH_HTTP_PACKET 1024
#define HTTP_RING_BUFFER_SIZE 4

//--------------------------MQTT CONFIG--------------------------------/
#define MQTT_TOPIC_OTA_STR "topicOTA/ESP32"

#define LENGTH_MQTT_TOPIC 100
#define LENGTH_MQTT_PAYLOAD 1024
#define MQTT_MAX_SUBSCRIBE_TOPICS 4

#define LENGTH_MQTT_URI LENGTH_HTTP_URL
#define LENGTH_MQTT_USERNAME 32
#define LENGTH_MQTT_PASSWORD 32

#define MQTT_PUB_RING_BUFFER_SIZE 5
#define MQTT_SUB_RING_BUFFER_SIZE 3

//------------------------AWS Config-----------------------------------/
#define LENGTH_AWS_TOPIC LENGTH_MQTT_TOPIC
#define LENGTH_AWS_PAYLOAD LENGTH_MQTT_PAYLOAD
#define AWS_MAX_SUBSCRIBE_TOPICS 3
#define AWS_MAX_PUBLISH_RETRY 3

#define AWS_PUB_RING_BUFFER_SIZE 3
#define AWS_SUB_RING_BUFFER_SIZE 3

#define LENGTH_AWS_JOB_ACTION 32
#define AWS_MAX_JOBS 3

#define AWS_MAX_SHADOWS_ELEMETS 5
#define LENGTH_AWS_SHADOW_KEY 16
#define LENGTH_AWS_SHADOW_BUFFER 32

#define LENGTH_THING_NAME LENGTH_DEVICE_NAME

#define LENGTH_ROOT_CA_MAX 1300u
#define LENGTH_CERTIFICATE_MAX 1400u
#define LENGTH_PRIVATE_KEY_MAX 1800u

//--------------------------BLE CONFIG--------------------------------/
#define BLE_PAYLOAD_SIZE 256

#define TIMEOUT_BLE_AUTH 30000
#define TIMEOUT_BLE_RX 5000

#define BLE_TX_RING_BUFFER_SIZE 3
#define BLE_RX_RING_BUFFER_SIZE 3

//-------------------------TASK CONFIG--------------------------/
#define TASK_SYSTEM_PRIORITY 6
#define TASK_SYSTEM_STACK_SIZE (6 * 1024) // reduce it to 4096

#define TASK_MQTT_PRIORITY 7
#define TASK_MQTT_STACK_SIZE (6 * 1024) // reduce it to 4096

//------------------------FLASH CONFIG--------------------------------/
#define FLASH_APP_DATA_SIZE 256

//------------------------OTA CONFIG--------------------------------/
#define LENGTH_OTA_URL LENGTH_HTTP_URL

#endif
