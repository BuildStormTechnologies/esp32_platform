#ifndef _LIB_PRINT_H_
#define _LIB_PRINT_H_

#include "esp_system.h"
#include "esp_types.h"
#include "lib_config.h"
#include "stdutils.h"

/***************************************************************************************************
                             Function Prototypes
 ***************************************************************************************************/
void print_setLogLevel(menusLibModule_et module_e, logLevels_et logLevel_e);
void print_setDefaultLogLevel(uint8_t maxModules_u8, logLevels_et *pLogLevels_e);
void print_serial(menusLibModule_et module_e, logLevels_et logLevel_e, const char *pFunNameStr, const char *pArgListStr, ...);
bool print_isLogsEnabled();
void print_enableLogs();
void print_disableLogs();

#define print_verbose(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_VERBOSE, __func__, var_arg_list)
#define print_error(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_ERROR, __func__, var_arg_list)
#define print_info(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_INFO, __func__, var_arg_list)
#define print_debug(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_DEBUG, __func__, var_arg_list)

#define print_verbose_raw(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_VERBOSE, NULL, var_arg_list)
#define print_error_raw(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_ERROR, NULL, var_arg_list)
#define print_info_raw(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_INFO, NULL, var_arg_list)
#define print_debug_raw(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_DEBUG, NULL, var_arg_list)

#define PRINTF printf

/**************************************************************************************************/

#endif /* LIB_PRINT_H_ */
