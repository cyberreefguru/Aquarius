/*
 * ColorMenuItem.h
 *
 *  Created on: Jan 6, 2024
 *      Author: cyberreefguru
 */
#ifndef CMI_H
#define CMI_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "MenuItem.h"
#include "ListMenuItem.h"
#include "menu/MenuColor.h"

class ColorMenuItem : public MenuItem
{
public:
    ColorMenuItem(const MenuColor *color);
    virtual ~ColorMenuItem();
    virtual void onDisplay();
    virtual void onEvent(ButtonEvent be);

private:
    const MenuColor* color;

//std::bind(&MainMenu::save, this)
//onActivateCallback(item, b);

};

#endif