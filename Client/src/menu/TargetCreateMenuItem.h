/**
 * @brief menu item to create a new target
 * @file TargetCreateMenuItem.h
 * @date Jan 23, 2024
 * @author cyberreefguru
 * 
*/
#ifndef TargetCreateMenuItem_H
#define EMI_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "TargetMenuItem.h"

class TargetCreateMenuItem : public MenuItem
{
public:
    TargetCreateMenuItem(ActionCallback cb);

    void initialize();
    void onDisplay(bool active) override;
    void onButtonPush() override;

protected:
    Target *target = nullptr;
    TargetMenuItem *tmi = nullptr;

};

#endif