/*
 * lib_delay.h
 *
 *  Created on: Jun 10, 2021
 *      Author: Saheblal Bagwan
 */

#ifndef LIB_DELAY_H_
#define LIB_DELAY_H_

#include "freertos/FreeRTOS.h"
#include "stdutils.h"

/* Macros -----------------------------------------------------------------*/
#define MS_TO_RTOS_TICKS(x) ((x) > portTICK_PERIOD_MS ? ((x) / portTICK_PERIOD_MS) : portTICK_PERIOD_MS)
#define TASK_DELAY_MS(x) vTaskDelay(MS_TO_RTOS_TICKS(x))

uint32_t millis();
int64_t micros();
void delay(uint32_t waitTime_u32);

#endif /* LIB_DELAY_H_ */
