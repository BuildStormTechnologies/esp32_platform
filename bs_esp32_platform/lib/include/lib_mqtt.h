#ifndef _LIB_MQTT_H_
#define _LIB_MQTT_H_

/*-------------------- Includes -----------------------*/
#include "lib_config.h"
#include "lib_msg.h"
#include "stdutils.h"

typedef enum
{
    STATE_MQTT_IDLE,
    STATE_MQTT_START,
    STATE_MQTT_DISCONNECTED,
    STATE_MQTT_CONNECTED,
    STATE_MQTT_ABORT,
    STATE_MQTT_MAX,
} mqttStates_et;

typedef enum
{
    MQTT_OKAY,
    MQTT_READ_EMPTY,
    MQTT_WRITE_FULL,
    MQTT_ERROR_MAX,
} mqttWrtStatus_et;

typedef struct
{
    char *pUriStr;
    char *pCertStr;
    char *pUserNameStr;
    char *pPasswordStr;
} mqttConfig_st;

bool MQTT_init(mqttConfig_st *ps_config);
void MQTT_sync();
bool MQTT_isConnected();
bool MQTT_isStarted();
bool MQTT_close();
bool MQTT_subscribe(char *pTopicStr, uint8_t qos_e);
bool MQTT_publish(mqttMsg_st *ps_msg);
uint8_t MQTT_availableToRead();
bool MQTT_read(mqttMsg_st *ps_msg);
void MQTT_printStatus();

#endif