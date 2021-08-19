/***************************************************************************************************
                                   BuildStorm.com
 ****************************************************************************************************
 * File:   lib_aws.h
 * Version: 1.0
 * Author: Saheblal Bagwan
 * Description: This module implements the AWS jobs funcationality                

Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
A copy of EULA is available for you https://buildstorm.com/eula
**************************************************************************************************/

#ifndef LIB_JOBS_H_
#define LIB_JOBS_H_

#include <stdint.h>

#define MAX_JOB_QUEUES 10
#define MAX_JOB_KEYS 4

typedef struct
{
 uint32_t queuedAt_u32;
 uint32_t currentTimeStamp_u32;
 uint8_t executionNumber_u8;
 uint8_t versionNumber_u8;
 uint8_t jobStatus_u8;
 char jobId[32];
 char clientToken[32];
}jobDetails_t;

typedef enum{
	JOB_STATE_IDLE,
	JOB_STATE_GET_JOB,
	JOB_STATE_SUBS_TO_JOBID,
	JOB_STATE_REQ_FOR_ACTION,
	JOB_STATE_WAIT_FOR_ACTION,
	JOB_STATE_UPDATE_STATUS,
	JOB_STATE_WAIT_FOR_OTA,
	JOB_STATE_DONE,
	JOB_STATE_MAX
}jobsState_et;

void jobs_init();
void jobs_start();
void jobs_process();
void jobs_write(jobDetails_t *ptr);
uint8_t jobs_read(jobDetails_t *ptr);
uint8_t jobs_available(void);
void jobs_clear();
jobsState_et jobs_getState();
void jobs_handleJobList(char *ptr);
int jobs_handleNewAction(char *ptr);
void job_newNotification();
void jobs_completeNotification();
void jobs_goToIdleState();
void jobs_handleNewNotification(char *ptr);
uint8_t jobs_initJobsDone();
void jobs_updateOtaStatus(uint8_t isSuccess);

void JOBS_sync();
void JOBS_init();
void JOBS_start();
void JOBS_callBackHandler(char *topic, char *payload);

#endif /* LIB_JOBS_H_ */
