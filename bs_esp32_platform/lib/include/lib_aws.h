/** \file lib_aws.h
 *  \brief An AWS library file
 * 
 *  AWS library handles AWS IoT events like Publish, Subscribe,
 *  Shadow updates, Connection events, Device Provisioning... etc.
 */

#ifndef _LIB_AWS_H_
#define _LIB_AWS_H_

#include "lib_config.h"
#include "lib_msg.h"
#include "lib_utils.h"

/**
 * @enum awsIotStates_et
 * An enum that represents states of AWS library. The AWS library will
 * be in one of the following mode.
 */
typedef enum
{
    STATE_AWS_IDLE,             /*!< AWS idle state */
    STATE_AWS_INIT,             /*!< AWS init state */
    STATE_AWS_START,            /*!< AWS start state */
    STATE_AWS_PROVISIONING,     /*!< AWS device provisioning in progress */
    STATE_AWS_CONNECTED,        /*!< Device is connected to AWS */
    STATE_AWS_DISCONNECTED,     /*!< Device is disconnected from AWS */
    STATE_AWS_SUSPENDED,        /*!< AWS library is suspended state */
    STATE_AWS_RESUME,           /*!< Resumes AWS library from suspended state */
    STATE_AWS_PROVISION_FAILED, /*!< AWS device provisioning has failed */
    STATE_AWS_MAX               /*!< Total number of AWS states */
} awsIotStates_et;

/**
 * @enum shadowValueType_et
 * An enum that represents all possible shadow value types.
 */
typedef enum
{
    SHADOW_VALUE_TYPE_INT,      /*!< Shadow value type as integer */
    SHADOW_VALUE_TYPE_UINT,     /*!< Shadow value type as unsigned integer */
    SHADOW_VALUE_TYPE_STRING,   /*!< Shadow value type as string */
    SHADOW_VALUE_TYPE_MAX,      /*!< Total number of shadow value types */
} shadowValueType_et;

/**
 * @enum shadowUpdateType_et
 * An enum that represents all possible shadow update types.
 */
typedef enum
{
    SHADOW_UPDATE_TYPE_DESIRED,     /*!< Update Desired state */
    SHADOW_UPDATE_TYPE_REPORTED,    /*!< Update Reported state */
    SHADOW_UPDATE_TYPE_ALL,         /*!< Update both Desired & Reported 
                                    states */
    SHADOW_UPDATE_TYPE_MAX,         /*!< Total number for update types */
} shadowUpdateType_et;

/**
 * @union value_ut
 * This is a shadow value type.
 */
typedef union
{
    uint32_t val_u32;                   /*!< Value of type uint32_t */
    int32_t val_i32;                    /*!< Value of type int32_t */
    char str[LENGTH_AWS_SHADOW_BUFFER]; /*!< Value of type string */
} value_ut;

/**
 * @brief Shadow update callback function type. The application should
 * define the callback function and intialize it in the @ref awsShadow_st 
 * configuration.
 */
typedef void (*awsShadowUpdateCallBack_t)(char *pKeyStr, void *pValue);

typedef struct
{
    char keyStr[LENGTH_AWS_SHADOW_KEY];
    value_ut value_e;
    shadowValueType_et valType_e;
} awsThingShadow_st;

/**
 * @brief AWS Shadow structure used by the library to handle shadow updates.
 * You should initialize the callback handler and register this awsShadow_st
 * by calling @ref AWS_shadowDeltaRegister function to receive callbacks
 * whenever the shadow element is updated.
 * 
 * This structure represent only one shadow element within a thing shadow.
 */
typedef struct
{
    shadowValueType_et valType_e;               /*!< A type of value required for this shadow element */
    awsShadowUpdateCallBack_t callBackHandler;  /*!< Callback handler to be called when shadow element is updated */
    char keyStr[LENGTH_AWS_SHADOW_KEY];         /*!< A key of the shadow element */
    value_ut value_e;                           /*!< A value of the shadow element */
    uint8_t isUpdated_b8;                       /*!< Flag to indicate update */
} awsShadow_st;

/**
 * @brief AWS configuration structure used by the library.
 */
typedef struct
{
    char hostNameStr[LENGTH_HTTP_URL];  /*!< AWS IoT Endpoint */
    uint16_t port_u16;                  /*!< AWS IoT port number */
    char *pRootCaStr;                   /*!< Root CA certificate string */
    char *pThingCertStr;                /*!< Thing ceritificate string */
    char *pThingPrivateKeyStr;          /*!< Thing Private key string */
    char *pClaimCertStr;                /*!< Claim certificate string */
    char *pClaimPrivateKeyStr;          /*!< Claim Private key string */
    char *pClaimTemplateStr;            /*!< Provisioning template name */
    const char *pThingNameStr;          /*!< AWS IoT thing name */
} awsConfig_st;

/**
 * @brief Check if the device is connected state.
 * @param none
 * @returns AWS connection status
 * @retval true when connected
 * @retval false when not connected
 */
bool AWS_isConnected();

/**
 * @brief Get the current state of AWS library.
 * @param none
 * @returns Current state of AWS library @ref awsIotStates_et
 */
awsIotStates_et AWS_getState();

/**
 * @brief Get current state of AWS library as string.
 * @param none
 * @returns String version of AWS states.
 * @retval "IDLE" - for STATE_AWS_IDLE
 * @retval "INIT" - for STATE_AWS_INIT
 * @retval "START" - for STATE_AWS_START
 * @retval "PROVISIONING" - for STATE_AWS_PROVISIONING
 * @retval "CONNECTED" - for STATE_AWS_CONNECTED
 * @retval "DISCONNECTED" - for STATE_AWS_DISCONNECTED
 * @retval "SUSPENDED" - for STATE_AWS_SUSPENDED
 * @retval "RESUME" - for STATE_AWS_RESUME
 * @retval "PROVISION_FAILED" - for STATE_AWS_PROVISION_FAILED
 */
const char *AWS_getStateString();

/**
 * @brief Get thing name.
 * @param none
 * @returns The thing name as registed with AWS IoT.
 */
const char *AWS_getThingName();

/**
 * @brief Suspend AWS library.
 * @param none
 * @returns none
 */
void AWS_suspend();

/**
 * @brief Resume AWS library from suspended state.
 * @param none
 * @returns none
 */
void AWS_resume();

/**
 * @brief Disconnect and close the AWS IoT connection.
 * @param none
 * @returns none
 */
void AWS_close();

/**
 * @brief Disconnect from AWS IoT and Reconnect back.
 * @param none
 * @returns none
 */
void AWS_restart();

/**
 * @brief Subscribe to a given Topic on AWS IoT.
 * @param [in] pTopicStr topic as string
 * @param [in] qos_e QOS level
 * @returns Subscription status
 * @retval true on success
 * @retval false on failure
 */
bool AWS_subscribe(char *pTopicStr, uint8_t qos_e);

/**
 * @brief Check if messages received for subscribed topics are
 * available in the subscription message buffer.
 * @param none
 * @returns Number of bytes available.
 */
uint16_t AWS_subMsgAvailable();

/**
 * @brief Read the available message from the subscription message buffer.
 * @param [out] mqttMsg_st MQTT message type
 * @returns Message read status
 * @retval true when message is read successfully from the buffer.
 * @retval false on errors
 */
bool AWS_subMsgRead(mqttMsg_st *ps_msg);

/**
 * @brief Publish given message to AWS IoT. The message is queued in a Publish
 * buffer, then gets published.
 * @param [in] mqttMsg_st MQTT message type for publishing
 * @returns Publish status
 * @retval true when message is queued for publishing
 * @retval false on errors
 */
bool AWS_publish(mqttMsg_st *ps_msg);

/**
 * @brief Check if message is available to publish in the Publish queue.
 * @param none
 * @returns Status to indiciate if message available for publishing
 * @retval true if message is available for publishing
 * @retval false if no message is available
 */
uint16_t AWS_pubMsgAvailable();

/**
 * @brief Check if library is still publishing messages.
 * @param none
 * @returns Status to indicate whether publish is in progress or not
 * @retval true when library is publishing messages
 * @retval false when it's not publishing
 */
bool AWS_publishInProgress();

/**
 * @brief Register a shadow element to receive callbacks whenever the shadow
 * element is updated with a new value.
 * @param [in] awsShadow_st shadow element to receive callback on update
 * @returns Status to indicate if callback is registered
 * @retval true registed successfully
 * @retval false when failed
 */
bool AWS_shadowDeltaRegister(awsShadow_st *ps_shadow);

/**
 * @brief Update the shadow element.
 * @param [in] pKeyStr A key representing shadow element
 * @param [in] pValue New value of the shadow element
 * @param [in] shadowUpdateType_et Type of shadow update
 * @returns Shadow update status
 * @retval true on success
 * @retval false on failure
 */
bool AWS_shadowUpdate(char *pKeyStr, void *pValue, shadowUpdateType_et updateType_e);

/**
 * @brief Update device shadow.
 * @param [in] awsThingShadow_st The Device shadow
 * @param [in] maxKeys_u8 Max keys to update
 * @param [in] shadowUpdateType_et Type of shadow update
 * @returns Shadow update status
 * @retval true on success
 * @retval false on failure
 */
bool AWS_shadowDocumentUpdate(awsThingShadow_st as_thingShadow[], uint8_t maxKeys_u8, shadowUpdateType_et updateType_e);

/**
 * @brief Print the status of AWS IoT.
 * @param none
 * @returns none
 */
void AWS_printStatus();

/**
 * @brief Print all of the subscribed topics.
 * @param none
 * @returns none
 */
void AWS_printSubscribedTopics();

/**
 * @brief Print the configured certificates. Prints ROOT CA,
 * Client Cert. & Private key.
 * @param none
 * @returns none
 */
void AWS_printCertificates();

#endif