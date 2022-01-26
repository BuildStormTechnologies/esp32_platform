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

/* Variables -----------------------------------------------------------------*/
static logLevels_et gDefaultLogLevels_ae[MODULES_MAX] = DEFAULT_LOG_LEVELS;

void app_task_2(void *param)
{
    uint32_t nextMsgTime_u32 = 0;

    uint8_t writeBuff[SIZE_BUFFER_TX + 1] = {0};
    uint16_t writeBuffLen_u16 = 0;
    uint16_t sentLen_u16 = 0;
    uint8_t writeCount_u8 = 0;

    uint8_t readBuff[SIZE_BUFFER_RX + 1] = {0};
    uint8_t readCount_u8 = 0;

    while (1)
    {
        if (millis() > nextMsgTime_u32)
        {
            nextMsgTime_u32 = millis();
            writeBuffLen_u16 = snprintf((char *)writeBuff, SIZE_BUFFER_TX, "UART2 Welcome ..0x%02X:%d ms", writeCount_u8, nextMsgTime_u32);

            sentLen_u16 = UART2_write(writeBuff, writeBuffLen_u16);
            print_info("%03d: Sent %d bytes of %s", writeCount_u8, sentLen_u16, writeBuff);

            writeCount_u8 += 2;
            nextMsgTime_u32 += 5000;
        }
        else
        {
            if (UART2_available())
            {
                print_info("%03d: Received => ", readCount_u8);
                while (UART2_readByte(readBuff))
                {
                    print_info_raw("%c", readBuff[0]);
                }
                readCount_u8++;
            }
        }

        TASK_DELAY_MS(150);
    }
}

void app_task_1(void *param)
{
    uint32_t nextMsgTime_u32 = 0;

    uint8_t writeBuff[SIZE_BUFFER_TX + 1] = {0};
    uint16_t writeBuffLen_u16 = 0;
    uint16_t sentLen_u16 = 0;
    uint8_t writeCount_u8 = 1;

    uint8_t readBuff[SIZE_BUFFER_RX + 1] = {0};
    uint8_t readCount_u8 = 0;

    while (1)
    {
        if (millis() > nextMsgTime_u32)
        {
            nextMsgTime_u32 = millis();
            writeBuffLen_u16 = snprintf((char *)writeBuff, SIZE_BUFFER_TX, "Welcome from UART1 ..0x%02X:%d ms", writeCount_u8, nextMsgTime_u32);

            sentLen_u16 = UART1_write(writeBuff, writeBuffLen_u16);
            print_info("%03d: Sent %d bytes of %s", writeCount_u8, sentLen_u16, writeBuff);

            writeCount_u8 += 2;
            nextMsgTime_u32 += 5500;
        }
        else
        {
            if (UART1_available())
            {
                print_info("%03d: Received => ", readCount_u8);
                while (UART1_readByte(readBuff))
                {
                    print_info_raw("%c", readBuff[0]);
                }
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
        .pLicenseIdStr = LICENSE_ID};

    SYSTEM_init(&sysConfig);
    SYSTEM_start();

    if (FALSE == UART_Init(UART_PORT_NUM_1, BAUD_RATE_UART_1, PIN_UART_1_TX, PIN_UART_1_RX))
    {
        print_error("\n Failed: UART1_Init \n restarting system\n\r\n\r");
        fflush(stdout);
        esp_restart();
    }

    if (FALSE == UART_Init(UART_PORT_NUM_2, BAUD_RATE_UART_2, PIN_UART_2_TX, PIN_UART_2_RX))
    {
        print_error("\n Failed: UART2_Init \n restarting system\n\r\n\r");
        fflush(stdout);
        esp_restart();
    }

    BaseType_t err = xTaskCreate(&app_task_1, "app_task_1", TASK_APP_STACK_SIZE, NULL, TASK_APP_PRIORITY + 1, NULL);
    if (pdPASS != err)
    {
        print_error("\n Error 0x%X in creating app_task_1 \n restarting system\n\r\n\r", err);
        fflush(stdout);
        esp_restart();
    }

    err = xTaskCreate(&app_task_2, "app_task_2", TASK_APP_STACK_SIZE + 1, NULL, TASK_APP_PRIORITY, NULL);
    if (pdPASS != err)
    {
        print_error("\n Error 0x%X in creating app_task_2 \n restarting system\n\r\n\r", err);
        fflush(stdout);
        esp_restart();
    }
}
