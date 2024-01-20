/*
 * ExitMenuItem.h
 *
 *  Created on: Jan 6, 2024
 *      Author: cyberreefguru
 */

#ifndef ExitMenuItem_H
#define ExitMenuItem_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "MenuItem.h"

class ExitMenuItem : public MenuItem
{
public:
    ExitMenuItem();
    virtual ~ExitMenuItem();
    void onDisplay(bool active) override;
    void onButtonRight() override;
    void onButtonPush() override;


protected:
};

#endif