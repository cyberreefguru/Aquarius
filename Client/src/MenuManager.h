/*
 * MenuManager.h
 *
 *  Created on: Dec  30, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "StateManager.h"
#include "DisplayManager.h"
#include "ActionEventManager.h"
#include "InputEventManager.h"
#include "Helper.h"

#include <functional>
#include <utility>

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_event.h"
}

class MenuManager
{
public:
    MenuManager();
    void initialize();
    void eventHandler(void *args, esp_event_base_t base, int32_t id, void *data);

private:
    ButtonEvent currentEvent = ButtonEvent::PRESS;
    ButtonAction currentAction = ButtonAction::DOWN;
    bool changed = false;
    uint8_t state = 0;
    uint8_t item = 0;
    uint8_t activeLineNum = 0;


    void displayMainMenu();
    void print(uint8_t curLine, const char * m, bool nl);

};

// end of add your includes here
#ifdef __cplusplus
    extern "C"
    {
#endif

extern MenuManager menuManager;

#ifdef __cplusplus
} // extern "C"
#endif