/*
 * ExitMenuItem.h
 *
 *  Created on: Jan 6, 2024
 *      Author: cyberreefguru
 */

#ifndef EMI_H
#define EMI_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "MenuManager.h"

class ExitMenuItem : public MenuItem
{
public:
    ExitMenuItem();
    virtual ~ExitMenuItem();
    void onDisplay();
    void onEvent(ButtonEvent be);

protected:
};

#endif