/***************************************************************************************************
                                   BuildStorm.com
 ****************************************************************************************************
 * File:   lib_aws.h
 * Version: 1.0
 * Author: Saheblal Bagwan
 * Description: This module implements the complete AWS IOTS for esp32. it takes care of below functionality.
                1. AWS device provisioning
                2. AWS publish/Subscribe
                3. AWS shadow updates
                4. OTA using AWS jobs
                

Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
A copy of EULA is available for you https://buildstorm.com/eula
**************************************************************************************************/
#ifndef _LIB_AWS_H_
#define _LIB_AWS_H_
#include "lib_config.h"


typedef enum{
  CERT_TYPE_CLAIM,
  CERT_TYPE_THING
}awsCertType_et;

typedef struct{
    char *thingNamePtr;
    char *hostNamePtr;
    uint32_t  port;
    awsCertType_et certType;
    char *rootCaPtr;
    char *clientCertPtr;
    char *privateKeyPtr;
    char *provisionTemplatePtr;
}awsInitConfig_st;

typedef struct
{
  char topic[LENGTH_AWS_TOPIC];
  char payload[LENGTH_AWS_PAYLOAD];
  uint16_t payloadLen;
  uint8_t qos;
  uint8_t retain;
}awsMsg_st;

typedef enum
{
    STATE_AWS_IDLE,
    STATE_AWS_INIT,
    STATE_AWS_START,
    STATE_AWS_PROVISIONING,
    STATE_AWS_CONNECTED,
    STATE_AWS_DISCONNECTED,
    STATE_AWS_MAX
} awsIotStates_et;

typedef enum
{
    STATE_PROVISION_IDLE,
    STATE_PROVISION_START,
    STATE_PROVISION_REQ,
    STATE_PROVISION_MAX
} provisionStates_et;

typedef struct
{
    char subTopic[LENGTH_AWS_TOPIC];
    uint8_t subTopicLen;
    uint8_t subQOS;
    uint8_t subsFlag;
} awsSubsTopics_st;

typedef enum{
  SHADOW_VALUE_TYPE_INT,
  SHADOW_VALUE_TYPE_UINT,
  SHADOW_VALUE_TYPE_FLOAT,
  SHADOW_VALUE_TYPE_STRING,
  SHADOW_VALUE_TYPE_MAX,
}shadowValueType_et;

typedef union{
   float fVal;
   uint32_t uVal;
   int32_t iVal; 
   char str[LENGTH_AWS_SHADOW_BUFFER];
}value_ut;

typedef void (*awsShadowUpdateCallBack_t)(char *pKey, void *value);

typedef struct{
   char key[LENGTH_AWS_SHADOW_KEY];
   value_ut value; 
   shadowValueType_et valType;
   awsShadowUpdateCallBack_t callBackHandler;
   uint8_t updated;
}awsShadow_st;



void AWS_init(awsInitConfig_st *configPtr);
void AWS_sync();
char *AWS_getThingName();
uint8_t AWS_isConnected();
bool AWS_subscribe(char *subTopic, uint8_t qos);
void AWS_publish(awsMsg_st *ptr);
uint8_t AWS_availableToRead();
uint8_t AWS_subMsgRead(awsMsg_st *ptr);
awsIotStates_et AWS_getState();
const char* AWS_getStateString();
void AWS_clearPublishMsgs();
void AWS_printStatus();
void AWS_printCertificates();
void AWS_abort();

bool AWS_shadowDeltaRegister(awsShadow_st *pShadow);
void AWS_shadowUpdateReported(char *pKey, void *pValue);
void AWS_shadowUpdateAll(char *pKey, void *pValue);

#endif