/**
 * \copyright Copyright (c) 2021, Buildstorm Pvt Ltd
 *
 * \file lib_msg.h
 * \brief MQTT message header file.
 */

#ifndef LIB_MSG_H_
#define LIB_MSG_H_

#include "lib_config.h"
#include "lib_utils.h"

/**
 * @enum qos_et
 * Supported QOS levels.
 */
typedef enum
{
    QOS0_AT_MOST_ONCE = 0, /*!< At most once */
    QOS1_AT_LEASET_ONCE,   /*!< At least once */
    // QOS2_AT_EXACTLY_ONCE   // Exactly once  // not supported
    QOS_AT_MAX /*!< Maximum number of supported QOS levels */
} qos_et;

/**
 * @enum @packetStatus_et
 * Possible status of MQTT message packets
 */
typedef enum
{
    STATUS_IDLE,      /*!< Idle status */
    STATUS_INPORGESS, /*!< Download is in progress */
    STATUS_COMPLETE,  /*!< Download completed */
    STATUS_FAILED,    /*!< Download failed */
    PACKET_STATUS_MAX /*!< Total number of available packet status */
} packetStatus_et;

/**
 * @brief Structure to represent MQTT message.
 */
typedef struct
{
    char topicStr[LENGTH_MQTT_TOPIC];     /*<! MQTT topic */
    char payloadStr[LENGTH_MQTT_PAYLOAD]; /*!< MQTT message payload */
    uint16_t payloadLen_u16;              /*!< Length of payload */
    uint8_t topicLen_u8;                  /*!< Length of topic */
    qos_et qos_e;                         /*!< QOS levels */
    bool retain_b8;                       /*!< Retain falg */
} mqttMsg_st;

/**
 * @brief Packeting structure to handle fragmentation and re-assembly
 * of file download.
 */
typedef struct
{
    uint32_t expectedFileSize_u32;       /*!< Expected filesize */
    uint32_t receivedFileSize_u32;       /*!< Received filesize */
    uint16_t dataLen_u16;                /*!< Length of received packet data */
    uint16_t packetId_u16;               /*!< Packet Id */
    packetStatus_et status_e;            /*!< Status of packet */
    uint8_t data_a8[LENGTH_HTTP_PACKET]; /*!< Received packet data */
} packet_st;

#endif /* LIB_MSG_H_ */
