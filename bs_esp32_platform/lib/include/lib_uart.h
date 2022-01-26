/** 
 * \file lib_uart.h
 * \brief UART library header file.
 * 
 * 
 */

#ifndef _LIB_UART_H_
#define _LIB_UART_H_

#include "driver/gpio.h"
#include "lib_config.h"
#include "lib_utils.h"


typedef enum
{
    UART_PORT_NUM_0 = 0, // not supported
    UART_PORT_NUM_1 = 1,
    UART_PORT_NUM_2 = 2,
    UART_PORT_NUM_MAX
} uartPortNum_et;

/***************************************************************************************************
                             Function Prototypes
***************************************************************************************************/
bool UART_Init(uartPortNum_et uartPortNum_e, uint32_t baudRate_u32, uint16_t pinTx_u16, uint16_t pinRx_u16);
uint16_t UART_available(uartPortNum_et uartPortNum_e);
bool UART_readByte(uartPortNum_et uartPortNum_e, uint8_t *pBuff_u8);
uint16_t UART_read(uartPortNum_et uartPortNum_e, uint8_t *pBuff_u8, uint16_t maxLen_u16);
uint16_t UART_write(uartPortNum_et uartPortNum_e, uint8_t *pBuff_u8, uint16_t len_u16);
void UART_printf(uartPortNum_et uartPortNum_e, const char *argList, ...);

/**************************************************************************************************/

/****************************************************************************************************
                           Function Mapping To Support Muliple Channels
*****************************************************************************************************/
#define UART1_Init(baudRate_u32, pinTx_u16, pinRx_u16) UART_Init(UART_PORT_NUM_1, baudRate_u32, pinTx_u16, pinRx_u16)
#define UART2_Init(baudRate_u32, pinTx_u16, pinRx_u16) UART_Init(UART_PORT_NUM_2, baudRate_u32, pinTx_u16, pinRx_u16)

#define UART1_available() UART_available(UART_PORT_NUM_1)
#define UART2_available() UART_available(UART_PORT_NUM_2)

#define UART1_readByte(pBuff_u8) UART_readByte(UART_PORT_NUM_1, pBuff_u8)
#define UART2_readByte(pBuff_u8) UART_readByte(UART_PORT_NUM_2, pBuff_u8)
#define UART1_read(pBuff_u8, maxLen_u16) UART_read(UART_PORT_NUM_1, pBuff_u8, maxLen_u16)
#define UART2_read(pBuff_u8, maxLen_u16) UART_read(UART_PORT_NUM_2, pBuff_u8, maxLen_u16)

#define UART1_write(pBuff_u8, len_u16) UART_write(UART_PORT_NUM_1, pBuff_u8, len_u16)
#define UART2_write(pBuff_u8, len_u16) UART_write(UART_PORT_NUM_2, pBuff_u8, len_u16)

#define UART1_printf(var_arg_list...) UART_printf(UART_PORT_NUM_1, var_arg_list)
#define UART2_printf(var_arg_list...) UART_printf(UART_PORT_NUM_2, var_arg_list)

/****************************************************************************************************/
#endif
