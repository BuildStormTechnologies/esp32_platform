/*******************************************************************************
* Copyright (c) 2021, Buildstorm Pvt Ltd
*
* Filename:     app_main.c
*
* Author:       Amruta
* email:        amruta@buildstorm.com
*
* Description:
*               Esp32 AWS OTA demo on TFT screen .
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "lib_system.h"
#include "app_config.h"
#include "lib_display_TJCTM24024.h"

#define thisModule APP_MODULE_MAIN

/* Thing Certificates ---------------------------------------------------------*/
extern const uint8_t aws_root_ca_pem_start[] asm("_binary_aws_root_ca_pem_start");
extern const uint8_t certificate_pem_crt_start[] asm("_binary_certificate_pem_crt_start");
extern const uint8_t private_pem_key_start[] asm("_binary_private_pem_key_start");

/* Variables -----------------------------------------------------------------*/
TaskHandle_t tHandle_appTask = NULL;

awsMsg_st awsAppMsg;
int desiredLed = 1, reportedLed = 0;
char desiredColor[32] = "WHITE", reportedColor[32] = "RED";

typedef enum
{
    STATE_SYS_IDLE,
    STATE_SYS_WIFI_CONNECTING,
    STATE_SYS_AWS_CONNECTING,
    STATE_SYS_AWS_CONNECTED,
    STATE_SYS_MAX
} sysStates_et;

sysStates_et systemState = STATE_SYS_IDLE;
#define OLED_CURSOR_Y_OFFSET(y) ((y * 5) + 5) // offset by (y + 1) char size
char thingId[32] = {0};

uint32_t nextChangeTime = 1000;
void led_ShadowHandler(char *pkey, void *value)
{
    desiredLed = *(int *)value;
    print_info("desiredLed:%d", desiredLed);
}

void color_ShadowHandler(char *pkey, void *value)
{
    if ((strcmp((char *)value, "WHITE") == 0) || (strcmp((char *)value, "RED") == 0) || (strcmp((char *)value, "GREEN") == 0) || (strcmp((char *)value, "BLUE") == 0))
    {
        strcpy(desiredColor, (char *)value);
    }
}

void app_statusUpdate()
{
    sysStates_et systemStateTemp = STATE_SYS_IDLE;
    uint8_t wifiIconState = 0;
    uint8_t awsIconState = 0;

    if (WIFI_isConnected())
    {
        wifiIconState = 2;

        if (AWS_getState() == STATE_AWS_CONNECTED)
        {
            systemStateTemp = STATE_SYS_AWS_CONNECTED;
            awsIconState = 2;
        }
        else
        {
            systemStateTemp = STATE_SYS_AWS_CONNECTING;
            awsIconState = 1;
            systemState = 0; // To Keep Blining the RED ICON
        }
    }
    else
    {
        wifiIconState = 1;
        awsIconState = 0;
        systemStateTemp = STATE_SYS_WIFI_CONNECTING;
        systemState = 0; // To Keep Blining the RED ICON
    }

    if (systemStateTemp != systemState)
    {
        systemState = systemStateTemp;
        DISP_statusScreen(APP_VERSION, wifiIconState, awsIconState);
    }
}

void app_task(void *param)
{
    uint8_t shadowUpdated = 0;
    vTaskDelay(2000 / portTICK_RATE_MS);
    DISP_clearDetailsScreen();
    while (1)
    {
        if (SYSTEM_getMode() == SYSTEM_MODE_NORMAL)
        {
            if (AWS_isConnected())
            {
                if (desiredLed != reportedLed)
                {
                    reportedLed = desiredLed;

                    shadowUpdated = 1;
                    GPIO_pinWrite(LED_PIN, desiredLed);
                    print_info("desiredLed:%d reportedLed:%d", desiredLed, reportedLed);
                    AWS_shadowUpdateReported(SHADOW_KEY_LED, &reportedLed);
                }

                if (strcmp(desiredColor, reportedColor) != 0)
                {
                    strcpy(reportedColor, desiredColor);
                    shadowUpdated = 1;
                    print_info("desiredColor:%s reportedColor:%s", desiredColor, reportedColor);
                    AWS_shadowUpdateReported(SHADOW_KEY_COLOR, reportedColor);
                }

                if (shadowUpdated == 1)
                {
                    char ledStr[4] = {0};
                    shadowUpdated = 0;
                    sprintf(ledStr, "%s", desiredLed ? "1 " : "0 ");
                    DISP_clearDetailsScreen();
                    DISP_shadowUpdateScreen(thingId, ledStr, desiredColor);
                }
            }
        }

        app_statusUpdate();
        vTaskDelay(500 / portTICK_RATE_MS);
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
    print_setDefaultLogLevel(MODULES_MAX, defaultLogLevels);
    DISP_init();

    awsInitConfig_st awsInitConfig = {
        .hostNamePtr = AWS_IOT_MQTT_HOST,
        .port = AWS_IOT_MQTT_PORT,
        .certType = CERT_TYPE_CLAIM,
        .rootCaPtr = (char *)aws_root_ca_pem_start,
        .clientCertPtr = (char *)certificate_pem_crt_start,
        .privateKeyPtr = (char *)private_pem_key_start,
    };
    awsShadow_st led_Shadow = {
        .key = SHADOW_KEY_LED,
        .valType = SHADOW_VALUE_TYPE_UINT,
        .callBackHandler = &led_ShadowHandler,
        .value.uVal = 0};

    awsShadow_st color_Shadow = {
        .key = SHADOW_KEY_COLOR,
        .valType = SHADOW_VALUE_TYPE_STRING,
        .callBackHandler = &color_ShadowHandler,
        .value.str = "GREEN"};
    SYSTEM_init();
    GPIO_pinMode(LED_PIN, GPIO_MODE_OUTPUT, GPIO_PIN_INTR_DISABLE, NULL);

    WIFI_init(TEST_WIFI_SSID, TEST_WIFI_PASSWORD);
    AWS_init(&awsInitConfig);

    AWS_shadowDeltaRegister(&led_Shadow);
    AWS_shadowDeltaRegister(&color_Shadow);
     AWS_shadowUpdateAll(SHADOW_KEY_LED, &desiredLed);
    AWS_shadowUpdateAll(SHADOW_KEY_COLOR, desiredColor);
   
    if (FLASH_isDeviceRegistered())
        sprintf(thingId, "%.*s", 19, FLASH_getThingName()); //Limited to 19 chars to dislay on TFT
    else if (awsInitConfig.certType == CERT_TYPE_THING)
        sprintf(thingId, "%.*s", 19, MY_THING_NAME);

    // OLED_UpdateUI();
    if (pdFALSE == xTaskCreate(&app_task, "app_task", TASK_APP_STACK_SIZE, NULL, TASK_APP_PRIORITY, &tHandle_appTask))
    {
        print_error("\n Error creating app_task \n restarting system\r\n\r\n");
        esp_restart();
    }
}
