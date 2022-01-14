#include <string.h>
#include "lib_system.h"
#include "lib_delay.h"
#include "lib_print.h"
#include "stdutils.h"
#include "app_config.h"

#define thisModule APP_MODULE_MAIN

/* Thing Certificates ---------------------------------------------------------*/
extern const uint8_t aws_root_ca_pem_start[] asm("_binary_aws_root_ca_pem_start");
extern const uint8_t thing_certificate_pem_crt_start[] asm("_binary_thing_certificate_pem_crt_start");
extern const uint8_t thing_private_pem_key_start[] asm("_binary_thing_private_pem_key_start");

/* Variables -----------------------------------------------------------------*/
static logLevels_et gDefaultLogLevels_ae[MODULES_MAX] = DEFAULT_LOG_LEVELS;

void app_eventsCallBackHandler(systemEvents_et eventId)
{
    switch (eventId)
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
    mqttMsg_st subMsg = {0};

    uint32_t nextAwsPublishTime_u32 = 0;
    uint8_t counter_u8 = 0;

    while (1)
    {
        switch (SYSTEM_getMode())
        {
        case SYSTEM_MODE_CONFIG:
            break;

        case SYSTEM_MODE_NORMAL:
            if (AWS_isConnected())
            {
                // publish message every 5 seconds
                if (millis() > nextAwsPublishTime_u32)
                {
                    nextAwsPublishTime_u32 = millis() + 5000;
                    pubMsg.payloadLen_u16 = sprintf(pubMsg.payloadStr, "Hello from device - counter: %d", counter_u8++);
                    pubMsg.topicLen_u8 = sprintf(pubMsg.topicStr, "testPub/ESP32");

                    AWS_publish(&pubMsg);
                    print_info("  PUB Message =>  topic:%s  payload:%s", pubMsg.topicStr, pubMsg.payloadStr);
                }

                // message received? print it
                if (AWS_subMsgRead(&subMsg))
                {
                    print_info("  SUB Message =>  topic:%s  payload:%s", subMsg.topicStr, subMsg.payloadStr);
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

void app_main()
{
    systemInitConfig_st s_sysConfig = {
        .pLogLevels_e = gDefaultLogLevels_ae,
        .logModulesCount_u8 = MODULES_MAX,
        .systemEventCallBack = app_eventsCallBackHandler,
        .pDeviceNamePrefixStr = DEVICE_NAME_PREFIX,
        .pLicenseIdStr = LICENSE_ID,

        .pWifiSsidStr = TEST_WIFI_SSID,
        .pWifiPwdStr = TEST_WIFI_PASSWORD,

        .s_awsConfig = {
            .pThingNameStr = MY_THING_NAME,
            .hostNameStr = AWS_IOT_MQTT_HOST,
            .port_u16 = 8883,
            .pRootCaStr = (char *)aws_root_ca_pem_start,
            .pThingCertStr = (char *)thing_certificate_pem_crt_start,
            .pThingPrivateKeyStr = (char *)thing_private_pem_key_start}};

    bool initSuccess = SYSTEM_init(&s_sysConfig);

    if (initSuccess)
    {
    	SYSTEM_start();
	
        // subscribe to a topic
        AWS_subscribe("testSub/ESP32", QOS0_AT_MOST_ONCE);

        if (pdFALSE == xTaskCreate(&app_task, "app_task", TASK_APP_STACK_SIZE, NULL, TASK_APP_PRIORITY, NULL))
        {
            print_error("\n Error creating app_task \n restarting system\r\n\r\n");
            esp_restart();
        }
    }
    else
    {
        print_error("\n\rError SYSTEM_init");
        
    }
}
