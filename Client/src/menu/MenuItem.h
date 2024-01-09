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
    virtual void onDisplay()=0; // must implement
    virtual void onButtonUp(){}
    virtual void onButtonDown(){}
    virtual void onButtonLeft(){}
    virtual void onButtonRight(){}
    virtual void onButtonPush(){}

protected:
    MenuItem();
    const char *title;
    const char *label;
    uint8_t numItems = 0; // TODO - move to ListMenuItem or something
    MenuItem **items = nullptr; // TODO - move to ListMenuItem or something
};

#endif