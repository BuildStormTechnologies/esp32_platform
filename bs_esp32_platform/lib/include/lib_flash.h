/**
 * \copyright Copyright (c) 2021, Buildstorm Pvt Ltd
 *
 * \file lib_flash.h
 * \brief Flash library header file.
 */

#ifndef _LIB_MODULE_FLASH_H_
#define _LIB_MODULE_FLASH_H_

/* Includes ------------------------------------------------------------------*/
#include "lib_utils.h"

/*---------------------------structures-------------------------------------*/
/**
 * @enum flashStatus_t
 * An enum to represent the status of flash operations.
 */
typedef enum
{
    FLASH_STATUS_OK,              /*!< Status ok */
    FLASH_STATUS_BUSY,            /*!< Status busy */
    FLASH_STATUS_LOAD_DEFAULT,    /*!< Load default configuration values */
    FLASH_STATUS_READ_FAIL,       /*!< Read failed */
    FLASH_STATUS_WRITE_FAIL,      /*!< Write failed */
    FLASH_STATUS_INVALID_DATASET, /*!< Data is invalid */
    FLASH_STATUS_MAX              /*!< Total number of status for Flash library */
} flashStatus_t;

/**
 * @enum systemStatusParams_et
 * An enum to represent System parameters.
 */
typedef enum
{
    SYSTEM_STATUS_OTA, /*!< System parameter OTA */
    SYSTEM_STATUS_ALL, /*!< System parameter ALL */
    SYSTEM_STATUS_MAX  /*!< Total number of parameters */
} systemStatusParams_et;

/**
 * @enum deviceConfigParams_et
 * An enum to represent Device Configuration parameters.
 */
typedef enum
{
    DEVICE_CONFIG_HOST,       /*!< AWS IoT Host */
    DEVICE_CONFIG_PORT,       /*!< AWS IoT Port number */
    DEVICE_CONFIG_USERNAME,   /*!< MQTT Username */
    DEVICE_CONFIG_PASSWORD,   /*!< MQTT Password */
    DEVICE_CONFIG_WIFI,       /*!< WIFI configuration parameter */
    DEVICE_CONFIG_THING_NAME, /*!< Thing name parameter */
    DEVICE_CONFIG_CLEAR,      /*!< Clear configurations */
    DEVICE_CONFIG_MAX         /*!< Total number of available configuration parameters */
} deviceConfigParams_et;

/**
 * @enum deviceCertType_et
 * An enum to represent Device Certificate type.
 */
typedef enum
{
    FLASH_CERT_CERTIFICATE_PEM, /*!< Device certificate */
    FLASH_CERT_PRIVATE_KEY,     /*!< Device private key */
    FLAH_CERT_MAX               /*!< Total number of device certificate types */
} deviceCertType_et;

/**
 * @enum flashDataSet_et
 * An enum to represent available Flash Datasets.
 */
typedef enum
{
    FLASH_DATASET_DEVICE_CONFIG,       /*!< Device configuration dataset */
    FLASH_DATASET_SYSTEM_STATUS,       /*!< System status dataset */
    FLASH_DATASET_DEVICE_CERTIFICATES, /*!< Device certificate dataset */
    FLASH_DATASET_APP,                 /*!< Application dataset */
    FLASH_DATASET_MAX,                 /*!< Total number of available datasets */
} flashDataSet_et;

/* Function declarations ----------------------------------------------------*/

/**
 * @brief Print stored device configuration.
 * @param none
 * @returns none
 */
void FLASH_printConfig();

/**
 * @brief Check if a dataset is updated.
 * @param none
 * @returns Dataset update status.
 * @retval true if a dataset is updated
 * @retval false if not updated
 */
bool FLASH_updatePending();

/**
 * @brief Check if the device is registered with AWS IoT.
 * @param none
 * @returns Device registration status.
 * @retval true is device is registered
 * @retval false if device is not registered yet.
 */
bool FLASH_isDeviceRegistered();

/**
 * @brief Get the given certificate from stored configuration.
 * @param [in] certType_e Type of certificate
 * @returns The certificate as string
 */
char *FLASH_getCertificate(deviceCertType_et certType_e);

/**
 * @brief Get thing name from stored configuration.
 * @param none
 * @returns The thing name.
 */
const char *FLASH_getThingName();

/**
 * @brief Read the data from application dataset.
 * @param [out] pData Data buffer
 * @param [in] pData Length of data
 * @returns Read status
 * @retval true on successful read
 * @retval false on failure
 */
bool FLASH_appDataRead(void *pData, uint16_t size_u16);

/**
 * @brief Store the given data to application data set.
 * @param [in] pData Data to be written
 * @param [in] size_u16 Length of data
 * @returns Write status
 * @retval true on success
 * @retval false on failure
 */
bool FLASH_appDataWrite(void *pData, uint16_t size_u16);

/**
 * @brief Erase stored application dataset.
 * @param none
 * @return Erase status
 * @retval true on success
 * @retval false on failure
 */
bool FLASH_appDataEraseAll();

#endif
