/*
 * TargetMenuItem.h
 *
 *  Created on: Jan 6, 2024
 *      Author: cyberreefguru
 */
#ifndef TargetMenuItem_H
#define TargetMenuItem_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "Target.h"
#include "MenuItem.h"

class TargetMenuItem : public MenuItem
{
public:
    TargetMenuItem(Target *target);
    virtual ~TargetMenuItem();

private:
    Target *target;
};

#endif