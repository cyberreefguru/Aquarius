/*
 * InputEventManager.h
 *
 *  Created on: Nov 20, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "ButtonEvent.h"
#include "StateManager.h"
#include "Helper.h"

#include <functional>
#include <utility>

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_event.h"
}

ESP_EVENT_DECLARE_BASE(INPUT_BASE);

class InputEventManager
{
public:
    InputEventManager();
    void initialize();
    esp_err_t postEvent(ButtonAction event, ButtonEvent *action);
    esp_err_t addEventHandler(esp_event_handler_t _hand);
    void defaultEventHandler(void *args, esp_event_base_t base, int32_t id, void *data);

private:
    esp_event_loop_handle_t inputHandler;
    esp_event_loop_args_t inputArgs;
};

// end of add your includes here
#ifdef __cplusplus
    extern "C"
    {
#endif

    extern InputEventManager inputEventManager;

#ifdef __cplusplus
} // extern "C"
#endif