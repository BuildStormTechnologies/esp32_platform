/***************************************************************************************************
                                   BuildStorm.com
 ****************************************************************************************************
 * File:   lib_mqtt.h
 * Version: 1.0
 * Author: Amruta
 * Description: This module implements the MQTT functionality. It takes care of following this.
                1. MQTT initialization, connection, disconnection
                2. MQTT publish/Subscribe                

Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
A copy of EULA is available for you https://buildstorm.com/eula
**************************************************************************************************/
#ifndef _LIB_MQTT_H_
#define _LIB_MQTT_H_

/*-------------------- Includes -----------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "lib_config.h" 

typedef enum
{
    STATE_MQTT_IDLE,
    STATE_MQTT_START,
    STATE_MQTT_DISCONNECTED,
    STATE_MQTT_CONNECTED,
    STATE_MQTT_ABORT,
    STATE_MQTT_MAX,
} mqttStates_et;

typedef struct
{
  char topic[LENGTH_MQTT_TOPIC];
  char payload[LENGTH_MQTT_PAYLOAD];
  uint16_t payloadLen;
  uint8_t qos;
  uint8_t retain;
}mqttMsg_st;

typedef struct{
    char subTopic[LENGTH_MQTT_TOPIC];
    uint8_t subQOS;
    uint8_t subsFlag;
}subsTopics_st;

typedef enum
{
    MQTT_OKAY,
    MQTT_READ_EMPTY,
    MQTT_WRITE_FULL,
    MQTT_ERROR_MAX,
} mqttWrtStatus_et;

typedef struct
{
    char *uri;
    char *certPtr;
    char *userNamePtr;
    char *passwordPtr;
} mqttConfig_st;


void MQTT_init(mqttConfig_st *cfgPtr);
void MQTT_sync();
bool MQTT_isConnected();
bool MQTT_isStarted();
bool MQTT_abort();
bool MQTT_subscribe(char *topic , uint8_t qos);
bool MQTT_publish(mqttMsg_st *msgPtr);
uint8_t MQTT_availableToRead(); 
bool MQTT_read(mqttMsg_st *rxMsg);
void MQTT_printStatus();

#endif