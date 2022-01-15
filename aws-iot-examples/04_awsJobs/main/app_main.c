#include <string.h>
#include "lib_system.h"
#include "lib_jobs.h"
#include "lib_gpio.h"
#include "lib_flash.h"
#include "lib_delay.h"
#include "lib_print.h"
#include "stdutils.h"
#include "app_config.h"

#include "lib_json.h"

#define thisModule APP_MODULE_MAIN
#define MAX_LED_BLINK_COUNT 5

/* Thing Certificates ---------------------------------------------------------*/
extern const uint8_t aws_root_ca_pem_start[] asm("_binary_aws_root_ca_pem_start");
extern const uint8_t claim_certificate_pem_crt_start[] asm("_binary_claim_certificate_pem_crt_start");
extern const uint8_t claim_private_pem_key_start[] asm("_binary_claim_private_pem_key_start");

/* Variables -----------------------------------------------------------------*/
static logLevels_et gDefaultLogLevels_ae[MODULES_MAX] = DEFAULT_LOG_LEVELS;
static char gJobIdStr[LENGTH_JOB_ID] = {0};
static char gJobDocumentStr[LENGTH_JOB_DOCUMENT] = {0};
static bool gJobReceived_b8 = FALSE;

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
    case EVENT_BLE_AUTHENTICATED:
        print_info("EVENT_BLE_AUTHENTICATED");
        break;
    case EVENT_BLE_DISCONNECTED:
        print_info("EVENT_BLE_DISCONNECTED");
        break;

    default:
        break;
    }
}

jobsStatus_et app_jobHandlerLed(job_st *ps_job)
{
    print_info("%s : %s", ps_job->idStr, ps_job->documentStr);

    // copy gJobIdStr & gJobDocumentStr
    strcpy(gJobIdStr, ps_job->idStr);
    strcpy(gJobDocumentStr, ps_job->documentStr);

    // handle the operation in application task
    gJobReceived_b8 = true;

    return JOB_STATUS_IN_PROGRESS;
}

void app_jobCheck()
{
    // job received? perform operation
    if (gJobReceived_b8)
    {
        gJobReceived_b8 = FALSE;

        uint32_t countValue_u32 = 0;
        uint32_t onTime_u32 = 0;
        uint32_t offTime_u32 = 0;
        char countStr[4] = {0};
        char onTimeStr[4] = {0};
        char offTimeStr[4] = {0};

        // variable for extracting json key-value pair
        tagStructure_st jobKeyValuePair[3] = {
            {"count", countStr},
            {"onTime", onTimeStr},
            {"offTime", offTimeStr}};

        // parse job document to initialize count value
        if (JSON_processString(gJobDocumentStr, jobKeyValuePair, 3))
        {
            countValue_u32 = util_getNumFromString(countStr);
            onTime_u32 = util_getNumFromString(onTimeStr);
            offTime_u32 = util_getNumFromString(offTimeStr);

            print_info("blink %d times => ON:%dms OFF:%dms", countValue_u32, onTime_u32, offTime_u32);
            if (countValue_u32 < MAX_LED_BLINK_COUNT)
            {
                // blink 3 times
                for (uint32_t i = 0; i < countValue_u32; i++)
                {
                    if (onTime_u32)
                    {
                        GPIO_pinWrite(LED0_PIN, HIGH);
                        TASK_DELAY_MS(onTime_u32);
                    }
                    if (offTime_u32)
                    {
                        GPIO_pinWrite(LED0_PIN, LOW);
                        TASK_DELAY_MS(offTime_u32);
                    }
                }

                JOBS_updateStatus(gJobIdStr, JOB_STATUS_SUCCESSED);
            }
            else
            {
                print_error("Error: blink count %d is greater than allowed blinks (%d)", countValue_u32, MAX_LED_BLINK_COUNT);
                JOBS_updateStatus(gJobIdStr, JOB_STATUS_FAILED);
            }
        }
        else
        {
            print_error("Error: Invalid job document: %s", gJobDocumentStr);
        }
    }
}

void app_task(void *param)
{
    uint32_t nextMsgTime_u32 = 0;

    SYSTEM_start();
	
    while (1)
    {
        switch (SYSTEM_getMode())
        {
        case SYSTEM_MODE_CONFIG:
            if (millis() > nextMsgTime_u32)
            {
                nextMsgTime_u32 = millis() + 2000;

                if (FLASH_isDeviceRegistered())
                {
                    print_info("Device successfully provisioned");
                }
                else
                {
                    print_info("Device is not provisioned");
                }
            }
            break;

        case SYSTEM_MODE_NORMAL:
            if (AWS_isConnected())
            {
                app_jobCheck();
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

void app_main()
{
    systemInitConfig_st s_sysConfig = {
        .pLogLevels_e = gDefaultLogLevels_ae,
        .logModulesCount_u8 = MODULES_MAX,
        .systemEventCallBack = app_eventsCallBackHandler,
        .pDeviceNamePrefixStr = DEVICE_NAME_PREFIX,
        .pLicenseIdStr = LICENSE_ID,

        .pWifiSsidStr = TEST_WIFI_SSID,
        .pWifiPwdStr = TEST_WIFI_PASSWORD,

        .s_awsConfig = {
            .hostNameStr = AWS_IOT_MQTT_HOST,
            .port_u16 = AWS_IOT_MQTT_PORT,
            .pRootCaStr = (char *)aws_root_ca_pem_start,
            .pClaimCertStr = (char *)claim_certificate_pem_crt_start,
            .pClaimPrivateKeyStr = (char *)claim_private_pem_key_start,
            .pClaimTemplateStr = AWS_PROVISION_TEMPLATE_NAME}};

    GPIO_pinMode(LED0_PIN, GPIO_MODE_OUTPUT, GPIO_PIN_INTR_DISABLE, NULL);
    GPIO_pinWrite(LED0_PIN, LOW);

    bool initSuccess = SYSTEM_init(&s_sysConfig);

    if (initSuccess)
    {
        if (JOBS_register("blink", 0, app_jobHandlerLed))
        {
            print_info("blink job reg success");
        }
        else
        {
            print_error("blink job reg failed");
        }

        if (pdFALSE == xTaskCreate(&app_task, "app_task", TASK_APP_STACK_SIZE, NULL, TASK_APP_PRIORITY, NULL))
        {
            print_error("\n Error creating app_task \n restarting system\r\n\r\n");
            esp_restart();
        }
    }
}
