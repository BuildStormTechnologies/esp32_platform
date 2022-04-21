/**
 * \copyright Copyright (c) 2021, Buildstorm Pvt Ltd
 *
 * \file lib_ota.h
 * \brief OTA library header file.
 */

#ifndef _LIB_OTA_H_
#define _LIB_OTA_H_

/* Includes ------------------------------------------------------------------*/
#include "esp_err.h"
#include "lib_utils.h"

// TODO: update the library using new apis. refer esp-idf ota example

/**
 * @enum flashOtaStatus_et
 * An enum to represent OTA status.
 */
typedef enum
{
    OTA_STATUS_READY,                /*!< Ready status */
    OTA_STATUS_SUCCESS,              /*!< OTA was successful */
    OTA_STATUS_GET_PARTITION_FAILED, /*!< Failed to get partition */
    OTA_STATUS_BEGIN_FAILED,         /*!< Failed to start OTA  */
    OTA_STATUS_WRITE_FAILED,         /*!< Failed to write OTA packets */
    OTA_STATUS_END_FAILED,           /*!< Failed to end OTA process */
    OTA_STATUS_SET_PARTITION_FAILED, /*!< Failed to set boot parition after OTA */
    OTA_STATUS_TIMEDOUT,             /*!< OTA process timedout */
    OTA_STATUS_DOWNLOAD_FAILED,      /*!< OTA file download failed */
    OTA_STATUS_FAILED_UNKOWN_REASON, /*!< OTA failed with unknown error */
    OTA_STATUS_MAX                   /*!< Total number of OTA status */
} flashOtaStatus_et;

/**
 * @enum firmUpdateType_et
 * Types of supported firmware updates.
 */
typedef enum
{
    OTA_UPDATE_TYPE_NONE,  /*!< None */
    OTA_UPDATE_TYPE_LOCAL, /*!< Perform local update */
    OTA_UPDATE_TYPE_WEB,   /*!< Perform web update */
    OTA_UPDATE_TYPE_MAX    /*!< Total number of firmware update types */
} firmUpdateType_et;

/*---------------------------structures-------------------------------------*/

/**
 * @brief OTA status
 */
typedef struct
{
    esp_err_t error;              /*!< ESP error type */
    flashOtaStatus_et status_e;   /*!< OTA status */
    uint8_t previousPartition_u8; /*!< Previous boot partition */
} otaStatus_st;

/* Function declarations ----------------------------------------------------*/

/**
 * @brief Start OTA firmware update process
 * @param [in] updateType_e type of update
 * @returns status of OTA start request
 * @retval true on success
 * @retval false on failure
 */
bool OTA_start(firmUpdateType_et updateType_e);

/**
 * @brief Get OTA progress in percentage.
 * @param none
 * @returns Progress value in percentage.
 */
uint8_t OTA_getProgressPercentage();

/**
 * @brief Check if OTA is in progress.
 * @param none
 * @returns Status to indicate if OTA is in progress
 * @retval true if in progress
 * @retval false if not in progress
 */
bool OTA_inProgress();

/**
 * @brief Prints the status of OTA.
 * @param none
 * @returns none
 */
void OTA_printStatus();

#endif