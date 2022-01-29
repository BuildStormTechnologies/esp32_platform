/*******************************************************************************
*
* Filename:     app_main.c
*
* Description:
*               main entry of the application .
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lib_system.h"
#include "lib_ble.h"
#include "lib_wifi.h"
#include "lib_aws.h"
#include "lib_jobs.h"
#include "lib_gpio.h"
#include "lib_flash.h"
#include "lib_delay.h"
#include "lib_print.h"
#include "lib_utils.h"

#include "app_config.h"

/* Macros ------------------------------------------------------------------*/

#define thisModule APP_MODULE_MAIN

#define SHADOW_KEY_LED "LED"
#define SHADOW_KEY_COLOR "COLOR"
#define PUBLISH_TOPIC_STR "devicePubTopic"
#define SUBSCRIBE_TOPIC_STR "deviceSubTopic"

/* User Data Types -----------------------------------------------------------------*/

typedef struct
{
    uint16_t counter;
    char message[32];
} userData_st;

/* Thing Certificates ---------------------------------------------------------*/
extern const uint8_t aws_root_ca_pem_start[] asm("_binary_aws_root_ca_pem_start");

#if (!USE_BLE_FOR_PROVISION)
#if USE_CLAIM_CERTIFICATES
extern const uint8_t claim_certificate_pem_crt_start[] asm("_binary_claim_certificate_pem_crt_start");
extern const uint8_t claim_private_pem_key_start[] asm("_binary_claim_private_pem_key_start");
#else
extern const uint8_t thing_certificate_pem_crt_start[] asm("_binary_thing_certificate_pem_crt_start");
extern const uint8_t thing_private_pem_key_start[] asm("_binary_thing_private_pem_key_start");
#endif
#endif

/* Variables -----------------------------------------------------------------*/

static logLevels_et gDefaultLogLevels_ae[MODULES_MAX] = DEFAULT_LOG_LEVELS;

static mqttMsg_st pubMsg = {0};
static mqttMsg_st subMsg = {0};
static uint32_t gDesiredLedState_u32 = LOW, gReportedLedState_u32 = LOW;
static char desiredColor[LENGTH_AWS_SHADOW_BUFFER] = "GREY", reportedColor[LENGTH_AWS_SHADOW_BUFFER] = "GREY";
static char jobId1[LENGTH_JOB_ID] = {0}, jobId2[LENGTH_JOB_ID] = {0}, jobId3[LENGTH_JOB_ID] = {0}, jobId4[LENGTH_JOB_ID] = {0};

void app_ledBlink()
{
    static uint32_t nextLedChangeTime = 0;
    static bool pinState = LOW;

    if (millis() > nextLedChangeTime)
    {
        nextLedChangeTime = millis() + 400;
        GPIO_pinWrite(LED0_PIN, pinState);
        pinState = !pinState;
    }
}

/**
 * @brief  This function publishes initial device status.
 * @retval None
 */
void app_publishDeviceStatus()
{
    awsThingShadow_st as_shadow[4] = {
        {.keyStr = "thing_name",
         .valType_e = SHADOW_VALUE_TYPE_STRING},
        {.keyStr = "firmware_ver",
         .valType_e = SHADOW_VALUE_TYPE_STRING,
         .value_e.str = APP_VERSION},
        {.keyStr = SHADOW_KEY_LED,
         .valType_e = SHADOW_VALUE_TYPE_UINT,
         .value_e.val_u32 = gDesiredLedState_u32},
        {.keyStr = SHADOW_KEY_COLOR,
         .valType_e = SHADOW_VALUE_TYPE_STRING}};

    strcpy(as_shadow[0].value_e.str, AWS_getThingName());
    strcpy(as_shadow[3].value_e.str, desiredColor);
    AWS_shadowDocumentUpdate(as_shadow, 4, SHADOW_UPDATE_TYPE_ALL);
}

jobsStatus_et app_testJob1_handler(job_st *ps_job)
{
    print_info("%s : %s", ps_job->idStr, ps_job->documentStr);
    print_info("q:%u  c:%u", ps_job->queuedAt_u32, ps_job->currentTimeStamp_u32);
    strcpy(jobId1, ps_job->idStr);
    return JOB_STATUS_IN_PROGRESS; // job accepted
}

jobsStatus_et app_testJob2_handler(job_st *ps_job)
{
    print_info("%s : %s", ps_job->idStr, ps_job->documentStr);
    print_info("q:%u  c:%u", ps_job->queuedAt_u32, ps_job->currentTimeStamp_u32);
    // don't copy job id
    // reject the job
    //    strcpy(jobId2, ps_job->idStr);
    return JOB_STATUS_REJECTED; // job rejected
}

jobsStatus_et app_testJob3_handler(job_st *ps_job)
{
    print_info("%s : %s", ps_job->idStr, ps_job->documentStr);
    print_info("q:%u  c:%u", ps_job->queuedAt_u32, ps_job->currentTimeStamp_u32);
    strcpy(jobId3, ps_job->idStr);
    return JOB_STATUS_IN_PROGRESS; // job accepted
}

jobsStatus_et app_testJob4_handler(job_st *ps_job)
{
    print_info("%s : %s", ps_job->idStr, ps_job->documentStr);
    print_info("q:%u  c:%u", ps_job->queuedAt_u32, ps_job->currentTimeStamp_u32);
    strcpy(jobId4, ps_job->idStr);
    return JOB_STATUS_IN_PROGRESS; // job accepted
}

void app_jobCheck()
{
    if (jobId1[0])
    {
        print_info("%s", jobId1);
        TASK_DELAY_MS(10000);
        JOBS_updateStatus(jobId1, JOB_STATUS_SUCCESSED);
        jobId1[0] = 0;
    }
    else if (jobId2[0])
    {
        print_info("%s", jobId2);
        TASK_DELAY_MS(10000);
        JOBS_updateStatus(jobId2, JOB_STATUS_FAILED);
        jobId2[0] = 0;
    }
    else if (jobId3[0])
    {
        print_info("%s", jobId3);
        // don't update status. Let it timeout
        jobId3[0] = 0;
    }
    else if (jobId4[0])
    {
        print_info("%s", jobId4);
        TASK_DELAY_MS(10000);
        JOBS_updateStatus(jobId4, JOB_STATUS_FAILED);
        jobId4[0] = 0;
    }
}

void app_ledShadowHandler(char *pkey, void *value)
{
    gDesiredLedState_u32 = *(uint8_t *)value;
    print_info("Delta update desired Led : %d", gDesiredLedState_u32);
}

void app_colorShadowHandler(char *pkey, void *value)
{
    if ((strcmp((char *)value, "WHITE") == 0) || (strcmp((char *)value, "RED") == 0) || (strcmp((char *)value, "GREEN") == 0) || (strcmp((char *)value, "BLUE") == 0))
    {
        strcpy(desiredColor, (char *)value);
        print_info("desiredColor:%s reportedColor:%s", desiredColor, reportedColor);
    }
}

void app_publishData()
{
    static uint8_t publishCount = 0;
    static uint32_t nextPublishTime_u32 = 0;

    if ((millis() > nextPublishTime_u32) && (publishCount < 20))
    {
        nextPublishTime_u32 = millis() + 10000;

        pubMsg.payloadLen_u16 = sprintf(pubMsg.payloadStr, "Hello World %03d", publishCount++);
        pubMsg.topicLen_u8 = sprintf(pubMsg.topicStr, PUBLISH_TOPIC_STR);
        print_info("%s", pubMsg.payloadStr);
        AWS_publish(&pubMsg);
    }
}

void app_awsInit()
{
    awsShadow_st led_Shadow = {
        .keyStr = SHADOW_KEY_LED,
        .valType_e = SHADOW_VALUE_TYPE_UINT,
        .callBackHandler = &app_ledShadowHandler,
        .value_e.val_u32 = gDesiredLedState_u32};

    awsShadow_st color_Shadow = {
        .keyStr = SHADOW_KEY_COLOR,
        .valType_e = SHADOW_VALUE_TYPE_STRING,
        .callBackHandler = &app_colorShadowHandler,
        .value_e.str = ""};

    strcpy(color_Shadow.value_e.str, desiredColor);

    if (AWS_shadowDeltaRegister(&led_Shadow))
    {
        print_info("led_Shadow reg success");
    }
    else
    {
        print_error("led_Shadow reg failed");
    }

    if (AWS_shadowDeltaRegister(&color_Shadow))
    {
        print_info("color_Shadow reg success");
    }
    else
    {
        print_error("color_Shadow reg failed");
    }

    if (AWS_subscribe(SUBSCRIBE_TOPIC_STR, QOS0_AT_MOST_ONCE))
    {
        print_info("aws subscribe success");
    }
    else
    {
        print_error("aws subscribe failed");
    }

    if (JOBS_register("TEST_JOB_1", 2, app_testJob1_handler))
    {
        print_info("TEST_JOB_1 reg success");
    }
    else
    {
        print_error("TEST_JOB_1 reg failed");
    }

    if (JOBS_register("TEST_JOB_2", 0, app_testJob2_handler)) // timeout = 0 means no timeout
    {
        print_info("TEST_JOB_2 reg success");
    }
    else
    {
        print_error("TEST_JOB_2 reg failed");
    }

    if (JOBS_register("TEST_JOB_3", 1, app_testJob3_handler))
    {
        print_info("TEST_JOB_3 reg success");
    }
    else
    {
        print_error("TEST_JOB_3 reg failed");
    }

    if (JOBS_register("TEST_JOB_4", 3, app_testJob4_handler))
    {
        print_info("TEST_JOB_4 reg success");
    }
    else
    {
        print_error("TEST_JOB_4 reg failed");
    }

    if (AWS_getThingName())
    {
        app_publishDeviceStatus();
    }
}

void app_userDataTest()
{
    userData_st appData = {0};

    // read operation
    if (FLASH_appDataRead((void *)&appData, sizeof(userData_st)))
    {
        print_info("Data read successfully => counter: %d, Msg: %s",
                   appData.counter,
                   appData.message);
    }
    else
    {
        print_error("Failed to read from flash");
    }

    print_info("Updating data");

    // update variables
    appData.counter++;
    if (appData.counter % 2)
    {
        strcpy(appData.message, "Counter is odd");
    }
    else
    {
        strcpy(appData.message, "Counter is even");
    }

    // write  operation
    if (FLASH_appDataWrite((void *)&appData, sizeof(userData_st)))
    {
        print_info("Data written successfully => Counter: %d, Msg: %s",
                   appData.counter,
                   appData.message);
    }
    else
    {
        print_error("Failed to write to flash");
    }
}

void app_bleCallback(char *pPacketStr, char *pDataStr)
{
    print_info("%s:%s", pPacketStr, pDataStr);
}

void app_eventsCallBackHandler(systemEvents_et eventId)
{
    switch (eventId)
    {
    case EVENT_WIFI_CONNECTED:
        print_info("EVENT_WIFI_CONNECTED");
        break;
    case EVENT_WIFI_DISCONNECTED:
        print_info("EVENT_WIFI_DISCONNECTED");
        break;

    case EVENT_AWS_CONNECTED:
        print_info("EVENT_AWS_CONNECTED");
        break;
    case EVENT_AWS_DISCONNECTED:
        print_info("EVENT_AWS_DISCONNECTED");
        break;

    case EVENT_BLE_CONNECTED:
        print_info("EVENT_BLE_CONNECTED");
        break;
    case EVENT_BLE_DISCONNECTED:
        print_info("EVENT_BLE_DISCONNECTED");
        break;
    case EVENT_BLE_AUTHENTICATED:
        print_info("EVENT_BLE_AUTHENTICATED");
        break;

    default:
        break;
    }
}

void app_task(void *param)
{
    SYSTEM_start();
    BLE_packetRegister("tes", app_bleCallback);
    app_userDataTest();
    while (1)
    {
        switch (SYSTEM_getMode())
        {
        case SYSTEM_MODE_DEVICE_CONFIG:
            app_ledBlink();
            break;

        case SYSTEM_MODE_NORMAL:
            if (AWS_isConnected())
            {
                if (AWS_subMsgRead(&subMsg))
                {
                    print_info("  SUB Message =>  topic:%s  payload:%s", subMsg.topicStr, subMsg.payloadStr);
                }
                else if (gDesiredLedState_u32 != gReportedLedState_u32)
                {
                    gReportedLedState_u32 = gDesiredLedState_u32;
                    GPIO_pinWrite(LED0_PIN, gDesiredLedState_u32);
                    print_info("gDesiredLedState_u32:%d gReportedLedState_u32:%d", gDesiredLedState_u32, gReportedLedState_u32);
                    AWS_shadowUpdate(SHADOW_KEY_LED, &gReportedLedState_u32, SHADOW_UPDATE_TYPE_REPORTED);
                }
                else if (strcmp(desiredColor, reportedColor) != 0)
                {
                    strcpy(reportedColor, desiredColor);
                    print_info("desiredColor:%s reportedColor:%s", desiredColor, reportedColor);
                    AWS_shadowUpdate(SHADOW_KEY_COLOR, reportedColor, SHADOW_UPDATE_TYPE_REPORTED);
                }
                else
                {
                    app_publishData();
                    app_jobCheck();
                }
            }
            break;

        case SYSTEM_MODE_OTA:
            break;

        default:
            break;
        }
        TASK_DELAY_MS(200);
    }
}

/**
* @brief    entry point of the project
* @param    None
* @return   None
*/
void app_main()
{
    systemInitConfig_st s_sysConfig =
    {.pLogLevels_e = gDefaultLogLevels_ae,
     .logModulesCount_u8 = MODULES_MAX,
     .systemEventCallBack = app_eventsCallBackHandler,
     .pDeviceNamePrefixStr = DEVICE_NAME_PREFIX,
     .pLicenseIdStr = LICENSE_ID,

#if (!USE_BLE_FOR_PROVISION)
     .pWifiSsidStr = TEST_WIFI_SSID,
     .pWifiPwdStr = TEST_WIFI_PASSWORD,
#endif

#if USE_BLE_FOR_PROVISION
     .s_awsConfig =
         {.pRootCaStr = (char *)aws_root_ca_pem_start}
#else
#if USE_CLAIM_CERTIFICATES
     .s_awsConfig = {
         .hostNameStr = AWS_IOT_MQTT_HOST,
         .port_u16 = AWS_IOT_MQTT_PORT,
         .pRootCaStr = (char *)aws_root_ca_pem_start,
         .pClaimCertStr = (char *)claim_certificate_pem_crt_start,
         .pClaimPrivateKeyStr = (char *)claim_private_pem_key_start,
         .pClaimTemplateStr = AWS_PROVISION_TEMPLATE_NAME}
#else
     .s_awsConfig =
         {
             .pThingNameStr = MY_THING_NAME,
             .hostNameStr = AWS_IOT_MQTT_HOST,
             .port_u16 = AWS_IOT_MQTT_PORT,
             .pRootCaStr = (char *)aws_root_ca_pem_start,
             .pThingCertStr = (char *)thing_certificate_pem_crt_start,
             .pThingPrivateKeyStr = (char *)thing_private_pem_key_start}
#endif // USE_CLAIM_CERTIFICATES
#endif // USE_BLE_FOR_PROVISION
    };

    if (SYSTEM_init(&s_sysConfig))
    {
        GPIO_pinMode(LED0_PIN, GPIO_MODE_OUTPUT, GPIO_PIN_INTR_DISABLE, NULL);
        GPIO_pinWrite(LED0_PIN, gDesiredLedState_u32);
        app_awsInit();
    }
    else
    {
        BLE_init();
    }

    BaseType_t err = xTaskCreate(&app_task, "app_task", TASK_APP_STACK_SIZE, NULL, TASK_APP_PRIORITY, NULL);
    if (pdPASS != err)
    {
        print_error("\n Error 0x%X in creating app_task \n restarting system\n\r\n\r", err);
        fflush(stdout);
        esp_restart();
    }
}
