/***************************************************************************************************
                                   BuildStorm.com
****************************************************************************************************
*
* Filename:     module_gpio.h
*
* Author:       Amruta
* email:        amruta@buildstorm.com
*
* Description:
*               Contains wrapper functions to handle GPIO functionalities.

* Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

* The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
* A copy of EULA is available for you https://buildstorm.com/eula
*****************************************************************************************************/

#ifndef _LIB_GPIO_H_
#define _LIB_GPIO_H_

/* Includes ------------------------------------------------------------------*/
#include "esp_system.h"
#include "esp_types.h"
#include "esp_err.h"
#include "driver/gpio.h"

/* Macros -----------------------------------------------------------------*/
#define  GPIO_pinWrite(gpioNum, state)  gpio_set_level(gpioNum, state)
#define  GPIO_pinRead(gpioNum) gpio_get_level(gpioNum)
/* User Defined Data Types ------------------------------------------------*/

typedef void (*gpio_intr_handler)(void *arg);

/* Function declarations ----------------------------------------------------*/
void GPIO_pinMode(gpio_num_t, gpio_mode_t, GPIO_INT_TYPE, gpio_intr_handler);

#endif