/**
 * \copyright Copyright (c) 2021, Buildstorm Pvt Ltd
 *
 * \file lib_delay.h
 * \brief Header file for delay.
 */

#ifndef LIB_DELAY_H_
#define LIB_DELAY_H_

#include "freertos/FreeRTOS.h"
#include "lib_utils.h"

/* Macros -----------------------------------------------------------------*/
#define MS_TO_RTOS_TICKS(x) ((x) > portTICK_PERIOD_MS ? ((x) / portTICK_PERIOD_MS) : portTICK_PERIOD_MS)
#define TASK_DELAY_MS(x) vTaskDelay(MS_TO_RTOS_TICKS(x))

/**
 * @brief Get time elapsed in milli seconds since start-up.
 * @param none
 * @returns Number of milli seconds
 */
uint32_t millis();

/**
 * @brief Get time elapsed in micro seconds since start-up.
 * @param none
 * @returns Number of micro seconds
 */
int64_t micros();

/**
 * @brief Delay, wait until given time period.
 * @param [in] waitTime_u32 Number of milli-seconds to wait
 * @returns none
 */
void delay(uint32_t waitTime_u32);

#endif /* LIB_DELAY_H_ */
