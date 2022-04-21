/**
 * \copyright Copyright (c) 2021, Buildstorm Pvt Ltd
 *
 * \file lib_uart.h
 * \brief UART library header file.
 */

#ifndef _LIB_UART_H_
#define _LIB_UART_H_

#include "driver/gpio.h"
#include "lib_config.h"
#include "lib_utils.h"

/**
 * @enum uartPortNum_et
 * An enum that represents supported UARTs by this library.
 *
 * UART_0 is the default UART used by esp-idf for logs.
 * So this library doesn't support it
 *
 */
typedef enum
{
    UART_PORT_NUM_0 = 0, /*!< UART_0: not supported */
    UART_PORT_NUM_1 = 1, /*!< UART_1 */
    UART_PORT_NUM_2 = 2, /*!< UART_2 */
    UART_PORT_NUM_MAX    /*!< Total number of UARTs*/
} uartPortNum_et;

/**
 * @brief Initialize a UART with given configuration
 * @param [in] uartPortNum_e UART number
 * @param [in] baudRate_u32 UART baudrate
 * @param [in] pinTx_u16 UART Tx Pin number
 * @param [in] pinRx_u16 UART Rx Pin number
 * @returns Initialization status
 * @retval true on success
 * @retval false on failure
 */
bool UART_Init(uartPortNum_et uartPortNum_e, uint32_t baudRate_u32, uint16_t pinTx_u16, uint16_t pinRx_u16);

/**
 * @brief Get the number of received bytes available in Rx buffer
 * @param [in] uartPortNum_e UART number
 * @returns Number of bytes available.
 */
uint16_t UART_available(uartPortNum_et uartPortNum_e);

/**
 * @brief Read a byte data from Rx buffer
 * @param [in] uartPortNum_e UART number
 * @returns Data read status
 * @retval true when data is read successfully from the buffer.
 * @retval false on errors
 */
bool UART_readByte(uartPortNum_et uartPortNum_e, uint8_t *pBuff_u8);

/**
 * @brief Read data from Rx buffer.
 *
 * The read size will be smallest of @ref maxLen_u16 and @ref UART_available()
 *
 * @param [in] uartPortNum_e UART number
 * @param [out] pBuff_u8 Data buffer
 * @param [in] maxLen_u16 Max number of bytes to read
 * @returns Number of bytes read
 */
uint16_t UART_read(uartPortNum_et uartPortNum_e, uint8_t *pBuff_u8, uint16_t maxLen_u16);

/**
 * @brief Write data to UART.
 *
 * This is non blocking function and it will copy data to internal Tx buffer to send it later.
 *
 * @param [in] uartPortNum_e UART number
 * @param [out] pBuff_u8 Data buffer
 * @param [in] maxLen_u16 Data buffer size
 * @returns Number of bytes sent
 */
uint16_t UART_write(uartPortNum_et uartPortNum_e, uint8_t *pBuff_u8, uint16_t len_u16);

/****************************************************************************************************
 *                           Function Mapping To Support Muliple Channels
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

#endif
