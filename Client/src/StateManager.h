/*
 * State.h
 *
 *  Created on: Nov 20, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <Adafruit_NeoPixel.h>
#include "Event.h"
#include "IndicatorManager.h"
#include "Color.h"

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}

class StateManager
{
public:
    StateManager();
    void initialize();

    Event lastEvent = Event::INITIALIZING;
    bool processing = false;
    bool active = false;
    bool wifi = false;
    int32_t rssi = 0;
    bool mqtt = false;

protected:
    void eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data);

private:
    TaskHandle_t stateTaskHandle = NULL;
    void stateTask(void *pvParameters);
    // State state;
    // bool wifi = false;
    // int32_t rssi = 0;
    // bool mqtt = false;
};

// end of add your includes here
#ifdef __cplusplus
extern "C"
{
#endif

    extern StateManager stateManager;

#ifdef __cplusplus
} // extern "C"
#endif