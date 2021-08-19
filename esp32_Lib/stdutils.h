/***************************************************************************************************
                                   BuildStorm.com
 ****************************************************************************************************
 * File:   stdutils.h
 * Version: 1.0
 * Author: Saheblal Bagwan
 * Description: Contains standard util macros, typedefs and data manupulation functions/macros
                

Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
A copy of EULA is available for you https://buildstorm.com/eula
**************************************************************************************************/

#ifndef _STD_UTIL_H_
#define _STD_UTIL_H_
#include <stdint.h>


/**********************************************************************************************
                      LOGIC level
*********************************************************************************************/
#define LOW  0x00u
#define HIGH 0x01u
/***************************************************************************************/

/**********************************************************************************************
                      Commonly used constants
********************************************************************************************/
#define C_ZERO_U8 0x00u
#define C_NULL_U8 0x00u
#define NULL_CHAR 0x00u

#ifndef NULL
#define NULL 0u
#endif

#ifndef TRUE
#define TRUE 1u
#endif

#ifndef true
#define true 1u
#endif


#ifndef FALSE
#define FALSE 0u
#endif

#ifndef false
#define false 0u
#endif


#define C_NOTOK_U8 0x00u
#define C_OK_U8 0x01u

#define C_INVALID_U8 0x00u
#define C_VALID_U8 0x01u

#define C_FAILED_U8 0x00u
#define C_SUCCESSFUL_U8 0x01u
#define C_BUSY_U8 0x02u

#define C_BINARY_U8 2u
#define C_DECIMAL_U8 10u
#define C_HEX_U8 16u
/***************************************************************************************/

/**********************************************************************************************
                    Standard Enumerations and Constants
*********************************************************************************************/
typedef enum
{
    E_FALSE,
    E_TRUE
} Boolean_et;

typedef enum
{
    E_FAILED,
    E_SUCCESS,
    E_BUSY,
    E_TIMEOUT
} Status_et;

typedef enum
{
    E_BINARY = 2,
    E_DECIMAL = 10,
    E_HEX = 16
} NumericSystem_et;
/***************************************************************************************/

/**********************************************************************************************
                    Macros for Bit Manipulation
**********************************************************************************************/
#define util_GetBitMask(bit)        (1 << (bit))
#define util_BitSet(x, bit)         ((x) |= util_GetBitMask(bit))
#define util_BitClear(x, bit)       ((x) &= ~util_GetBitMask(bit))
#define util_BitToggle(x, bit)      ((x) ^= util_GetBitMask(bit))
#define util_UpdateBit(x, bit, val) ((val) ? util_BitSet(x, bit) : util_BitClear(x, bit))

#define util_GetBitStatus(x, bit)   (((x) & (util_GetBitMask(bit))) != 0u)
#define util_IsBitSet(x, bit)       (((x) & (util_GetBitMask(bit))) != 0u)
#define util_IsBitCleared(x, bit)   (((x) & (util_GetBitMask(bit))) == 0u)

#define util_AreAllBitsSet(x, BitMask) (((x) & (BitMask)) == BitMask)
#define util_AreAnyBitsSet(x, BitMask) (((x) & (BitMask)) != 0x00u)
/***************************************************************************************/

/**********************************************************************************************
                    Macros to find the mod of a number
*********************************************************************************************/
#define util_GetMod8(dividend, divisor) (uint8_t)(dividend - (divisor * (uint8_t)(dividend / divisor)))
#define util_GetMod16(dividend, divisor) (uint16_t)(dividend - (divisor * (uint16_t)(dividend / divisor)))
#define util_GetMod32(dividend, divisor) (uint32_t)(dividend - (divisor * (uint32_t)(dividend / divisor)))
/****************************************************************************************/

/**********************************************************************************************
                    Macros for Dec2Ascii,Hec2Ascii and Acsii2Hex conversion
**********************************************************************************************/
#define util_Dec2Ascii(Dec) ((Dec) + 0x30)
#define util_Ascii2Dec(Asc) ((Asc)-0x30)
#define util_Hex2Ascii(Hex) (((Hex) > 0x09) ? ((Hex) + 0x37) : ((Hex) + 0x30))
#define util_Ascii2Hex(Asc) (((Asc) > 0x39) ? ((Asc)-0x37) : ((Asc)-0x30))

/****************************************************************************************/

/**********************************************************************************************
                    Macros to extract the nibbles
*********************************************************************************************/
#define util_ExtractNibble0to4(x) (uint8_t)((x)&0x0Fu)
#define util_ExtractNibble4to8(x) (uint8_t)(((x) >> 4) & 0x0Fu)
#define util_ExtractNibble8to12(x) (uint8_t)(((x) >> 8) & 0x0Fu)
#define util_ExtractNibble12to16(x) (uint8_t)(((x) >> 12) & 0x0Fu)
/***************************************************************************************/

/**********************************************************************************************
                    Macros to extract the Byte
*********************************************************************************************/
#define util_ExtractByte0to8(x) (uint8_t)((x)&0xFFu)
#define util_ExtractByte8to16(x)   (uint8_t) (((x)>>8) & 0xFFu)
#define util_ExtractByte16to24(x)  (uint8_t) (((x)>>16) & 0xFFu)
#define util_ExtractByte24to32(x) (uint8_t)(((x) >> 24) & 0xFFu)
/***************************************************************************************/

/**********************************************************************************************
                    Other Macros
*********************************************************************************************/
#define util_GetMax(num1, num2) (((num1) > (num2)) ? (num1) : (num2))
#define util_GetMin(num1, num2) (((num1) < (num2)) ? (num1) : (num2))

#define util_GetAbsolute(x) (((x) < 0) ? -(x) : (x))
#define util_IsAsciiInt(Asc) (((Asc) >= 0x30) && ((Asc) <= 0x39))
#define util_IsAsciiHex(Asc) ((util_IsAsciiInt(Asc)) || \
                              (((Asc) >= 'A') && ((Asc) <= 'F')) ||\
                              (((Asc) >= 'a') && ((Asc) <= 'f')))

#define util_IsUpperCase(Asc) (((Asc) >= 'A') && ((Asc) <= 'Z'))
#define util_IsLowerCase(Asc) (((Asc) >= 'a') && ((Asc) <= 'z'))
#define util_toLower(Asc)     (util_IsUpperCase(Asc)?((Asc)+0x20):(Asc))
#define util_toUpper(Asc)     (util_IsLowerCase(Asc)?((Asc)-0x20):(Asc))

#define util_ShiftToRight(x, c)      ((x) >> c)
#define util_ShiftToLeft(x, c)       ((x) << c)
#define util_ShiftNibbleToRight(x)   ((x) >> 4)
#define util_ShiftNibbleToLeft(x)    ((x) << 4)
#define util_ShiftBytesToRight(x, c) ((x) >> (8 * (c)))
#define util_ShiftBytesToLeft(x, c)  ((x) << (8 * (c)))

#define util_SecToMs(x) ((x)*1000)
/***************************************************************************************/

uint32_t util_getNumFromString(char *ptr);
#endif
