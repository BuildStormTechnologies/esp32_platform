#ifndef _APP_MAIN_H_
#define _APP_MAIN_H_
#include <stdint.h>
 
typedef enum
{
    SYSTEM_MODE_TEST,
    SYSTEM_MODE_NORMAL,
    SYSTEM_MODE_CONFIG,
    SYSTEM_MODE_OTA,
    SYSTEM_MODE_MAX
} systemMode_et;

systemMode_et SYSTEM_getSystemStatus();
const char* SYSTEM_getSystemStatusString();

#endif