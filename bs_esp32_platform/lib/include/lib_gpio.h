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

#ifndef _LIB_GPIO_H_
#define _LIB_GPIO_H_

/* Includes ------------------------------------------------------------------*/

#include "driver/gpio.h"
#include "stdutils.h"

/* Macros -----------------------------------------------------------------*/
#define GPIO_pinWrite(gpioNum, state) gpio_set_level(gpioNum, state)
#define GPIO_pinRead(gpioNum) gpio_get_level(gpioNum)
/* User Defined Data Types ------------------------------------------------*/

typedef void (*gpio_intr_handler)(void *arg);

/* Function declarations ----------------------------------------------------*/
void GPIO_pinMode(gpio_num_t, gpio_mode_t, GPIO_INT_TYPE, gpio_intr_handler);

#endif