/** \file lib_aws.h
 *  \brief AWS library file
 * 
 *  APIs provided by Lib AWS.
 */

#ifndef _LIB_AWS_H_
#define _LIB_AWS_H_

#include "lib_config.h"
#include "lib_msg.h"
#include "stdutils.h"

typedef enum
{
    STATE_AWS_IDLE,
    STATE_AWS_INIT,
    STATE_AWS_START,
    STATE_AWS_PROVISIONING,
    STATE_AWS_CONNECTED,
    STATE_AWS_DISCONNECTED,
    STATE_AWS_SUSPENDED,
    STATE_AWS_RESUME,
    STATE_AWS_PROVISION_FAILED,
    STATE_AWS_MAX
} awsIotStates_et;

typedef enum
{
    SHADOW_VALUE_TYPE_INT,
    SHADOW_VALUE_TYPE_UINT,
    SHADOW_VALUE_TYPE_STRING,
    SHADOW_VALUE_TYPE_MAX,
} shadowValueType_et;

typedef enum
{
    SHADOW_UPDATE_TYPE_DESIRED,
    SHADOW_UPDATE_TYPE_REPORTED,
    SHADOW_UPDATE_TYPE_ALL,
    SHADOW_UPDATE_TYPE_MAX,
} shadowUpdateType_et;

typedef union
{
    uint32_t val_u32;
    int32_t val_i32;
    char str[LENGTH_AWS_SHADOW_BUFFER];
} value_ut;

typedef void (*awsShadowUpdateCallBack_t)(char *pKeyStr, void *pValue);

typedef struct
{
    char keyStr[LENGTH_AWS_SHADOW_KEY];
    value_ut value_e;
    shadowValueType_et valType_e;
} awsThingShadow_st;

typedef struct
{
    shadowValueType_et valType_e;
    awsShadowUpdateCallBack_t callBackHandler;
    char keyStr[LENGTH_AWS_SHADOW_KEY];
    value_ut value_e;
    uint8_t isUpdated_b8;
} awsShadow_st;

typedef struct
{
    char hostNameStr[LENGTH_HTTP_URL];
    uint16_t port_u16;
    char *pRootCaStr;
    char *pThingCertStr;
    char *pThingPrivateKeyStr;
    char *pClaimCertStr;
    char *pClaimPrivateKeyStr;
    char *pClaimTemplateStr;
    const char *pThingNameStr;
} awsConfig_st;

bool AWS_isConnected();
awsIotStates_et AWS_getState();
const char *AWS_getStateString();
const char *AWS_getThingName();

void AWS_suspend();
void AWS_resume();
void AWS_close();
void AWS_restart();

bool AWS_subscribe(char *pTopicStr, uint8_t qos_e);
uint16_t AWS_subMsgAvailable();
bool AWS_subMsgRead(mqttMsg_st *ps_msg);

bool AWS_publish(mqttMsg_st *ps_msg);
uint16_t AWS_pubMsgAvailable();
bool AWS_publishInProgress();

bool AWS_shadowDeltaRegister(awsShadow_st *ps_shadow);
bool AWS_shadowUpdate(char *pKeyStr, void *pValue, shadowUpdateType_et updateType_e);
bool AWS_shadowDocumentUpdate(awsThingShadow_st as_thingShadow[], uint8_t maxKeys_u8, shadowUpdateType_et updateType_e);

void AWS_printStatus();
void AWS_printSubscribedTopics();
void AWS_printCertificates();

#endif