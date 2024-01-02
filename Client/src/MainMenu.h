/*
 * Menu.h
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "MenuManager.h"
#include "menu/TextMenuItem.h"
#include "Helper.h"

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_event.h"
}

class MainMenu : public MenuItem
{
public:
    MainMenu();
    // void initialize(const char * title, MenuItem *items, uint8_t numItems);
    
protected:

private:
    void exit();
    void save();
};

#ifdef __cplusplus
    extern "C"
    {
#endif

// Put external variables here

#ifdef __cplusplus
} // extern "C"
#endif