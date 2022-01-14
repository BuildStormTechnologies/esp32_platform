
/**********************************************************************************************
                                ExploreEmbedded
****************************************************************************************************
* File:   stdutils.h
* Version: 15.1
* Author: ExploreEmbedded
* Website: http://www.exploreembedded.com/wiki
* Description: Contains standard util macros, typedefs and constants

The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the
library works on any of development boards for respective controllers. However, ExploreEmbedded
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information
related to updates.


GNU GENERAL PUBLIC LICENSE:
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

Errors and omissions should be reported to codelibraries@exploreembedded.com
********************************************************************************************/

/*********************************************************************************************
                            Revision History
**********************************************************************************************
15.0: Initial version
15.1: Changed the prefix of bit masks from M_ to MASK_
    Added the section others macros
    Defined the constants for Number system
*********************************************************************************************/

#ifndef _STD_UTIL_H_
#define _STD_UTIL_H_
#include "esp_types.h"

/**********************************************************************************************
                      LOGIC level
*********************************************************************************************/
#define LOW 0x00u
#define HIGH 0x01u
/***************************************************************************************/

/**********************************************************************************************
                      Commonly used constants
********************************************************************************************/

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

/***************************************************************************************/

/**********************************************************************************************
                    Standard Enumerations and Constants
*********************************************************************************************/

typedef enum
{
    STS_SUCCESS,
    STS_BUSY,
    STS_FAILED,
    STS_TIMEOUT
} status_et;

/***************************************************************************************/

/**********************************************************************************************
                    Macros for Bit Manipulation
**********************************************************************************************/
#define util_GetBitMask(bit) (1 << (bit))
#define util_BitSet(x, bit) ((x) |= util_GetBitMask(bit))
#define util_BitClear(x, bit) ((x) &= ~util_GetBitMask(bit))
#define util_BitToggle(x, bit) ((x) ^= util_GetBitMask(bit))
#define util_UpdateBit(x, bit, val) ((val) ? util_BitSet(x, bit) : util_BitClear(x, bit))

#define util_GetBitStatus(x, bit) (((x) & (util_GetBitMask(bit))) != 0u)
#define util_IsBitSet(x, bit) (((x) & (util_GetBitMask(bit))) != 0u)
#define util_IsBitCleared(x, bit) (((x) & (util_GetBitMask(bit))) == 0u)

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
#define util_IsUpperCase(Asc) (((Asc) >= 'A') && ((Asc) <= 'Z'))
#define util_IsLowerCase(Asc) (((Asc) >= 'a') && ((Asc) <= 'z'))
#define util_toLower(Asc) (util_IsUpperCase(Asc) ? ((Asc) + 0x20) : (Asc))
#define util_toUpper(Asc) (util_IsLowerCase(Asc) ? ((Asc)-0x20) : (Asc))
/***************************************************************************************************/

/**********************************************************************************************
                    Macros to extract the Nibbles
*********************************************************************************************/
#define util_ExtractBits0to4(x) (uint8_t)((x)&0x0Fu)
#define util_ExtractBits4to8(x) (uint8_t)(((x) >> 4) & 0x0Fu)
#define util_ExtractBits8to12(x) (uint8_t)(((x) >> 8) & 0x0Fu)
#define util_ExtractBits12to16(x) (uint8_t)(((x) >> 12) & 0x0Fu)
/***************************************************************************************/

/**********************************************************************************************
                    Macros to extract the Byte
*********************************************************************************************/
#define util_ExtractBits0to8(x) (uint8_t)((x)&0xFFu)
#define util_ExtractBits8to16(x) (uint8_t)(((x) >> 8) & 0xFFu)
#define util_ExtractBits16to24(x) (uint8_t)(((x) >> 16) & 0xFFu)
#define util_ExtractBits24to32(x) (uint8_t)(((x) >> 24) & 0xFFu)
/***************************************************************************************/

/**********************************************************************************************
                    Other Macros
*********************************************************************************************/
#define util_GetMax(num1, num2) (((num1) > (num2)) ? (num1) : (num2))
#define util_GetMin(num1, num2) (((num1) < (num2)) ? (num1) : (num2))

#define util_swap(x, y) (x ^= y ^= x ^= y)
#define util_GetAbsolute(x) (((x) < 0) ? -(x) : (x))
#define util_IsAsciiInt(Asc) (((Asc) > 0x29) && ((Asc) < 0x40))
#define util_IsAsciiHex(Asc) ((util_IsAsciiInt(Asc)) ||             \
                              (((Asc) >= 'A') && ((Asc) <= 'F')) || \
                              (((Asc) >= 'a') && ((Asc) <= 'f')))

#define util_ShiftToRight(x, c) ((x) >> c)
#define util_ShiftToLeft(x, c) ((x) << c)
#define util_ShiftNibbleToRight(x) ((x) >> 4)
#define util_ShiftNibbleToLeft(x) ((x) << 4)
#define util_ShiftBytesToRight(x, c) ((x) >> (8 * (c)))
#define util_ShiftBytesToLeft(x, c) ((x) << (8 * (c)))

#define util_SecToMs(x) ((x)*1000)

#define TIMEOUT_US(us) (us)
#define TIMEOUT_MS(ms) (ms)
#define TIMEOUT_SEC(sec) (sec)
#define TIMEOUT_MIN(min) (min)

#define util_generateEnum(ENUM) ENUM,
#define util_generateString(STRING) #STRING,
/***************************************************************************************/

uint32_t util_getNumFromString(const char *pStr);
bool util_isValidString(const char *pStr);

#endif
