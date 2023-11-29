/*
 * Indicator.h
 *
 *  Created on: Nov 20, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}

class Indicator
{
public:
    Indicator();
    void initialize(uint32_t c, uint8_t b);
    void setColor(uint32_t c);
    uint32_t getColor();
    void setBrightness(uint8_t b);
    uint8_t getBrightness();
    
protected:
    uint32_t color = 0;
    uint8_t brightness = 255;
};