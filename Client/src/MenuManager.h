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
    MenuItem(const char *title);
    virtual ~MenuItem();

    virtual const char* getTitle()
    {
        return title;
    }
    virtual bool isActive()
    {
        return active;
    }
    virtual void setActive(bool active)
    {
        this->active = active;
    }

    virtual bool hasChildren()
    {
        return (numItems>0 && items != nullptr);
    }

    virtual uint8_t getNumberChildren()
    {
        return numItems;
    }

    virtual MenuItem** getChildren()
    {
        return items;
    }


    // void initialize(const char *title, MenuItem **items, uint8_t numItems);
    // void setChildren(MenuItem **items, uint8_t numItems);

    virtual void onEvent(ButtonEvent be);
    virtual void onDisplay();

protected:
    MenuItem();
    const char *title;
    bool active = false;
    uint8_t numItems = 0;
    MenuItem **items = nullptr;
    // uint8_t currentItemIndex = 0;
    // uint8_t windowStart = 0;

    // MenuItem *getActive();
    // uint8_t getActiveIndex();
    // void activateNext();
    // void activatePrevious();
};

class ListMenuItem : public MenuItem
{
public:
    ListMenuItem(const char *title, MenuItem** items, uint8_t numItems);
    virtual ~ListMenuItem();
    virtual void onEvent(ButtonEvent be);
    virtual void onDisplay();

    // protected:
    ListMenuItem();
    // const char *title;
    // uint8_t numItems = 0;
    // MenuItem **items = nullptr;
    uint8_t currentItemIndex = 0;
    uint8_t windowStart = 0;

    MenuItem *getActive();
    uint8_t getActiveIndex();
    void activateNext();
    void activatePrevious();
};


class SimpleMenuItem : public MenuItem
{
public:
    SimpleMenuItem(const char *title);
    virtual ~SimpleMenuItem();
    virtual void onEvent(ButtonEvent be);
    virtual void onDisplay();
};

class ExitMenuItem : public MenuItem
{
public:
    ExitMenuItem();
    virtual ~ExitMenuItem();
    void onDisplay();
    void onEvent(ButtonEvent be);

protected:
};

class NumberInputItem : public MenuItem
{
public:
    NumberInputItem(const char *title, const char *label, uint32_t v, uint8_t numChars = 2);
    virtual ~NumberInputItem();
    void initialize(MenuItem **items, uint8_t numItems);
    void onEvent(ButtonEvent be);
    void onDisplay();

protected:
    const char *label;
    uint32_t value;
    uint8_t numDigits = 2;
    uint8_t curDigit = numDigits - 1;
    byte *inputBuff = nullptr;
};

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

    void inputEventHandler(void *args, esp_event_base_t base, int32_t id, void *data);
    void actionEventHandler(void *args, esp_event_base_t base, int32_t id, void *data);

private:
    ButtonEvent currentEvent = ButtonEvent::DOWN;
    ButtonAction currentAction = ButtonAction::PRESS;
    bool changed = false;
    // uint8_t state = 0;
    // uint8_t item = 0;
    // uint8_t activeLineNum = 0;
    // uint8_t windowStart = 0;
    // uint8_t windowEnd = 5;
    // MenuItem *currentItem;
    // MenuItem *mainMenu;

    void print(uint8_t curLine, const char *m, bool nl);
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