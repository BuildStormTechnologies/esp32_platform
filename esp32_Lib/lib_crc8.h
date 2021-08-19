/***************************************************************************************************
                                   BuildStorm.com
****************************************************************************************************
*
* Filename:     lib_crc8.h
*
* Author:       Amruta
* email:        amruta@buildstorm.com
*
* Description:
*               CRC 8 library for BLE packeting
*
*  Copyright (c) 2018, Buildstorm Technologies
* The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
* A copy of EULA is available for you https://buildstorm.com/eula
****************************************************************************************************/
#ifndef _LIB_CRC8_H_
#define _LIB_CRC8_H_
#include <stdint.h>

uint8_t getCRC8(uint8_t *data_ptr, uint8_t length_u8);

#endif