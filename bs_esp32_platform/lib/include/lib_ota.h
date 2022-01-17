/*******************************************************************************
* Copyright (c) 2021, Buildstorm Pvt Ltd
*
* Filename:     lib_ota.h
*
* Author:       Amruta
* email:        amruta@buildstorm.com
*
* Description:
*               Contains wrapper functions to handle OTA functionalities.
*******************************************************************************/

#ifndef _LIB_OTA_H_
#define _LIB_OTA_H_

/* Includes ------------------------------------------------------------------*/
#include "esp_err.h"
#include "stdutils.h"

typedef enum
{
    OTA_STATUS_READY,
    OTA_STATUS_SUCCESS,
    OTA_STATUS_GET_PARTITION_FAILED,
    OTA_STATUS_BEGIN_FAILED,
    OTA_STATUS_WRITE_FAILED,
    OTA_STATUS_END_FAILED,
    OTA_STATUS_SET_PARTITION_FAILED,
    OTA_STATUS_TIMEDOUT,
    OTA_STATUS_DOWNLOAD_FAILED,
    OTA_STATUS_FAILED_UNKOWN_REASON,
    OTA_STATUS_MAX
} flashOtaStatus_et;

typedef enum
{
    OTA_UPDATE_TYPE_NONE,
    OTA_UPDATE_TYPE_LOCAL,
    OTA_UPDATE_TYPE_WEB,
    OTA_UPDATE_TYPE_MAX
} firmUpdateType_et;

/*---------------------------structures-------------------------------------*/

typedef struct
{
    esp_err_t error;
    flashOtaStatus_et status_e;
    uint8_t previousPartition_u8;
} otaStatus_st;

/* Function declarations ----------------------------------------------------*/

bool OTA_start(firmUpdateType_et updateType_e);
uint8_t OTA_getProgressPercentage();
bool OTA_inProgress();
void OTA_printStatus();

#endif