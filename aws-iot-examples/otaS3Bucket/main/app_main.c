#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "lib_system.h"
#include "app_config.h"

#define thisModule APP_MODULE_MAIN

/* Thing Certificates ---------------------------------------------------------*/
extern const uint8_t aws_root_ca_pem_start[] asm("_binary_aws_root_ca_pem_start");
extern const uint8_t certificate_pem_crt_start[] asm("_binary_certificate_pem_crt_start");
extern const uint8_t private_pem_key_start[] asm("_binary_private_pem_key_start");

/* Variables -----------------------------------------------------------------*/
TaskHandle_t tHandle_appTask = NULL;

awsMsg_st awsAppMsg;

void app_task(void *param)
{
     static uint32_t nextAwsPublishTime = 10000;
    while (1)
    {
        if (SYSTEM_getMode() == SYSTEM_MODE_NORMAL)
        {
            if (AWS_isConnected())
            {
                // Publish Cyclic messages
                if (millis() > nextAwsPublishTime)
                {
                    nextAwsPublishTime = millis() + 10000;
                    awsAppMsg.payloadLen = sprintf(awsAppMsg.payload, "Firmware version: %s Hello AWS %d", APP_VERSION, millis());
                    strcpy(awsAppMsg.topic, PUB_TOPIC);
                    awsAppMsg.qos = 1;
                    awsAppMsg.retain = 0;

                    AWS_publish(&awsAppMsg);
                    printf("\n\r[PUB Message]  topic:%s  payload:%s", awsAppMsg.topic, awsAppMsg.payload);
                }

            }
        }
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

/**
* @brief    entry point of the project
* @param    None
* @return   None
*/
void app_main()
{
    uint8_t defaultLogLevels[MODULES_MAX] = DEFAULT_LOG_LEVELS;
    printf("\n device_id:%s lib_version:%s\r\n", DEVICE_getDeviceId(), LIB_VERSION);
    print_setDefaultLogLevel(MODULES_MAX, defaultLogLevels);

    awsInitConfig_st awsInitConfig = {
        .thingNamePtr = MY_THING_NAME,
        .hostNamePtr = AWS_IOT_MQTT_HOST,
        .port = AWS_IOT_MQTT_PORT,
        .certType = CERT_TYPE_CLAIM,
        .rootCaPtr = (char *)aws_root_ca_pem_start,
        .clientCertPtr = (char *)certificate_pem_crt_start,
        .privateKeyPtr = (char *)private_pem_key_start,
    };

    SYSTEM_init();
    WIFI_init(TEST_WIFI_SSID, TEST_WIFI_PASSWORD);
    AWS_init(&awsInitConfig);

    if (pdFALSE == xTaskCreate(&app_task, "app_task", TASK_APP_STACK_SIZE, NULL, TASK_APP_PRIORITY, &tHandle_appTask))
    {
        print_error("\n Error creating app_task \n restarting system\r\n\r\n");
        esp_restart();
    }
}
