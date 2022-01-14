#ifndef _LIB_HTTP_H_
#define _LIB_HTTP_H_

#include "stdutils.h"
#include "lib_json.h"

#define HTTP_TIMEOUT 10000
#define MAX_HTTP_HEADERS 3

typedef enum
{
    HTTP_REQUEST_GET = 0,     /*!< HTTP GET Method */
    HTTP_REQUEST_POST,        /*!< HTTP POST Method */
    HTTP_REQUEST_PUT,         /*!< HTTP PUT Method */
    HTTP_REQUEST_PATCH,       /*!< HTTP PATCH Method */
    HTTP_REQUEST_DELETE,      /*!< HTTP DELETE Method */
    HTTP_REQUEST_HEAD,        /*!< HTTP HEAD Method */
    HTTP_REQUEST_NOTIFY,      /*!< HTTP NOTIFY Method */
    HTTP_REQUEST_SUBSCRIBE,   /*!< HTTP SUBSCRIBE Method */
    HTTP_REQUEST_UNSUBSCRIBE, /*!< HTTP UNSUBSCRIBE Method */
    HTTP_REQUEST_OPTIONS,     /*!< HTTP OPTIONS Method */
    HTTP_REQUEST_MAX,
} httpReq_et;

typedef enum
{
    STATE_HTTP_IDLE,
    STATE_HTTP_START,
    STATE_HTTP_SET_REQUEST_HEADER,
    STATE_HTTP_SET_RESPONSE_HEADER,
    STATE_HTTP_CONNECT,
    STATE_HTTP_SET_URL,
    STATE_HTTP_GET_REQUEST,
    STATE_HTTP_POST_REQUEST,
    STATE_HTTP_POST_DATA,
    STATE_HTTP_WAIT_FOR_POST_RESPONSE,
    STATE_HTTP_READ,
    STATE_HTTP_WAIT_FOR_FILE_HEADER,
    STATE_HTTP_DOWNLOAD_FILE,
    STATE_HTTP_DOWNLOAD_COMPLETE,
    STATE_HTTP_RETRY,
    STATE_HTTP_TIMEOUT,
    STATE_HTTP_FAILED,
    STATE_HTTP_CLOSE,
    STATE_HTTP_MAX
} httpStates_et;

typedef struct
{
    httpReq_et reqType_e;
    tagStructure_st as_headers[MAX_HTTP_HEADERS];
    char *pUrlStr;
    char *pPayloadStr;
    bool header_b8;
} httpConfig_st;

bool HTTP_start(httpConfig_st *ps_config);
uint16_t HTTP_availableToRead();
bool HTTP_read(packet_st *ps_packet);
void HTTP_close();
const char *HTTP_getStateString(httpStates_et state_e);

#endif