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

#include "Color.h"
#include "ActionEvent.h"
#include "DisplayManager.h"
#include "IndicatorManager.h"

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
    void initializeDisplay();
    void display();

    ActionEvent lastEvent = ActionEvent::INITIALIZING;
    uint32_t startTime = 0;
    bool configure = false;
    bool processing = false;
    bool active = false;
    bool wifi = false;
    bool mqtt = false;
    int32_t rssi = 0;

protected:

private:
    TaskHandle_t stateTaskHandle = NULL;
    void eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data);
    void stateTask(void *pvParameters);

    void setUpTime(bool refresh = false);
    void setStatusMessage(const char * msg, bool refresh=false);
    void setNetworkStatus(bool refresh=false);
    void setMemory(bool refresh=false);
    void setNode(bool refresh=false);

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