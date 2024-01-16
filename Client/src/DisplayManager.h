/*
 * DisplayManager.h
 *
 *  Created on: Nov 26, 2023
 *      Author: cyberreefguru
 */


#ifndef DisplayManager_H
#define DisplayManager_H

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
    void print(uint8_t d);
    void print(uint16_t d);
    void print(uint32_t d);
    void print(float f);
    void print(double d);
    void print(const char * m);
    void println(const char * m);
    void print(String s);
    void printf(const char *format, ...);
    void println();
    void clear();
    void clearRow(uint8_t row);
    void clearRow(uint8_t srow, uint8_t scol, uint8_t erow, uint8_t ecol);
    void setCursor(uint8_t row, uint8_t col);
    void setTextColor(uint16_t fg);
    void setTextColor(uint16_t fg, uint16_t bg);
    void setBrightness(uint8_t v);
    void dim(bool b);
    void setCursorXY(uint16_t x, uint16_t y);
    void setCursorX(uint16_t x);
    void setCursorY(uint16_t y);
    uint16_t getCursorX();
    uint16_t getCursorY();
    void addCursorX(int16_t x);
    void addCursorY(int16_t y);
    void addCursor(int16_t x, int16_t y);

        
protected:
    Adafruit_SSD1306 ssd1306;
    DisplaySize size;

private:
    bool refresh = false;
    uint8_t brightness = 255;
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

#endif