/*
 * Button.h
 *
 *  Created on: Nov 19, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "ButtonEvent.h"

class Button
{
public:
    Button();
    void initialize(uint8_t pin, ButtonEvent action);

    uint8_t pin;
    bool lastState;
    uint32_t lastTrigger;
    ButtonEvent action;

protected:
private:

};