/**
 * \copyright Copyright (c) 2021, Buildstorm Pvt Ltd
 *
 * \file lib_mqtt.h
 * \brief MQTT library header file.
 */

#ifndef _LIB_MQTT_H_
#define _LIB_MQTT_H_

/*-------------------- Includes -----------------------*/
#include "lib_config.h"
#include "lib_msg.h"
#include "lib_utils.h"

/**
 * @enum mqttStates_et
 * An enum to represent states of MQTT library.
 */
typedef enum
{
    STATE_MQTT_IDLE,         /*!< Idle state */
    STATE_MQTT_START,        /*!< Initialize and Start MQTT */
    STATE_MQTT_DISCONNECTED, /*!< MQTT is in Disconnected state */
    STATE_MQTT_CONNECTED,    /*!< MQTT is Connected state */
    STATE_MQTT_ABORT,        /*!< Abort and close MQTT connection */
    STATE_MQTT_MAX,
} mqttStates_et;

/**
 * @enum mqttWrtStatus_et
 * An enum to represent MQTT status.
 */
typedef enum
{
    MQTT_OKAY,
    MQTT_READ_EMPTY,
    MQTT_WRITE_FULL,
    MQTT_ERROR_MAX,
} mqttWrtStatus_et;

/**
 * @brief MQTT configuration structure.
 */
typedef struct
{
    char *pUriStr;      /*!< MQTT broker URI */
    char *pCertStr;     /*!< Certificate string */
    char *pUserNameStr; /*!< MQTT username */
    char *pPasswordStr; /*!< MQTT password */
} mqttConfig_st;

/**
 * @brief Initialize MQTT library with given MQTT configuration.
 * @param [in] ps_config MQTT configuration
 * @returns Status of initialization
 * @retval true on success
 * @retval false on failure
 */
bool MQTT_init(mqttConfig_st *ps_config);

/**
 * @brief Run MQTT library, this function should be called periodically
 * by the application.
 * @param none
 * @returns none
 */
void MQTT_sync();

/**
 * @brief Check if MQTT is connected to broker.
 * @param none
 * @returns Status of connection
 * @retval true if connected
 * @retval false if disconnected
 */
bool MQTT_isConnected();

/**
 * @brief Check if MQTT is initialized and has started.
 * @param none
 * @return status of MQTT has started or not
 * @retval true if MQTT has started
 * @retval false if MQTT has not started
 */
bool MQTT_isStarted();

/**
 * @brief Close and terminate MQTT connection
 * @param none
 * @returns Status of close request
 * @retval true if closed successfully
 * @retval false if failed to close
 */
bool MQTT_close();

/**
 * @brief Subscribe to a give topic.
 * @param [in] pTopicStr Topic to subscribe
 * @param [in] qos_e QOS Level
 * @returns Status to indicate if subscrption was successful or not
 * @retval true subscribed successfully
 * @retval false failed to subscribe
 */
bool MQTT_subscribe(char *pTopicStr, uint8_t qos_e);

/**
 * @brief Publish a given message.
 * @param [in] ps_msg Message to be published
 * @returns Status of publish request
 * @retval true if published
 * @retval false on error
 */
bool MQTT_publish(mqttMsg_st *ps_msg);

/**
 * @brief Check is messages are available on subsribed topics. The library
 * maintains a buffer to store received messages.
 * @param none
 * @returns Number of bytes available
 */
uint8_t MQTT_availableToRead();

/**
 * @brief Read the received message received.
 * @param [out] ps_msg
 * @returns Status of read message
 * @retval true on success
 * @retval false on failure
 */
bool MQTT_read(mqttMsg_st *ps_msg);

/**
 * @brief Print the status of MQTT library.
 * @param none
 * @returns none
 */
void MQTT_printStatus();

#endif