/*
 * Display.h
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

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}

class Display
{
public:
    Display();
    void initialize();
    void eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data);
    
protected:
    Adafruit_SSD1306 ssd1306;

private:
    const char * statusMessage;
    void setStatusMessage(const char * msg);
    void setNetworkStatus();
    void setIpAddress();
    void setMemory();
    void clearRow(uint8_t row);
    void setCursor(uint8_t row, uint8_t col);
    void displayTask( void * pvParameters );
    TaskHandle_t displayTaskHandle = NULL;


};

// end of add your includes here
#ifdef __cplusplus
    extern "C"
    {
#endif

    extern Display display;

#ifdef __cplusplus
} // extern "C"
#endif