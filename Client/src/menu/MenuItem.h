/*
 * MenuItem.h
 *
 *  Created on: Jan 7, 2024
 *      Author: cyberreefguru
 */

#pragma once

#ifndef MenuItem_H
#define MenuItem_H

#include <Arduino.h>
#include <ArduinoLog.h>

#include "ButtonEvent.h"
#include "StateManager.h"
#include "DisplayManager.h"
#include "ActionEventManager.h"
#include "InputEventManager.h"

typedef const char* menu_title_t;
typedef const char* menu_label_t;
typedef const char* menu_prompt_t;


class MenuItem
{
public:
    MenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt);
    virtual ~MenuItem();

    virtual const char* getMenuLabel()
    {
        return menuLabel;
    }
    virtual const char* getMenuTitle()
    {
        return menuTitle;
    }
    virtual const char* getMenuPrompt()
    {
        return menuPrompt;
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
    virtual void onEvent(ButtonEvent be);
    virtual void onDisplay()=0; // must implement
    virtual void onButtonUp(){}
    virtual void onButtonDown(){}
    virtual void onButtonLeft(){}
    virtual void onButtonRight(){}
    virtual void onButtonPush(){}

protected:
    MenuItem();
    const char *menuLabel; // shown when in a list
    const char *menuTitle; // shown when onDisplay called
    const char *menuPrompt; // shown when onDisplay called
    uint8_t numItems = 0; // TODO - move to ListMenuItem or something
    MenuItem **items = nullptr; // TODO - move to ListMenuItem or something
};

#endif