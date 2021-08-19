#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "lib_system.h"
#include "app_config.h"
// #include "lib_oled.h"

#define thisModule APP_MODULE_MAIN

/* Thing Certificates ---------------------------------------------------------*/
extern const uint8_t aws_root_ca_pem_start[] asm("_binary_aws_root_ca_pem_start");
extern const uint8_t certificate_pem_crt_start[] asm("_binary_certificate_pem_crt_start");
extern const uint8_t private_pem_key_start[] asm("_binary_private_pem_key_start");

extern const uint8_t claim_certificate_pem_crt_start[] asm("_binary_claim_certificate_pem_crt_start");
extern const uint8_t claim_private_pem_key_start[] asm("_binary_claim_private_pem_key_start");

/* Variables -----------------------------------------------------------------*/
TaskHandle_t tHandle_appTask = NULL;

awsMsg_st awsAppMsg;
int desiredLed = 1, reportedLed = 0;
char desiredColor[32] = "WHITE", reportedColor[32] = "RED";
int ledValue = 0;

void led0_ShadowHandler(char *pkey, void *value)
{
    desiredLed = *(int *)value;
    print_info("Delta update desired Led : %d", desiredLed);
}

void led1_ShadowHandler(char *pkey, void *value)
{
    // if ((strcmp((char *)value, "ON") == 0) || (strcmp((char *)value, "OFF") == 0))
    // {
        strcpy(desiredColor, (char *)value);
        print_info("Delta update desired color : %s", desiredColor);
    // }
}



void app_task(void *param)
{
    while (1)
    {
        if (SYSTEM_getMode() == SYSTEM_MODE_NORMAL)
        {
            if (AWS_isConnected())
            {
                if (desiredLed != reportedLed)
                {
                    reportedLed = desiredLed;

                    GPIO_pinWrite(LED0_PIN, desiredLed);
                    print_info("desiredLed:%d reportedLed:%d", desiredLed, reportedLed);
                    AWS_shadowUpdateReported(SHADWO_KEY_LED0, &reportedLed);
                }

                if (strcmp(desiredColor, reportedColor) != 0)
                {
                    strcpy(reportedColor, desiredColor);

                    print_info("desired Color:%s reported Color:%s", desiredColor, reportedColor);
                    AWS_shadowUpdateReported(SHADWO_KEY_LED1, reportedColor);
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

    awsShadow_st led0_Shadow = {
        .key = SHADWO_KEY_LED0,
        .valType = SHADOW_VALUE_TYPE_UINT,
        .callBackHandler = &led0_ShadowHandler,
        .value.uVal = 0};

    awsShadow_st led1_Shadow = {
        .key = SHADWO_KEY_LED1,
        .valType = SHADOW_VALUE_TYPE_STRING,
        .callBackHandler = &led1_ShadowHandler,
        .value.str = "WHITE"};

    SYSTEM_init();
    GPIO_pinMode(LED0_PIN, GPIO_MODE_OUTPUT, GPIO_PIN_INTR_DISABLE, NULL);

    WIFI_init(TEST_WIFI_SSID, TEST_WIFI_PASSWORD);
    AWS_init(&awsInitConfig);

    AWS_shadowDeltaRegister(&led0_Shadow);
    AWS_shadowDeltaRegister(&led1_Shadow);
     AWS_shadowUpdateAll(SHADWO_KEY_LED0, &desiredLed);
    AWS_shadowUpdateAll(SHADWO_KEY_LED1, desiredColor);

    if (pdFALSE == xTaskCreate(&app_task, "app_task", TASK_APP_STACK_SIZE, NULL, TASK_APP_PRIORITY, &tHandle_appTask))
    {
        print_error("\n Error creating app_task \n restarting system\r\n\r\n");
        esp_restart();
    }
}
