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
#include "lib_uart.h"
#include "lib_delay.h"
#include "lib_print.h"
#include "lib_utils.h"

#include "app_config.h"

/* Macros ------------------------------------------------------------------*/

#define thisModule APP_MODULE_MAIN

#define SIZE_BUFFER_TX 64
#define SIZE_BUFFER_RX 16
#define STR_1 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

/* Variables -----------------------------------------------------------------*/
static logLevels_et gDefaultLogLevels_ae[MODULES_MAX] = DEFAULT_LOG_LEVELS;

void app_task(void *param)
{
    uint32_t nextMsgTime_u32 = 0;

    uint8_t writeBuff[SIZE_BUFFER_TX + 1] = {0};
    uint16_t writeBuffLen_u16 = 0;
    uint16_t sentLen_u16 = 0;
    uint8_t writeCount_u8 = 1;

    uint8_t readBuff[SIZE_BUFFER_RX + 1] = {0};
    uint16_t readLen_u16 = 0;
    uint8_t readCount_u8 = 0;

    while (1)
    {
        if (millis() > nextMsgTime_u32)
        {
            writeBuffLen_u16 = snprintf((char *)writeBuff, SIZE_BUFFER_TX, "%s", STR_1);
            sentLen_u16 = UART1_write(writeBuff, writeBuffLen_u16);
            nextMsgTime_u32 = millis() + 2000;
            writeCount_u8++;
            print_info("Sent %d bytes: %.*s", sentLen_u16, sentLen_u16, writeBuff);
        }
        else
        {
            readLen_u16 = UART1_read(readBuff, SIZE_BUFFER_RX);
            if (readLen_u16)
            {
                print_info("%03d: Received => %.*s", readCount_u8, readLen_u16, readBuff);
                readCount_u8++;
            }
        }

        TASK_DELAY_MS(100);
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
        .pLicenseIdStr = LICENSE_ID,
        .pAppVersionStr = APP_VERSION};

    SYSTEM_init(&sysConfig);
    SYSTEM_start();

    if (FALSE == UART1_Init(BAUD_RATE_UART_1, PIN_UART_1_TX, PIN_UART_1_RX))
    {
        print_error("\n Failed: UART1_Init \n restarting system\n\r\n\r");
        fflush(stdout);
        esp_restart();
    }

    BaseType_t err = xTaskCreate(&app_task, "app_task", TASK_APP_STACK_SIZE, NULL, TASK_APP_PRIORITY + 1, NULL);
    if (pdPASS != err)
    {
        print_error("\n Error 0x%X in creating app_task \n restarting system\n\r\n\r", err);
        fflush(stdout);
        esp_restart();
    }
}
