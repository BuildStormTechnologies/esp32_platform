/*******************************************************************************
* Copyright (c) 2021, Buildstorm Pvt Ltd
*
* Filename:     app_main.c
*
* Author:       Amruta
* email:        amruta@buildstorm.com
*
* Description:
*               main entry of the application .
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

typedef enum
{
    STATE_SYS_IDLE,
    STATE_SYS_WIFI_CONNECTING,
    STATE_SYS_AWS_CONNECTING,
    STATE_SYS_AWS_CONNECTED,
    STATE_SYS_AWS_PROVISIONING,
    STATE_SYS_AWS_PROVISIONED,
    STATE_SYS_AWS_REBOOT,
    STATE_SYS_MAX
} sysStates_et;

sysStates_et systemState = STATE_SYS_IDLE;
#define OLED_CURSOR_Y_OFFSET(y) ((y * 5) + 5) // offset by (y + 1) char size
char thingId[32] = {0};

uint32_t nextChangeTime =1000;
 static awsIotStates_et tempAwsState = 0;
awsIotStates_et get_tempAwsState()
{
   
        if(millis()>=nextChangeTime)
        {
            nextChangeTime = millis()+2000;
            
            if(tempAwsState<STATE_AWS_CONNECTED)   
                 tempAwsState = tempAwsState+1;     

            print_info("tempAwsState:%d",tempAwsState);                 
        }
        
        return tempAwsState;
}

void app_statusUpdate()
{
    sysStates_et systemStateTemp = STATE_SYS_IDLE;
    awsIotStates_et awsState = STATE_AWS_IDLE;
    uint8_t wifiIconState = 0;
    uint8_t awsIconState = 0;
    static uint8_t awsProvosionDispState = 0;
    static uint32_t provisionedDisplayTime = 0;

    if (WIFI_isConnected())
    {
        wifiIconState = 2;
        awsState = AWS_getState();
        //awsState = get_tempAwsState();
        
        switch (awsState)
        {
        case STATE_AWS_PROVISIONING:
            systemStateTemp = STATE_SYS_AWS_PROVISIONING;
            awsProvosionDispState = 1;
            awsIconState = 2;
            break;
            
        case STATE_AWS_CONNECTED:
       // print_info("STATE_AWS_CONNECTED:%d",awsProvosionDispState);
            if (awsProvosionDispState == 1)
            {
                awsProvosionDispState = 2;
                systemStateTemp = STATE_SYS_AWS_PROVISIONED;
                provisionedDisplayTime = millis()+1500;
            }
            else if (awsProvosionDispState == 2)
            {
                if(millis()>provisionedDisplayTime)
                {
                  systemStateTemp = STATE_SYS_AWS_REBOOT;
                  awsProvosionDispState = 3;
                }
            }
            else
            {
                systemStateTemp = STATE_SYS_AWS_CONNECTED;
            }
            awsIconState = 2;
            break;
        
        default:
            systemStateTemp = STATE_SYS_AWS_CONNECTING;
            awsIconState = 1;
            systemState = 0; // To Keep Blining the RED ICON
            break;
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
        
        if(!FLASH_isDeviceRegistered() || awsProvosionDispState)
          DISP_provisionScreen(awsProvosionDispState);
        // OLED_UpdateUI();
    }
}

void app_task(void *param)
{
    static uint32_t nextAwsPublishTime = 10000;
    vTaskDelay(2000 / portTICK_RATE_MS);
    DISP_clearDetailsScreen();
    uint8_t pubCount = 0;
    char pubMsg[32] = {0};
    char subMsg[32] = {0};
    while (1)
    {
        if (SYSTEM_getMode() == SYSTEM_MODE_NORMAL)
        {
            if (AWS_isConnected())
            {
                // Publish Cyclic messages
                if (millis() > nextAwsPublishTime)
                {
                    nextAwsPublishTime = millis() + 2000;
                    awsAppMsg.payloadLen = sprintf(awsAppMsg.payload, "Hello AWS %d", pubCount++);
                    strcpy(pubMsg, awsAppMsg.payload);
                    strcpy(awsAppMsg.topic, PUB_TOPIC);
                    awsAppMsg.qos = 1;
                    awsAppMsg.retain = 0;

                    AWS_publish(&awsAppMsg);
                    printf("\n\r[PUB Message]  topic:%s  payload:%s", awsAppMsg.topic, awsAppMsg.payload);
                    DISP_detailsScreen(thingId, pubMsg, subMsg);
                }

                // Check for Sub Msgs
                if (AWS_availableToRead())
                {
                    if (AWS_subMsgRead(&awsAppMsg))
                    {
                        printf("\n\r[SUB Message]  topic:%s  payload:%s", awsAppMsg.topic, awsAppMsg.payload);
                        strcpy(subMsg, awsAppMsg.payload);
                        DISP_detailsScreen(thingId, pubMsg, subMsg);
                    }
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
    // printf("\n device_id:%s lib_version:%s\r\n", DEVICE_getDeviceId(), LIB_VERSION);
    print_setDefaultLogLevel(MODULES_MAX, defaultLogLevels);
    DISP_init();
  
    awsInitConfig_st awsInitConfig = {
        .hostNamePtr = AWS_IOT_MQTT_HOST,
        .port = AWS_IOT_MQTT_PORT,
        .certType = CERT_TYPE_CLAIM,
        .rootCaPtr = (char *)aws_root_ca_pem_start,
        .clientCertPtr = (char *)certificate_pem_crt_start,
        .privateKeyPtr = (char *)private_pem_key_start,
        .provisionTemplatePtr = AWS_PROVISION_TEMPLATE_NAME,
    };

   
    SYSTEM_init();

    WIFI_init(TEST_WIFI_SSID, TEST_WIFI_PASSWORD);
    AWS_init(&awsInitConfig);
    AWS_subscribe(SUB_TOPIC, 0); //subscribe with QOS0;

    if (FLASH_isDeviceRegistered())
        sprintf(thingId, "%.*s", 19, FLASH_getThingName()); //Limited to 19 chars to dislay on TFT
    else if (awsInitConfig.certType == CERT_TYPE_THING)
        sprintf(thingId, "%.*s", 19, MY_THING_NAME);

   
    if (pdFALSE == xTaskCreate(&app_task, "app_task", TASK_APP_STACK_SIZE, NULL, TASK_APP_PRIORITY, &tHandle_appTask))
    {
        print_error("\n Error creating app_task \n restarting system\r\n\r\n");
        esp_restart();
    }
}
