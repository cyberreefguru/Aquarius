/*
 * Indicator.cpp
 *
 *  Created on: Nov 20, 2023
 *      Author: cyberreefguru
 */

#include "Indicator.h"

Indicator::Indicator() {}

void Indicator::initialize(uint32_t c, uint8_t b)
{
    color = c;
    brightness = b;
}

void Indicator::setColor(uint32_t c)
{
    color = c;
}

uint32_t Indicator::getColor()
{
    return color;
}

void Indicator::setBrightness(uint8_t b)
{
    brightness = b;
}

uint8_t Indicator::getBrightness()
{
    return brightness;
}
