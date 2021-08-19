/***************************************************************************************************
                                   BuildStorm.com
****************************************************************************************************
*
* Filename:     lib_flash.h
*
* Author:       Amruta
* email:        amruta@buildstorm.com
*
* Description:
*               Contains wrapper functions to handle flash read/write functionalities.

* Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

* The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
* A copy of EULA is available for you https://buildstorm.com/eula
*****************************************************************************************************/

#ifndef _LIB_MODULE_FLASH_H_
#define _LIB_MODULE_FLASH_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>



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
    SYSTEM_OTA_STATUS,
    SYSTEM_STATUS_ALL,
    SYSTEM_STATUS_MAX
} systemStatusParams_et;

typedef enum
{
    DEVICE_CONFIG_HOST,
    DEVICE_CONFIG_PORT,
    DEVICE_CONFIG_WIFI,
    DEVICE_CONFIG_THING_NAME,
    DEVICE_CONFIG_REGISTERATION,
    DEVICE_CONFIG_CLEAR,
    DEVICE_CONFIG_MAX
} deviceConfigParams_et;

typedef enum
{
    DEVICE_CERTIFICATE_PEM,
    DEVICE_PRIVATE_KEY,
    DEVICE_CERTIFICATE_CLEAR_ALL,
    DEVICE_CERT_MAX
} deviceCertType_et;


typedef enum
{
    FLASH_DATASET_DEVICE_CONFIG,
    FLASH_DATASET_SYSTEM_STATUS,
    FLASH_DATASET_DEVICE_CERTIFICATES,
    FLASH_DATASET_MAX,
} flashDataSet_et;


/* Function declarations ----------------------------------------------------*/
flashStatus_t FLASH_init();
bool FLASH_reInit();
void FLASH_printConfig();
void FLASH_printStatus();
void FLASH_sync();

bool FLASH_busyState();
bool FLASH_updatePending();
bool FLASH_isDeviceRegistered();
void FLASH_deviceResgister();

bool FLASH_updateDeviceConfig(deviceConfigParams_et configType, void *configPtr);
bool FLASH_getDeviceConfig(deviceConfigParams_et configType, void *configPtr);

bool FLASH_getSystemStatus(systemStatusParams_et statusType, void *stsPtr);
bool FLASH_updateSystemStatus(systemStatusParams_et statusType, void *stsPtr);

char *FLASH_getCertificates(deviceCertType_et type);
void FLASH_updateCertificates(deviceCertType_et type, char *srcPtr);
char *FLASH_getThingName();

flashStatus_t FLASH_save(flashDataSet_et datasetType);
#endif
