/*
 * MenuItem.h
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "DisplayManager.h"
#include "ButtonEvent.h"

#include "Helper.h"

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_event.h"
}


typedef std::function<void(void)> MenuCallback;

class MenuItem
{
    // using MenuCallback = std::function<void()>;

public:
    MenuItem();
    void initialize(const char * title, MenuItem *items, uint8_t numItems);
    void onEvent(ButtonEvent be);
    void onDisplay();
    void onActivate(bool b);
    void setEventCallback(std::function<void(ButtonEvent be)> cb);
    void setDisplayCallback(std::function<void()> cb);
    void setActivateCallback(std::function<void(void)> cb);

    std::function<void(ButtonEvent be)>  onEventCallback = nullptr;
    std::function<void(void)> onDisplayCallback = nullptr;
    std::function<void(void)>  onActivateCallback = nullptr;

    // void (*onEventCallback)() = nullptr;
    // void (*onDisplayCallback)() = nullptr;
    // void (*onActivateCallback)() = nullptr;

protected:
    const char * title;
    bool active = false;
    uint8_t numItems = 0;
    MenuItem *items = nullptr;
  
};


class TextMenuItem : public MenuItem
{
public:
    TextMenuItem(const char* title)
    {
        this->title = title;
        this->items = nullptr;
        this->numItems = 0;
    }
    // void initialize(const char * title, MenuItem *items, uint8_t numItems);
    // void onEvent(ButtonEvent be);
    // void onDisplay();
    // void onActivate(bool b);

protected:
  
};




#ifdef __cplusplus
    extern "C"
    {
#endif

// Put external variables here

#ifdef __cplusplus
} // extern "C"
#endif