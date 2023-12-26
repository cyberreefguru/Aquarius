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

#include "Event.h"
#include "EventManager.h"
#include "StateManager.h"
#include "PreferenceManager.h"

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}

class DisplayManager
{
public:
    DisplayManager();
    void initialize();
    void eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data);
    void setSize(DisplaySize size);
    
protected:
    Adafruit_SSD1306 ssd1306;
    DisplaySize size;

private:
    bool refresh = false;
    void setStatusMessage(const char * msg, bool refresh=false);
    void setNetworkStatus(bool refresh=false);
    void setMemory(bool refresh=false);
    void setNode(bool refresh=false);
    void clearRow(uint8_t row);
    void clearRow(uint8_t srow, uint8_t scol, uint8_t erow, uint8_t ecol);
    void setCursor(uint8_t row, uint8_t col);
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