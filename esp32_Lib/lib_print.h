/***************************************************************************************************
                                   BuildStorm.com
 ****************************************************************************************************
 * File:   lib_print.h
 * Version: 1.0
 * Author: Saheblal Bagwan
 * Description: This file provides the API for serial debugging.
                - Supports runtime configuration of debug logs.

Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
A copy of EULA is available for you https://buildstorm.com/eula
**************************************************************************************************/
#ifndef _LIB_PRINT_H_
#define _LIB_PRINT_H_

#include "esp_system.h"
#include "esp_types.h"
#include "lib_config.h"


#define print_verbose(var_arg_list...) print_serial(thisModule,PRINT_LEVEL_ERROR,__func__,var_arg_list) // set to lowest log level to print every time
#define print_error(var_arg_list...) print_serial(thisModule,PRINT_LEVEL_ERROR,__func__,var_arg_list)
#define print_info(var_arg_list...)  print_serial(thisModule,PRINT_LEVEL_INFO,__func__,var_arg_list)
#define print_debug(var_arg_list...) print_serial(thisModule,PRINT_LEVEL_DEBUG,__func__,var_arg_list)


#define print_verbose_raw(var_arg_list...) print_serial(thisModule,PRINT_LEVEL_ERROR,NULL,var_arg_list)
#define print_error_raw(var_arg_list...) print_serial(thisModule,PRINT_LEVEL_ERROR,NULL,var_arg_list)
#define print_debug_raw(var_arg_list...) print_serial(thisModule,PRINT_LEVEL_DEBUG,NULL,var_arg_list)
#define print_info_raw(var_arg_list...)  print_serial(thisModule,PRINT_LEVEL_INFO,NULL,var_arg_list)


void PRINT_setLogLevel(uint8_t libModule, uint8_t logLevel);
void print_serial(uint8_t libModule,uint8_t logLevel, const char *funName,const char *argList, ...);
void print_setDefaultLogLevel(uint8_t maxModules, uint8_t *logLevels);

#endif