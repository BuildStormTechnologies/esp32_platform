#include <string.h>
#include "lib_system.h"
#include "stdutils.h"
#include "app_config.h"

#define thisModule APP_MODULE_MAIN

/* Thing Certificates ---------------------------------------------------------*/
extern const uint8_t aws_root_ca_pem_start[] asm("_binary_aws_root_ca_pem_start");
extern const uint8_t claim_certificate_pem_crt_start[] asm("_binary_claim_certificate_pem_crt_start");
extern const uint8_t claim_private_pem_key_start[] asm("_binary_claim_private_pem_key_start");

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

    uint32_t nextMsgTime_u32 = 0;
    uint8_t counter_u8 = 0;

    while (1)
    {
        switch (SYSTEM_getMode())
        {
        case SYSTEM_MODE_CONFIG:
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
                    pubMsg.topicLen_u8 = sprintf(pubMsg.topicStr, "testPub/ESP32");

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

void app_main()
{
    systemInitConfig_st s_sysConfig = {
        .pLogLevels_e = gDefaultLogLevels_ae,
        .logModulesCount_u8 = MODULES_MAX,
        .systemEventCallBack = app_eventsCallBackHandler,

        .pWifiSsidStr = TEST_WIFI_SSID,
        .pWifiPwdStr = TEST_WIFI_PASSWORD,

        .s_awsConfig =
            {.hostNameStr = AWS_IOT_MQTT_HOST,
             .port_u16 = AWS_IOT_MQTT_PORT,
             .pRootCaStr = (char *)aws_root_ca_pem_start,
             .pClaimCertStr = (char *)claim_certificate_pem_crt_start,
             .pClaimPrivateKeyStr = (char *)claim_private_pem_key_start,
             .pClaimTemplateStr = AWS_PROVISION_TEMPLATE_NAME}};

    bool initSuccess = SYSTEM_init(&s_sysConfig);

    if (initSuccess)
    {
        if (pdFALSE == xTaskCreate(&app_task, "app_task", TASK_APP_STACK_SIZE, NULL, TASK_APP_PRIORITY, NULL))
        {
            print_error("\n Error creating app_task \n restarting system\r\n\r\n");
            esp_restart();
        }
    }
}
