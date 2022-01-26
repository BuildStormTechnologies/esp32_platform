/*******************************************************************************
* Copyright (c) 2021, Buildstorm Pvt Ltd
*
* Filename:     module_gpio.h
*
* Author:       Amruta
* email:        amruta@buildstorm.com
*
* Description:
*               Contains wrapper functions to handle GPIO functionalities.
*******************************************************************************/

/** 
 * \file lib_gpio.h
 * \brief GPIO library header file.
 */

#ifndef _LIB_GPIO_H_
#define _LIB_GPIO_H_

/* Includes ------------------------------------------------------------------*/

#include "driver/gpio.h"
#include "lib_utils.h"

/* Macros -----------------------------------------------------------------*/
#define GPIO_pinWrite(gpioNum, state) gpio_set_level(gpioNum, state)
#define GPIO_pinRead(gpioNum) gpio_get_level(gpioNum)
/* User Defined Data Types ------------------------------------------------*/

/**
 * @brief GPIO interrupt handler callback function. The application should
 * define it and provide it in @ref GPIO_pinMode as parameter.
 */
typedef void (*gpio_intr_handler)(void *arg);

/* Function declarations ----------------------------------------------------*/

/**
 * @brief Configure GPIO pin, mode, interrupt & interrupt handler.
 * @param gpioNum GPIO number
 * @param mode GPIO mode
 * @param intrType GPIO interrupt type
 * @param handler GPIO interrupt callback handler
 * @returns none
 */
void GPIO_pinMode(gpio_num_t, gpio_mode_t, GPIO_INT_TYPE, gpio_intr_handler);

#endif