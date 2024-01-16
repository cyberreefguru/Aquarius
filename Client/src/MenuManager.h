/*
 * MenuManager.h
 *
 *  Created on: Dec  30, 2023
 *      Author: cyberreefguru
 */

#ifndef MM_H
#define MM_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include <SimpleStack.h>

#include "ButtonEvent.h"

#include "menu/MenuItem.h"

#include <functional>
#include <utility>

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_event.h"
}

typedef std::function<void(void)> MenuCallback;

class MenuManager
{
public:
    MenuManager();
    virtual ~MenuManager();
    void initialize();
    void push(MenuItem *item);
    MenuItem* peek();
    void pop();

    void display();
    uint8_t getScreenMaxX()
    {
        return 21;
    }
    uint8_t getScreenMaxY()
    {
        return 7;
    }

    void inputEventHandler(void *args, esp_event_base_t base, int32_t id, void *data);
    void actionEventHandler(void *args, esp_event_base_t base, int32_t id, void *data);

    void doExit(bool active);
    void onResetPush();
    void popAndDisplay();
    
    void doNodeId();
    void doScreenBrightness();
    void doLedBrightness();
    void doSensor();
    void doServoStart();
    void doServoEnd();

protected:
    ButtonEvent currentEvent = ButtonEvent::DOWN;
    ButtonAction currentAction = ButtonAction::PRESS;
    bool changed = false;

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

#endif