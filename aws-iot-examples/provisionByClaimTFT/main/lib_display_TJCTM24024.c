#include "lib_display_TJCTM24024.h"

// ==========================================================
// Define which spi bus to use TFT_VSPI_HOST or TFT_HSPI_HOST
#define SPI_BUS TFT_HSPI_HOST
// ==========================================================

//---------------------
static int Wait(int ms)
{
    vTaskDelay(ms / portTICK_RATE_MS);
    return 1;
}

#define FONT_HEADER_FOOTER DEFAULT_FONT
Font font_header = {0};

#define FONT_STATUS DEJAVU18_FONT
Font font_status = {0};

#define FONT_DETAILS DEJAVU18_FONT //UBUNTU16_FONT
Font font_details = {0};

#define SCREEN_HEADER_X 0
#define SCREEN_HEADER_Y 0
#define SCREEN_HEADER_W (_width - 1)
#define SCREEN_HEADER_H (font_header.y_size + 8)

#define SCREEN_FOOTER_X 0
#define SCREEN_FOOTER_Y (_height - font_header.y_size - 9)
#define SCREEN_FOOTER_W (_width - 1)
#define SCREEN_FOOTER_H (font_header.y_size + 8)

#define SCREEN_STATUS_X 0
#define SCREEN_STATUS_Y (SCREEN_HEADER_Y + SCREEN_HEADER_H + 8)
#define SCREEN_STATUS_W (_width - 1)
#define SCREEN_STATUS_H (font_status.y_size + 8)

#define SCREEN_DETAILS_X 0
#define SCREEN_DETAILS_Y (SCREEN_STATUS_Y + SCREEN_STATUS_H)
#define SCREEN_DETAILS_W (_width - 1)
#define SCREEN_DETAILS_H (SCREEN_FOOTER_Y - (SCREEN_STATUS_Y + SCREEN_STATUS_H))

//---------------------------------
static void disp_header(char *hdr, char *ftr)
{
    TFT_drawRect(SCREEN_HEADER_X, SCREEN_HEADER_Y, SCREEN_HEADER_W, SCREEN_HEADER_H, TFT_CYAN);
    TFT_fillRect(SCREEN_HEADER_X + 1, SCREEN_HEADER_Y + 1, SCREEN_HEADER_W - 2, SCREEN_HEADER_H - 2, _bg);

    TFT_drawRect(SCREEN_FOOTER_X, SCREEN_FOOTER_Y, SCREEN_FOOTER_W, SCREEN_FOOTER_H, TFT_CYAN);
    TFT_fillRect(SCREEN_FOOTER_X + 1, SCREEN_FOOTER_Y + 1, SCREEN_FOOTER_W - 2, SCREEN_FOOTER_H - 2, _bg);

    TFT_setFont(FONT_HEADER_FOOTER, NULL);

    if (hdr)
    {
        TFT_fillRect(SCREEN_HEADER_X + 1, SCREEN_HEADER_Y + 1, SCREEN_HEADER_W - 2, SCREEN_HEADER_H - 2, TFT_BLACK);
        TFT_printWithColor(hdr, CENTER, 4, TFT_LIGHTGREY, TFT_BLACK);
    }

    if (ftr)
    {
        TFT_fillRect(SCREEN_FOOTER_X + 1, SCREEN_FOOTER_Y + 1, SCREEN_FOOTER_W - 2, SCREEN_FOOTER_H - 2, TFT_BLACK);
        TFT_printWithColor(ftr, CENTER, _height - TFT_getfontheight() - 5, TFT_LIGHTGREY, TFT_BLACK);
    }
}

void DISP_clearDetailsScreen()
{
    TFT_drawRect(SCREEN_DETAILS_X, SCREEN_DETAILS_Y, SCREEN_DETAILS_W, SCREEN_DETAILS_H, TFT_BLACK);
    TFT_fillRect(SCREEN_DETAILS_X + 1, SCREEN_DETAILS_Y + 1, SCREEN_DETAILS_W - 2, SCREEN_DETAILS_H - 2, TFT_BLACK);
}

void DISP_detailsScreen(char *thingId, char *msg1, char *msg2)
{
    TFT_setFont(FONT_DETAILS, NULL);

    char dispBuff[100] = {0};
    int y = (dispWin.y2 - dispWin.y1) / 3 - 20;

    sprintf(dispBuff, "\n Thing : %s\n\n Pub   : %s\n\n Sub   : %s", thingId, msg1, msg2);
    TFT_printWithColor(dispBuff, 0, y, TFT_ORANGE, TFT_BLACK);
}

void DISP_provisionScreen(uint8_t provisionState)
{
    char dispBuff[100] = {0};

    TFT_setFont(DEJAVU18_FONT, NULL);

    int offset = TFT_getfontheight() + 4;
    int y = (dispWin.y2 - dispWin.y1) / 3 + 20;
    color_t msgColor = {0};
    msgColor = TFT_ORANGE;

    TFT_printWithColor("Thing", CENTER, y, msgColor, TFT_BLACK);

    switch (provisionState)
    {
    case 0:
        sprintf(dispBuff, "Not Provisioned");
        msgColor = TFT_RED;
        break;
        
    case 1:
        sprintf(dispBuff, " Provisioning.. ");
        msgColor = TFT_LIGHTGREY;
        break;
        
    case 2:
        sprintf(dispBuff, " Provisioned  ");
        msgColor = TFT_DARKGREEN;
        break;
        
    case 3:
        sprintf(dispBuff, "   Rebooting....");
        msgColor = TFT_DARKGREEN;
    break;
    
    default:
        break;
    }

    TFT_setFont(DEJAVU24_FONT, NULL);
    TFT_fillRect(0, y + offset, _width, offset, TFT_BLACK);
    TFT_printWithColor(dispBuff, CENTER, y + offset, msgColor, TFT_BLACK);
}

void DISP_otaScreen(uint8_t otaState)
{
    char dispBuff[100] = {0};

    TFT_setFont(DEJAVU18_FONT, NULL);

    int offset = TFT_getfontheight() + 4;
    int y = (dispWin.y2 - dispWin.y1) / 3 + 20;
    color_t msgColor = {0};
    msgColor = TFT_ORANGE;

    TFT_printWithColor("OTA", CENTER, y, msgColor, TFT_BLACK);

    switch (otaState)
    {
    case 0:
        break;
    
    case 1:
        sprintf(dispBuff, "Job request ");
        msgColor = TFT_LIGHTGREY;
        break;
        
    case 2:
        sprintf(dispBuff, "Start File Download");
        msgColor = TFT_LIGHTGREY;
        break;
        
    case 3:
        sprintf(dispBuff, "In Progress");
        msgColor = TFT_LIGHTGREY;
        break;    
        
    case 4:
        sprintf(dispBuff, "Success...");
        msgColor = TFT_DARKGREEN;
        break; 
        
    case 5:
        sprintf(dispBuff, "Failed");
        msgColor = TFT_RED;
        break;
        
    case 6:
        sprintf(dispBuff, "Rebooting.....");
        msgColor = TFT_DARKGREEN;
    break;
    
    default:
        break;
    }

    TFT_setFont(DEJAVU24_FONT, NULL);
  //  TFT_printWithColor("XXXXXXXXXXXXXXXXXXXXXXXX", CENTER, y + offset, TFT_BLACK, TFT_BLACK);
    
    TFT_fillRect(0, y + offset, _width, offset, TFT_BLACK);

    TFT_printWithColor(dispBuff, CENTER, y + offset, msgColor, TFT_BLACK);
}


void DISP_statusScreen(char *fwVersion, uint8_t wifiState, uint8_t awsState)
{
    static uint8_t wifiToggleBgColor = 0;
    static uint8_t awsToggleBgColor = 0;
    
    TFT_setFont(FONT_DETAILS, NULL);
    TFT_printWithColor(fwVersion, SCREEN_STATUS_X + 10, SCREEN_STATUS_Y, TFT_WHITE, TFT_BLACK);

    TFT_setFont(FONT_STATUS, NULL);

    color_t wifiColor = {0};
    color_t awsColor = {0};
    
    if(wifiState == 1)
    {
        wifiToggleBgColor =!wifiToggleBgColor; 
    }    
    
    if(awsState == 1)
    {
        awsToggleBgColor =!awsToggleBgColor;
    }

    wifiColor = ((wifiState > 1) ? TFT_DARKGREEN : (wifiToggleBgColor?TFT_RED:TFT_BLACK));
    awsColor = ((awsState > 1) ? TFT_DARKGREEN : (awsToggleBgColor?TFT_RED:TFT_BLACK));

    TFT_fillRect(SCREEN_STATUS_X + 165, SCREEN_STATUS_Y - 4, 65, SCREEN_STATUS_H, wifiColor);
    TFT_printWithColor(" WIFI", SCREEN_STATUS_X + 170, SCREEN_STATUS_Y, TFT_WHITE, wifiColor);

    TFT_fillRect(SCREEN_STATUS_X + 245, SCREEN_STATUS_Y - 4, 65, SCREEN_STATUS_H, awsColor);
    TFT_printWithColor(" AWS ", SCREEN_STATUS_X + 250, SCREEN_STATUS_Y, TFT_WHITE, awsColor);
}

void DISP_welcomeScreen()
{
    // TFT_saveClipWin();
    // TFT_resetclipwin();
    // TFT_setclipwin(10, 20, _width - 10, _height - 20);

    TFT_setFont(DEJAVU24_FONT, NULL);

    // int offset = TFT_getfontheight() + 4;
    // int y = (dispWin.y2 - dispWin.y1) / 2;
    // TFT_print("ESP32 AWS", CENTER, y - offset); //DEJAVU24_FONT // 20 char/line
    // TFT_print("Device Provision", CENTER, y);   //DEJAVU24_FONT // 20 char/line
    // TFT_print("By Claim", CENTER, y + offset);  //DEJAVU24_FONT // 20 char/line

    int offset = TFT_getfontheight() + 4;
    int y = (dispWin.y2 - dispWin.y1) / 3;
    TFT_printWithColor("ESP32 AWS", CENTER, y, TFT_LIGHTGREY, TFT_BLACK);                 //DEJAVU24_FONT // 20 char/line
    TFT_printWithColor("Device Provision", CENTER, y + offset, TFT_LIGHTGREY, TFT_BLACK); //DEJAVU24_FONT // 20 char/line
    TFT_printWithColor("By Claim", CENTER, y + 2 * offset, TFT_LIGHTGREY, TFT_BLACK);     //DEJAVU24_FONT // 20 char/line

    // TFT_restoreClipWin();
}

void disp_varInit()
{
    TFT_resetclipwin();
    TFT_setRotation(LANDSCAPE);
    font_header = TFT_getFont(FONT_HEADER_FOOTER);
    font_status = TFT_getFont(FONT_STATUS);
    font_details = TFT_getFont(FONT_DETAILS);

    _fg = TFT_WHITE;
    _bg = TFT_BLACK;
    text_wrap = 1;
}

void DISP_demo()
{
    // disp_varInit();
    // disp_header("DEVICE PROVISION DEMO", "BuildStorm Technologies");

    // DISP_welcomeScreen();
    // Wait(2000);

    DISP_clearDetailsScreen();

    uint8_t wifiState = 0;
    uint8_t awsState = 0;
    uint8_t count = 0;
    DISP_statusScreen("v1.1.1", wifiState, awsState);

    for (uint8_t provisionState = 0; provisionState < 3; provisionState++)
    {
        DISP_provisionScreen(provisionState);
        Wait(2000);
    }

    DISP_clearDetailsScreen();

    while (1)
    {
        count++;
        if (count % 2)
        {
            wifiState++;
        }
        else
        {
            awsState++;
        }
        wifiState = wifiState % 3;
        awsState = awsState % 3;
        DISP_statusScreen("v1.1.1", wifiState, awsState);
        DISP_detailsScreen("esp_CC50E3B6C8D0_74", "ESP Hello 010", "AWS Hello 010");
        Wait(1000);
    }
}

void DISP_init()
{
    esp_err_t ret;

    tft_disp_type = DEFAULT_DISP_TYPE;
    _width = DEFAULT_TFT_DISPLAY_WIDTH;   // smaller dimension
    _height = DEFAULT_TFT_DISPLAY_HEIGHT; // larger dimension
    max_rdclock = 8000000;

    TFT_PinsInit();

    spi_lobo_device_handle_t spi;

    spi_lobo_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO, // set SPI MISO pin
        .mosi_io_num = PIN_NUM_MOSI, // set SPI MOSI pin
        .sclk_io_num = PIN_NUM_CLK,  // set SPI CLK pin
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 6 * 1024,
    };
    spi_lobo_device_interface_config_t devcfg = {
        .clock_speed_hz = 8000000,         // Initial clock out at 8 MHz
        .mode = 0,                         // SPI mode 0
        .spics_io_num = -1,                // we will use external CS pin
        .spics_ext_io_num = PIN_NUM_CS,    // external CS pin
        .flags = LB_SPI_DEVICE_HALFDUPLEX, // ALWAYS SET  to HALF DUPLEX MODE!! for display spi
    };

    // ====================================================================================================================

    vTaskDelay(500 / portTICK_RATE_MS);
    //printf("\r\n==============================\r\n");
    //printf("TFT display DEMO, LoBo 11/2017\r\n");
    //printf("==============================\r\n");
    //printf("Pins used: miso=%d, mosi=%d, sck=%d, cs=%d\r\n", PIN_NUM_MISO, PIN_NUM_MOSI, PIN_NUM_CLK, PIN_NUM_CS);

    //printf("==============================\r\n\r\n");

    // ==================================================================
    // ==== Initialize the SPI bus and attach the LCD to the SPI bus ====

    ret = spi_lobo_bus_add_device(SPI_BUS, &buscfg, &devcfg, &spi);
    assert(ret == ESP_OK);
    //printf("SPI: display device added to spi bus (%d)\r\n", SPI_BUS);
    disp_spi = spi;

    // ==== Test select/deselect ====
    ret = spi_lobo_device_select(spi, 1);
    assert(ret == ESP_OK);
    ret = spi_lobo_device_deselect(spi);
    assert(ret == ESP_OK);

    //printf("SPI: attached display device, speed=%u\r\n", spi_lobo_get_speed(spi));
    //printf("SPI: bus uses native pins: %s\r\n", spi_lobo_uses_native_pins(spi) ? "true" : "false");

    // ================================
    // ==== Initialize the Display ====

    //printf("SPI: display init...\r\n");
    TFT_display_init();
    //printf("OK\r\n");

    // ---- Detect maximum read speed ----
    max_rdclock = find_rd_speed();
    //printf("SPI: Max rd speed = %u\r\n", max_rdclock);

    // ==== Set SPI clock used for display operations ====
    spi_lobo_set_speed(spi, DEFAULT_SPI_CLOCK);
    //printf("SPI: Changed speed to %u\r\n", spi_lobo_get_speed(spi));

    //printf("\r\n---------------------\r\n");
    //printf("Graphics demo started\r\n");
    //printf("---------------------\r\n");

    disp_varInit();
    disp_header("AWS DEVICE PROVISION DEMO", "BuildStorm Technologies");
    DISP_welcomeScreen();
}
