
/*
 * Helper.h
 *
 *  Created on: Nov 28, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <WiFi.h>
#include "EventManager.h"

class Helper
{
public:
    Helper();
    static const char * toString(WiFiEvent_t w);
    static const char * toString(Event e);
};
