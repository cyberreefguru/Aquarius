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
#include "menu/MenuColor.h"

class ColorMenuItem : public MenuItem
{
public:
    ColorMenuItem(const MenuColor *color);
    virtual ~ColorMenuItem();
    void onDisplay(bool active) override;
    void onButtonPush() override;

private:
    const MenuColor* color;

//std::bind(&MainMenu::save, this)
//onActivateCallback(item, b);

};

#endif