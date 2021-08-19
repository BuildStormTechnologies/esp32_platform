/*******************************************************************************
* Copyright (c) 2021, Buildstorm Pvt Ltd
*
* Filename:     app_main.c
*
* Author:       Saheblal Bagwan
* email:        bagwan@buildstorm.com
*
* Description:
*               main entry of the application .
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "lib_gpio.h"
#include "lib_system.h"
#include "app_config.h"

#define thisModule APP_MODULE_MAIN

 #define LED_PIN 2

/* Variables -----------------------------------------------------------------*/
TaskHandle_t tHandle_appTask = NULL;

awsMsg_st awsAppMsg;

void app_task(void *param)
{
    static uint32_t count = 0;
    uint8_t ledState = TRUE;
    while (1)
    {
        GPIO_pinWrite(LED_PIN, ledState);
        ledState = !ledState;
        print_verbose("Hello World %d", count++);
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
    print_setDefaultLogLevel(MODULES_MAX, defaultLogLevels);

    SYSTEM_init();
    GPIO_pinMode(LED_PIN, GPIO_MODE_OUTPUT, GPIO_PIN_INTR_DISABLE, NULL);

    if (pdFALSE == xTaskCreate(&app_task, "app_task", TASK_APP_STACK_SIZE, NULL, TASK_APP_PRIORITY, &tHandle_appTask))
    {
        print_error("\n Error creating app_task \n restarting system\r\n\r\n");
        esp_restart();
    }
}
