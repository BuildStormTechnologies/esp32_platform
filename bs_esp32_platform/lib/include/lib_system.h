/** 
 * \file lib_system.h
 * \brief System library header file.
 * 
 * The system library initialiezes the hardware peripherals required by the
 * system by handling core operations like handling connectivity events
 * for WiFi, BLE, AWS IoT operations, Flash storage operations, printing
 * device logs & OTA firmware updates.
 */

#ifndef _LIB_SYSTEM_H_
#define _LIB_SYSTEM_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"

#include "lib_aws.h"
#include "lib_ota.h"
#include "stdutils.h"


/** 
 * @enum systemMode_et
 * An enum that represents System modes. The system will always be in one of
 * the following mode.
 */
typedef enum
{
    SYSTEM_MODE_IDLE,   /*!< System idle state */
    SYSTEM_MODE_TEST,   /*!< Test mode */
    SYSTEM_MODE_CONFIG, /*!< Device is waiting for configuration */
    SYSTEM_MODE_NORMAL, /*!< Device is configured/provisioned to run AWS IoT */
    SYSTEM_MODE_OTA,    /*!< System is in OTA mode to perform firmware update */
    SYSTEM_MODE_ABORT,  /*!< System abort mode */
    SYSTEM_MODE_MAX     /*!< Total number of system modes */
} systemMode_et;

/** 
 * @enum systemEvents_et
 * An enum that represents System events. The system notifes the application
 * about these events using a callback of type systemEventCb_t.
 */
typedef enum
{
    EVENT_WIFI_CONNECTED,    /*!< WiFi is connected */
    EVENT_WIFI_DISCONNECTED, /*!< WiFi is disconnected */
    EVENT_AWS_CONNECTED,     /*!< Device is connected to AWS IoT endpoint */
    EVENT_AWS_DISCONNECTED,  /*!< Device is disconnected to AWS IoT endpoint*/
    EVENT_BLE_CONNECTED,     /*!< Device is connected to BLE central device */
    EVENT_BLE_AUTHENTICATED, /*!< A BLE xentral device has authenticated successfully */
    EVENT_BLE_DISCONNECTED,  /*!< Device is disconnected from BLE central device */
    EVENT_MQTT_CONNECTED,    /*!< Device is connected to MQTT broker */
    EVENT_MQTT_DISCONNECTED, /*!< Device is disconnected from MQTT broker */
    EVENT_MAX                /*!< Total number of system events */
} systemEvents_et;

/**
 * @brief System events callback function type. The application should
 * define the callback function and initialize the system configuration
 * with the callback function to receive the system events.
 */
typedef void (*systemEventCb_t)(systemEvents_et eventId);

/**
 * @brief System configuration structure. The application should define the
 * system configuration variable and configure it before calling
 * @ref SYSTEM_init function.
 */
typedef struct
{
    logLevels_et *pLogLevels_e; /*!< Desired log levels */
    uint8_t logModulesCount_u8; /*!< Total number of logging modules */
    char *pLicenseIdStr;
    char *pWifiSsidStr;                  /*!< WiFi SSID */
    char *pWifiPwdStr;                   /*!< WiFi password */
    char *pDeviceNamePrefixStr;          // max 15 bytes
    systemEventCb_t systemEventCallBack; /*!< System event callback handler */
    awsConfig_st s_awsConfig;            /*!< AWS configuration */
} systemInitConfig_st;

/**
 * @brief Initiliaze the system with given configuration.
 * @param [in] s_pConfig Pointer to system configuration structure.
 * @returns Initialization status
 * @retval true on success
 * @retval false on failure
 */
bool SYSTEM_init(systemInitConfig_st *s_pConfig);
void SYSTEM_start();
void SYSTEM_startOta(char *pUrlStr);

/**
 * @brief Initialize the device for OTA firmware update and put the
 * system into SYSTEM_MODE_OTA mode.
 * @param [in] e_type Firmware update type
 * @param [in] pUrlStr URL of firmware binary file
 * @returns OTA trigger status
 * @retval true on success
 * @retval false on failure
 */
bool SYSTEM_startFirmwareUpdate(firmUpdateType_et e_type, char *pUrlStr);

/**
 * @brief Start firmware file download.
 * @param [in] pUrlStr URL of file to be downloaded
 * @returns File download started status 
 * @retval true on success
 * @retval false on failure
 */
bool SYSTEM_startFileDownload(char *pUrlStr);

/**
 * @brief Restarts device.
 * @param [in] restartDelay_u32 Delay (ms) after which system should be restarted
 * @retval none
 */
void SYSTEM_restart(uint32_t restartDelay_u32);

bool SYSTEM_isWaitingForRestart();

/**
 * @brief Get the system mode.
 * @param none
 * @returns The current mode of the system
 */
systemMode_et SYSTEM_getMode();


/**
 * @brief Get the system mode as string.
 * @returns The current mode of the system as string
 * @retval "IDLE" string for SYSTEM_MODE_IDLE
 * @retval "TEST" string for SYSTEM_MODE_TEST
 * @retval "CONFIG" string for SYSTEM_MODE_CONFIG
 * @retval "NORMAL" string for SYSTEM_MODE_NORMAL
 * @retval "OTA" string for SYSTEM_MODE_OTA
 * @retval "ABORT" string for SYSTEM_MODE_ABORT
 */
const char *SYSTEM_getModeString();

/**
 * @brief Puts the system in abort mode and restarts the system.
 * @param [in] pMsgStr Error message
 * @param [in] pFunNameStr Function that called SYSTEM_abort
 * @param [in] errorCode_u32 Error code
 * @retval none
 */
void SYSTEM_abort(char *pMsgStr, const char *pFunNameStr, uint32_t errorCode_u32);
void SYSTEM_factoryReset(bool useFactoryPartition_b8, bool eraseAllData_b8);

/**
 * @brief Get the device name as registered in AWS IoT.
 * @param none
 * @returns Thing name as string
 */
const char *SYSTEM_getDeviceName();

/**
 * @brief Get the MAC address of the device.
 * @param none
 * @returns Device's MAC address as string
 */
const char *SYSTEM_getMacAddr();

/**
 * @brief Get the cause of device reset.
 * @param none
 * @returns System reset reason as string value
 * @retval NO_MEAN write some description here
 * @retval POWERON_RESET write some description here
 * @retval SW_RESET write some description here
 * @retval OWDT_RESET write some description here
 * @retval DEEPSLEEP_RESET write some description here
 * @retval SDIO_RESET write some description here
 * @retval TG0WDT_SYS_RESET write some description here
 * @retval TG1WDT_SYS_RESET write some description here
 * @retval RTCWDT_SYS_RESET write some description here
 * @retval INTRUSION_RESET write some description here
 * @retval TGWDT_CPU_RESET write some description here
 * @retval SW_CPU_RESET write some description here
 * @retval EXT_CPU_RESET write some description here
 * @retval RTCWDT_BROWN_OUT_RESET write some description here
 * @retval RTCWDT_RTC_RESET write some description here
 */
const char *SYSTEM_getResetCause();

#endif