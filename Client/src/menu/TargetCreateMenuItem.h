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

class TargetCreateMenuItem : public TargetMenuItem
{
public:
    TargetCreateMenuItem();
    ~TargetCreateMenuItem();

    void initialize();
    // void onDisplay(bool active) override;
    // void onButtonUp() override;
    // void onButtonDown() override;
    // void onButtonLeft() override;
    // void onButtonRight() override;
    // void onButtonPush() override;

    void doOk() override;


protected:
    // Target *target = nullptr;
    
};

#endif