
/*
 * MenuColor.h
 *
 *  Created on: Jan 4, 2024
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "Color.h"

class MenuColor
{
public:
    MenuColor(const char *name, const char *label, Color value);
    const char *name;
    const char *label;
    Color value;
};

// end of add your includes here
#ifdef __cplusplus
extern "C"
{
#endif

    extern const MenuColor colorWhite;
    extern const MenuColor colorBlack;
    extern const MenuColor colorPink;
    extern const MenuColor colorRed;
    extern const MenuColor colorMagenta;
    extern const MenuColor colorPurple;
    extern const MenuColor colorLightOrange;
    extern const MenuColor colorOrange;
    extern const MenuColor colorDarkOrange;
    extern const MenuColor colorLightYellow;
    extern const MenuColor colorYellow;
    extern const MenuColor colorYellowGreen;
    extern const MenuColor colorLightGreen;
    extern const MenuColor colorGreen;
    extern const MenuColor colorDarkGreen;
    extern const MenuColor colorLightBlue;
    extern const MenuColor colorBlue;
    extern const MenuColor colorNavyBlue;
    extern const MenuColor colorCyan;
    extern const MenuColor colorDarkCyan;

    extern const MenuColor *menuColors[];
    extern const uint8_t numMenuColors;

#ifdef __cplusplus
} // extern "C"
#endif
