/*******************************************************************************
*
* Filename:     app_main.c
*
* Description:
*               main entry of the application .
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lib_system.h"
#include "lib_ble.h"
#include "lib_wifi.h"
#include "lib_aws.h"
#include "lib_jobs.h"
#include "lib_gpio.h"
#include "lib_flash.h"
#include "lib_delay.h"
#include "lib_print.h"
#include "lib_json.h"
#include "lib_utils.h"

#include "app_config.h"

/* Macros ------------------------------------------------------------------*/

#define thisModule APP_MODULE_MAIN
#define STR_AWS_TOPIC_PUBLISH "devicePubTopic"

/* Certificates ---------------------------------------------------------*/
extern const uint8_t aws_root_ca_pem_start[] asm("_binary_aws_root_ca_pem_start");

/* Variables -----------------------------------------------------------------*/

static logLevels_et gDefaultLogLevels_ae[MODULES_MAX] = DEFAULT_LOG_LEVELS;

void app_eventsCallBackHandler(systemEvents_et event_e)
{
    switch (event_e)
    {
    case EVENT_WIFI_CONNECTED:
        print_info("EVENT_WIFI_CONNECTED");
        break;
    case EVENT_WIFI_DISCONNECTED:
        print_info("EVENT_WIFI_DISCONNECTED");
        break;

    case EVENT_AWS_CONNECTED:
        print_info("EVENT_AWS_CONNECTED");
        break;
    case EVENT_AWS_DISCONNECTED:
        print_info("EVENT_AWS_DISCONNECTED");
        break;

    case EVENT_BLE_CONNECTED:
        print_info("EVENT_BLE_CONNECTED");
        break;
    case EVENT_BLE_AUTHENTICATED:
        print_info("EVENT_BLE_AUTHENTICATED");
        break;
    case EVENT_BLE_DISCONNECTED:
        print_info("EVENT_BLE_DISCONNECTED");
        break;

    default:
        break;
    }
}

void app_task(void *param)
{
    mqttMsg_st pubMsg = {0};
    uint32_t nextMsgTime_u32 = 0;
    uint8_t counter_u8 = 0;

    while (1)
    {
        switch (SYSTEM_getMode())
        {
        case SYSTEM_MODE_DEVICE_CONFIG:
            if (millis() > nextMsgTime_u32)
            {
                nextMsgTime_u32 = millis() + 2000;

                if (FLASH_isDeviceRegistered())
                {
                    print_info("Device successfully provisioned");
                }
                else
                {
                    print_info("Device is not provisioned");
                }
            }
            break;

        case SYSTEM_MODE_NORMAL:
            if (AWS_isConnected())
            {
                // publish message every 10 seconds
                if (millis() > nextMsgTime_u32)
                {
                    nextMsgTime_u32 = millis() + 10000;
                    pubMsg.payloadLen_u16 = sprintf(pubMsg.payloadStr, "Hello from device - counter: %d", counter_u8++);
                    pubMsg.topicLen_u8 = sprintf(pubMsg.topicStr, STR_AWS_TOPIC_PUBLISH);

                    AWS_publish(&pubMsg);
                    print_info("  PUB Message =>  topic:%s  payload:%s", pubMsg.topicStr, pubMsg.payloadStr);
                }
            }
            break;

        case SYSTEM_MODE_OTA:
            break;

        default:
            break;
        }
        TASK_DELAY_MS(200);
    }
}

/**
* @brief    entry point of the project
* @param    None
* @return   None
*/
void app_main()
{
    systemInitConfig_st sysConfig = {
        .pLogLevels_e = gDefaultLogLevels_ae,
        .logModulesCount_u8 = MODULES_MAX,
        .systemEventCallBack = app_eventsCallBackHandler,
        .pDeviceNamePrefixStr = DEVICE_NAME_PREFIX,
        .pAppVersionStr = APP_VERSION,
        .pLicenseIdStr = LICENSE_ID,
        .s_awsConfig = {
            .pRootCaStr = (char *)aws_root_ca_pem_start}};

    SYSTEM_init(&sysConfig);
    BLE_init();
    SYSTEM_start();

    BaseType_t err = xTaskCreate(&app_task, "app_task", TASK_APP_STACK_SIZE, NULL, TASK_APP_PRIORITY, NULL);
    if (pdPASS != err)
    {
        print_error("\n Error 0x%X in creating app_task \n restarting system\n\r\n\r", err);
        fflush(stdout);
        esp_restart();
    }
}
