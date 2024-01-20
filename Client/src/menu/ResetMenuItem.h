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

#include "MenuItem.h"

class ResetMenuItem : public MenuItem
{
public:
    ResetMenuItem(ActionCallback cb);
    void onDisplay(bool active) override;

protected:

};

#endif