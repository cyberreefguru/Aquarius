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
    ColorMenuItem(uint8_t index);
    virtual ~ColorMenuItem();

private:
    uint8_t index;
};

#endif