/*
 * MenuItem.h
 *
 *  Created on: Jan 6, 2024
 *      Author: cyberreefguru
 */

#pragma once

#ifndef MI_H
#define MI_H

#include <Arduino.h>
#include <ArduinoLog.h>

#include "ButtonEvent.h"
#include "StateManager.h"
#include "DisplayManager.h"
#include "ActionEventManager.h"
#include "InputEventManager.h"

class MenuItem
{
public:
    MenuItem(const char *title, const char *label);
    virtual ~MenuItem();

    virtual const char* getTitle()
    {
        return title;
    }
    virtual const char* getLabel()
    {
        return label;
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
    virtual void onDisplay();

protected:
    MenuItem();
    const char *title;
    const char *label;
    uint8_t numItems = 0;
    MenuItem **items = nullptr;
};

#endif