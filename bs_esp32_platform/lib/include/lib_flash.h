/*******************************************************************************
* Copyright (c) 2021, Buildstorm Pvt Ltd
*
* Filename:     lib_flash.h
*
* Author:       Amruta
* email:        amruta@buildstorm.com
*
* Description:
*               Contains wrapper functions to handle flash read/write functionalities.
*******************************************************************************/

#ifndef _LIB_MODULE_FLASH_H_
#define _LIB_MODULE_FLASH_H_

/* Includes ------------------------------------------------------------------*/
#include "stdutils.h"

/*---------------------------structures-------------------------------------*/
typedef enum
{
    FLASH_STATUS_OK,
    FLASH_STATUS_BUSY,
    FLASH_STATUS_LOAD_DEFAULT,
    FLASH_STATUS_READ_FAIL,
    FLASH_STATUS_WRITE_FAIL,
    FLASH_STATUS_INVALID_DATASET,
    FLASH_STATUS_MAX
} flashStatus_t;

typedef enum
{
    SYSTEM_STATUS_OTA,
    SYSTEM_STATUS_ALL,
    SYSTEM_STATUS_MAX
} systemStatusParams_et;

typedef enum
{
    DEVICE_CONFIG_HOST,
    DEVICE_CONFIG_PORT,
    DEVICE_CONFIG_USERNAME,
    DEVICE_CONFIG_PASSWORD,
    DEVICE_CONFIG_WIFI,
    DEVICE_CONFIG_THING_NAME,
    DEVICE_CONFIG_CLEAR,
    DEVICE_CONFIG_MAX
} deviceConfigParams_et;

typedef enum
{
    FLASH_CERT_CERTIFICATE_PEM,
    FLASH_CERT_PRIVATE_KEY,
    FLAH_CERT_MAX
} deviceCertType_et;

typedef enum
{
    FLASH_DATASET_DEVICE_CONFIG,
    FLASH_DATASET_SYSTEM_STATUS,
    FLASH_DATASET_DEVICE_CERTIFICATES,
    FLASH_DATASET_APP,
    FLASH_DATASET_MAX,
} flashDataSet_et;

/* Function declarations ----------------------------------------------------*/

void FLASH_printConfig();
bool FLASH_updatePending();
bool FLASH_isDeviceRegistered();
char *FLASH_getCertificate(deviceCertType_et certType_e);
const char *FLASH_getThingName();
bool FLASH_appDataRead(void *pData, uint16_t size_u16);
bool FLASH_appDataWrite(void *pData, uint16_t size_u16);
bool FLASH_appDataEraseAll();

#endif
