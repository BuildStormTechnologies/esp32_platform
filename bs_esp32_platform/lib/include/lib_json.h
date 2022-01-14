#ifndef _LIB_JSON_H
#define _LIB_JSON_H

#include "stdutils.h"
#include "lib_config.h"

#define LENGTH_KEY_SIZE 32 //Max 3-char keyStr ex:"typ", "dat", "cmd", "sts" etc

typedef struct
{
    char keyStr[LENGTH_KEY_SIZE];
    char *pValueStr;
} tagStructure_st;

#define MAX_JSON_ARRAY_OBJS 10

typedef struct
{
    uint8_t numOfJosnObjs_u8;
    char jsonObjs[MAX_JSON_ARRAY_OBJS][150];
} jsonArray_st;

bool JSON_processString(const char *pJsonStr, const tagStructure_st tags[], uint8_t maxKeys_u8);
uint8_t JSON_processArrayObjs(char *pJsonStr, jsonArray_st *jsnArrPtr);

#endif
