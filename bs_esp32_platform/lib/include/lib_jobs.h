/*
 * lib_jobs.h
 *
 *  Created on: 27 Apr 2021
 *      Author: Saheblal Bagwan
 */

#ifndef LIB_JOBS_H_
#define LIB_JOBS_H_

#include "stdutils.h"

#define LENGTH_JOB_DOCUMENT 256 // should be greaterr than LENGTH_OTA_URL
#define LENGTH_JOB_ID 32
#define LENGTH_JOB_CLIENT_TOKEN 32

typedef enum
{
    JOB_STATUS_IN_PROGRESS,
    JOB_STATUS_SUCCESSED,
    JOB_STATUS_FAILED,
    JOB_STATUS_REJECTED,
    JOB_STATUS_MAX,
} jobsStatus_et;

typedef struct
{
    uint32_t queuedAt_u32;
    uint32_t currentTimeStamp_u32;
    char idStr[LENGTH_JOB_ID];
    char documentStr[LENGTH_JOB_DOCUMENT];
} job_st;

typedef jobsStatus_et (*jobCallBack_t)(job_st *ps_job);

bool JOBS_register(char *pJobActionStr, uint8_t timeoutMin_u8, jobCallBack_t callbackHandler);
void JOBS_updateStatus(char *pJobIdStr, jobsStatus_et status_e);

#endif /* LIB_JOBS_H_ */
