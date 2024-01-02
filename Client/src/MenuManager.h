/*
 * MenuManager.h
 *
 *  Created on: Dec  30, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "ButtonEvent.h"
#include "StateManager.h"
#include "DisplayManager.h"
#include "ActionEventManager.h"
#include "InputEventManager.h"
#include "Helper.h"

#include <SimpleStack.h>

#include <functional>
#include <utility>

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_event.h"
}

// typedef std::function<void(void)> MenuCallback;

class MenuItem
{
    // using MenuCallback = std::function<void()>;

public:

    MenuItem(const char * title);
    
    void initialize(const char * title, MenuItem **items, uint8_t numItems);

    virtual void onEvent(ButtonEvent be);
    void onDisplay();

    // MenuItem (const MenuItem &) = delete;
    // MenuItem & operator = (const MenuItem &) = delete;

    // void onEvent(MenuItem* item, ButtonEvent be);
    // void onDisplay(MenuItem* item);
    // void onActivate(MenuItem* item, bool b);


    // void setEventCallback(std::function<void(MenuItem* item, ButtonEvent be)> cb);
    // void setDisplayCallback(std::function<void(MenuItem* item)> cb);
    // void setActivateCallback(std::function<void(MenuItem* item, bool b)> cb);

    // std::function<void(MenuItem* item, ButtonEvent be)>  onEventCallback = nullptr;
    // std::function<void(MenuItem* item)> onDisplayCallback = nullptr;
    // std::function<void(MenuItem* item, bool b)>  onActivateCallback = nullptr;

// protected:
    MenuItem();
    const char * title;
    bool active = false;
    uint8_t numItems = 0;
    MenuItem **items = nullptr;
    uint8_t currentItemIndex = 0;
    uint8_t windowStart = 0;

    MenuItem* getActive();
    uint8_t getActiveIndex();
    void activateNext();
    void activatePrevious();


};

class ExitMenuItem : public MenuItem
{
public:
    ExitMenuItem();
    void onEvent(ButtonEvent be);

protected:
  
};



class MenuManager
{
public:
    MenuManager();
    ~MenuManager();
    void initialize();
    void push(MenuItem* item);
    void pop();

    void display();

    void inputEventHandler(void *args, esp_event_base_t base, int32_t id, void *data);
    void actionEventHandler(void *args, esp_event_base_t base, int32_t id, void *data);

private:
    ButtonEvent currentEvent = ButtonEvent::DOWN;
    ButtonAction currentAction = ButtonAction::PRESS;
    bool changed = false;
    uint8_t state = 0;
    uint8_t item = 0;
    uint8_t activeLineNum = 0;
    uint8_t windowStart = 0;
    uint8_t windowEnd = 5;
    MenuItem* currentItem;
    MenuItem* mainMenu;


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