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
#include "StateManager.h"
#include "DisplayManager.h"
#include "ActionEventManager.h"
#include "InputEventManager.h"
#include "Helper.h"

#include "menu/MenuColor.h"

#include "menu/MenuItem.h"
#include "menu/ListMenu.h"
#include "menu/NumberInputItem.h"
#include "menu/SimpleMenuItem.h"
#include "menu/ExitMenuItem.h"

// #include "menu/ColorListItem.h"
// #include "menu/BrightnessMenuItem.h"


#include <functional>
#include <utility>

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_event.h"
}

// // typedef std::function<void(void)> MenuCallback;

// class MenuItem
// {
//     // using MenuCallback = std::function<void()>;

// public:
//     MenuItem(const char *title, const char *label);
//     virtual ~MenuItem();

//     virtual const char* getTitle()
//     {
//         return title;
//     }
//     virtual const char* getLabel()
//     {
//         return label;
//     }
//     virtual bool hasChildren()
//     {
//         return (numItems>0 && items != nullptr);
//     }
//     virtual uint8_t getNumberChildren()
//     {
//         return numItems;
//     }
//     virtual MenuItem** getChildren()
//     {
//         return items;
//     }
//     virtual void onEvent(ButtonEvent be);
//     virtual void onDisplay();

// protected:
//     MenuItem();
//     const char *title;
//     const char *label;
//     uint8_t numItems = 0;
//     MenuItem **items = nullptr;
// };

// // class LabelListMenu : public MenuItem
// // {
// // public:
// //     LabelListMenu(){}
// //     LabelListMenu(const char *title, const char *label, MenuItem** items, uint8_t numItems);
// //     virtual ~LabelListMenu();
// //     virtual void onEvent(ButtonEvent be);
// //     virtual void onDisplay();

// // protected:
// //     uint8_t activeIndex = 0;
// //     uint8_t windowSize = 0;
// //     uint8_t windowStart = 0;

// //     MenuItem *getActive();
// //     uint8_t getActiveIndex();
// //     void activateNext();
// //     void activatePrevious();
// // private:

// // };

// class ColorMenuItem : public MenuItem
// {
// public:
//     ColorMenuItem(const MenuColor *color);
//     virtual ~ColorMenuItem();
//     virtual void onDisplay();
//     virtual void onEvent(ButtonEvent be);

// private:
//     const MenuColor* color;

// //std::bind(&MainMenu::save, this)
// //onActivateCallback(item, b);

// };

// class ColorListItem : public LabelListMenu
// {
// public:
//     ColorListItem(const char *title, const char *label);
//     virtual ~ColorListItem();
//     virtual void onDisplay();
//     virtual void onEvent(ButtonEvent be);

// //std::bind(&MainMenu::save, this)
// //onActivateCallback(item, b);

// };

// class SimpleMenuItem : public MenuItem
// {
// public:
//     SimpleMenuItem(const char *title);
//     SimpleMenuItem(const char *title, const char* label);
//     virtual ~SimpleMenuItem();
//     virtual void onEvent(ButtonEvent be);
//     virtual void onDisplay();
// };

// class ExitMenuItem : public MenuItem
// {
// public:
//     ExitMenuItem();
//     virtual ~ExitMenuItem();
//     void onDisplay();
//     void onEvent(ButtonEvent be);

// protected:
// };


// class NumberInputItem : public MenuItem
// {
// public:
//     NumberInputItem(){}
//     NumberInputItem(const char *title, const char *label);
//     void initialize(uint32_t *value, uint8_t numChars = 2);
//     virtual ~NumberInputItem();
//     void onEvent(ButtonEvent be);
//     void onDisplay();

// protected:
//     uint32_t *value;
//     uint8_t numDigits = 2;
//     uint8_t curDigit = numDigits - 1;
//     byte *inputBuff = nullptr;
// };

// class BrightnessInputItem : public NumberInputItem
// {
// public:
//     BrightnessInputItem(const char *title, const char *label);
//     void initialize(uint32_t *value, uint8_t numChars = 2);
//     virtual ~BrightnessInputItem();
//     void onEvent(ButtonEvent be);
//     void onDisplay();

// };

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

protected:
    ButtonEvent currentEvent = ButtonEvent::DOWN;
    ButtonAction currentAction = ButtonAction::PRESS;
    bool changed = false;
    uint32_t vNodeId = 0;
    uint32_t vServoStart = 0;
    uint32_t vServoEnd = 0;
    uint32_t vSensor = 0;
    uint32_t vBrightness = 0;
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