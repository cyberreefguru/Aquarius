/**
 * @brief menu item to reset preferences
 * @file TargetCreateMenuItem.h
 * @date Jan 14, 2024
 * @author cyberreefguru
 * 
*/
#ifndef ResetMenuItem_H
#define EMI_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "MenuItem.h"

class ResetMenuItem : public MenuItem
{
public:
    ResetMenuItem(ActionCallback cb);
    void onDisplay(bool active) override;

protected:

};

#endif