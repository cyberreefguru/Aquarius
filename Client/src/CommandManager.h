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
#include <ArduinoJson.h>

#include "Command.h"
#include "ActionEvent.h"
#include "ActionEventManager.h"

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
    char eventData[CMD_MAX_SIZE];
    void parse();
    void doAction(Command& c);
    void doResponse(Command& c);
    void doLog(Command& c);
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