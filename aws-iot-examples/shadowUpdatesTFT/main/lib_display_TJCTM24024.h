#include <time.h>
#include <errno.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "tftspi.h"
#include "tft.h"

void DISP_init();
void DISP_demo();
void DISP_clearDetailsScreen();
void DISP_detailsScreen(char *thingId, char *msg1, char *msg2);
void DISP_shadowUpdateScreen(char *thingId, char *led, char *color);
void DISP_provisionScreen(uint8_t provisionState);
void DISP_otaScreen(uint8_t otaState);
void DISP_statusScreen(char *fwVersion, uint8_t wifiState, uint8_t awsState);
void DISP_welcomeScreen();
