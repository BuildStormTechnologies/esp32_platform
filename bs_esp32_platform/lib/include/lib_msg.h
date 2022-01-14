/*
 * lib_msg.h
 *
 *  Created on: Aug 14, 2021
 *      Author: Saheblal Bagwan
 */

#ifndef LIB_MSG_H_
#define LIB_MSG_H_

#include "lib_config.h"
#include "stdutils.h"

typedef enum
{
    QOS0_AT_MOST_ONCE = 0, // At most once
    QOS1_AT_LEASET_ONCE,    // At least once
    // QOS2_AT_EXACTLY_ONCE   // Exactly once  // not supported
    QOS_AT_MAX
} qos_et;

typedef enum
{
    STATUS_IDLE,
    STATUS_INPORGESS,
    STATUS_COMPLETE,
    STATUS_FAILED,
    PACKET_STATUS_MAX
} packetStatus_et;

typedef struct
{
    char topicStr[LENGTH_MQTT_TOPIC];
    char payloadStr[LENGTH_MQTT_PAYLOAD];
    uint16_t payloadLen_u16;
    uint8_t topicLen_u8;
    qos_et qos_e;
    bool retain_b8;
} mqttMsg_st;

typedef struct
{
    uint32_t expectedFileSize_u32;
    uint32_t receivedFileSize_u32;
    uint16_t dataLen_u16;
    uint16_t packetId_u16;
    packetStatus_et status_e;
    uint8_t data_a8[LENGTH_HTTP_PACKET];
} packet_st;

#endif /* LIB_MSG_H_ */
