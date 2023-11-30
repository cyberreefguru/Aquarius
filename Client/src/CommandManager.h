/*
 * CommandManager.h
 *
 *  Created on: Nov 20, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <Adafruit_NeoPixel.h>

#include "Event.h"
#include "EventManager.h"
#include "Color.h"

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}

class CommandManager
{
public:
    CommandManager();
    void initialize();

protected:
    void eventHandler(void *args, esp_event_base_t base, int32_t id, void *data);
    void commandTask( void * pvParameters );
    TaskHandle_t commandTaskHandle = nullptr;

    QueueHandle_t commandQueueHandle = nullptr;


private:
    bool cmd = false;
    
};

// end of add your includes here
#ifdef __cplusplus
extern "C"
{
#endif

    extern CommandManager commandManager;

#ifdef __cplusplus
} // extern "C"
#endif