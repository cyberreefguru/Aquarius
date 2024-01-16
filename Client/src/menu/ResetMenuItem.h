/*
 * ResetMenuItem.h
 *
 *  Created on: Jan 14, 2024
 *      Author: cyberreefguru
 */

#ifndef ResetMenuItem_H
#define EMI_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

// #include "MenuManager.h"

#include "MenuItem.h"
#include "ActionMenuItem.h"

class ResetMenuItem : public ActionMenuItem
{
public:
    ResetMenuItem();
    virtual ~ResetMenuItem(){}
    void onDisplay(bool active) override;
    // void onAction();
    void onButtonUp() override;
    void onButtonDown() override;
    void onButtonLeft() override;
    void onButtonRight() override;
    void onButtonPush() override;

protected:

};

#endif