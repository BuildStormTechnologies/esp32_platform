#ifndef _LIB_JSON_H
#define _LIB_JSON_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "lib_config.h"


/**
* JSON type identifier. Basic types are:
*  o Object
*  o Array
*  o String
*  o Other primitive: number, boolean (true/false) or null
*/
typedef enum
{
    JSMN_UNDEFINED = 0,
    JSMN_OBJECT = 1,
    JSMN_ARRAY = 2,
    JSMN_STRING = 3,
    JSMN_PRIMITIVE = 4
} jsmntype_t;

enum jsmnerr
{
    /* Not enough tokens were provided */
    JSMN_ERROR_NOMEM = -1,
    /* Invalid character inside JSON string */
    JSMN_ERROR_INVAL = -2,
    /* The string is not a full JSON packet, more bytes expected */
    JSMN_ERROR_PART = -3
};

/**
* JSON token description.
* type     type (object, array, string etc.)
* start    start position in JSON data string
* end      end position in JSON data string
*/
typedef struct
{
    uint16_t type;
    int16_t start;
    int16_t end;
    int16_t size;
#ifdef JSMN_PARENT_LINKS
    int parent;
#endif
} jsmntok_t;

/**
* JSON parser. Contains an array of token blocks available. Also stores
* the string being parsed now and current position in that string
*/
typedef struct
{
    uint16_t pos;     /* offset in the JSON string */
    uint16_t toknext; /* next token to allocate */
    int16_t toksuper; /* superior token node, e.g parent object or array */
} jsmn_parser_t;

#define LENGTH_KEY_SIZE 32 //Max 3-char key ex:"typ", "dat", "cmd", "sts" etc

extern char jsonPktData[];
extern char jsonSharedMsgBuff[];

typedef struct
{
    char key[LENGTH_KEY_SIZE];
    char *value;
} tagStructure_st;

typedef struct
{
    char type[LENGTH_KEY_SIZE];
    char payload[LENGTH_MQTT_PAYLOAD];
} rcvdPkt_st;

#define MAX_JSON_ARRAY_OBJS 10

typedef struct{
  uint8_t numOfJosnObjs_u8;
  char jsonObjs[MAX_JSON_ARRAY_OBJS][150];
}jsonArray_st;

void jsmn_init(jsmn_parser_t *tokenParser);
uint8_t processJson(const char *json_ptr, const tagStructure_st tags[], int maxKeys);
bool json_extractPacket(char *ptr, rcvdPkt_st *rcvdPkt_ps, uint8_t maxKeys);
int json_processArrayObjs(char *ptr,jsonArray_st *jsnArrPtr);

#endif
