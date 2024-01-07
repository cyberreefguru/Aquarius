/*
 * SimpleMenuItem.h
 *
 *  Created on: Jan 6, 2024
 *      Author: cyberreefguru
 */

#ifndef SMI_H
#define SMI_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

// #include "MenuItem.h"
#include "MenuManager.h"

class SimpleMenuItem : public MenuItem
{
public:
    SimpleMenuItem(const char *title);
    SimpleMenuItem(const char *title, const char* label);
    virtual ~SimpleMenuItem();
    virtual void onEvent(ButtonEvent be);
    virtual void onDisplay();
};

#endif