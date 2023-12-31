/*
 * DisplayManager.h
 *
 *  Created on: Nov 26, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "PreferenceManager.h"

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}


#define FONT_HEIGHT 8
#define FONT_WIDTH 6
#define STATUS_ROW 0
#define STATUS_COL 8
#define WIFI_ROW 2
#define WIFI_COL 0
#define MQTT_ROW 2
#define MQTT_COL 11
#define IP_ADDRESS_ROW 4
#define IP_ADDRESS_COL 0
#define MEMORY_ROW 6
#define MEMORY_COL 0
#define NODE_ROW 0
#define NODE_COL 0
#define UPTIME_ROW 7
#define UPTIME_COL 0

class DisplayManager
{
public:
    DisplayManager();
    void initialize();
    // void eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data);
    void setRefresh(bool r=true);
    void setSize(DisplaySize size);
    void print(const char * m);
    void print(String s);
    void println(const char * m);
    void printf(const char *format, ...);
    void clear();
    void clearRow(uint8_t row);
    void clearRow(uint8_t srow, uint8_t scol, uint8_t erow, uint8_t ecol);
    void setCursor(uint8_t row, uint8_t col);
    void setTextColor(uint16_t fg);
    void setTextColor(uint16_t fg, uint16_t bg);


protected:
    Adafruit_SSD1306 ssd1306;
    DisplaySize size;

private:
    bool refresh = false;
    void displayTask( void * pvParameters );
    TaskHandle_t displayTaskHandle = NULL;

};

// end of add your includes here
#ifdef __cplusplus
    extern "C"
    {
#endif

    extern DisplayManager displayManager;

#ifdef __cplusplus
} // extern "C"
#endif