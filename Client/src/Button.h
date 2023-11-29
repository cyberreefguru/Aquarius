/*
 * Button.h
 *
 *  Created on: Nov 19, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

class Button
{
public:
    Button();
    void initialize(uint8_t pin);
    bool get();
    void set();
    void reset();
    
protected:
uint8_t pin;
    bool value;
    uint32_t lastTrigger;
};