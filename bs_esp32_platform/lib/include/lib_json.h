/** 
 * \file lib_json.h
 * \brief JSON library header file.
 */

#ifndef _LIB_JSON_H
#define _LIB_JSON_H

#include "lib_utils.h"
#include "lib_config.h"

#define LENGTH_KEY_SIZE 32 //Max 3-char keyStr ex:"typ", "dat", "cmd", "sts" etc

/**
 * @brief A structure to represent key-value pairs in a JSON string.
 */
typedef struct
{
    char keyStr[LENGTH_KEY_SIZE];   /*!< A key */
    char *pValueStr;                /*!< Value associated with the key */
} tagStructure_st;

#define MAX_JSON_ARRAY_OBJS 10

/**
 * @brief A structure to represent array of JSON objects.
 */
typedef struct
{
    uint8_t numOfJosnObjs_u8;                   /*!< Number of JSON objects in array */
    char jsonObjs[MAX_JSON_ARRAY_OBJS][150];    /*!< Array of objects */
} jsonArray_st;

/**
 * @brief Extract the key-value pairs sepcified by tags from a give JSON string.
 * @param [in] pJsonStr The JSON string
 * @param [inout] tags An array of key-value pairs to be extracted
 * @param [in] maxKeys_u8 The maximum number of keys to be extracted
 * @returns Status of extraction
 * @retval true on success
 * @retval false on failure
 */
bool JSON_processString(const char *pJsonStr, const tagStructure_st tags[], uint8_t maxKeys_u8);

/**
 * @brief Extract an array of JSON objects from given JSON string.
 * @param [in] pJsonStr The JSON strong
 * @param [inout] jsnArrPtr An array of JSON objects
 * @returns Status of extraction
 * @retval true on success
 * @retval false on failure
 */
uint8_t JSON_processArrayObjs(char *pJsonStr, jsonArray_st *jsnArrPtr);

#endif
