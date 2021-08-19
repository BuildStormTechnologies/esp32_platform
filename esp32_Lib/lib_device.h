/***************************************************************************************************
                                   BuildStorm.com
****************************************************************************************************
*
* Filename:     lib_device.h
*
* Author:       Amruta
* email:        amruta@buildstorm.com
*
* Description:
*               Contains wrapper functions to common device functionalities.

* Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

* The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
* A copy of EULA is available for you https://buildstorm.com/eula
*****************************************************************************************************/

#ifndef _LIB_DEVICE_H_
#define _LIB_DEVICE_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Function declarations ----------------------------------------------------*/
const char *DEVICE_getDeviceId();
const char *DEVICE_getMacAddr();
const char *DEVICE_getName();
const char *DEVICE_getResetCause();
void DEVICE_checkMemoryUsage();
void DEVICE_getHeapUsage(uint32_t *p_freeHeapsize, uint32_t *p_minHeapSize);
void DEVICE_printHeapUsage();

#endif
