
/*
 * Helper.h
 *
 *  Created on: Nov 28, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <WiFi.h>

#include "Command.h"
#include "ActionEvent.h"
#include "ActionEventManager.h"


class Helper
{
public:
    Helper();
    static const void fatal(const char * msg);
    static const char * toString(WiFiEvent_t w);
};
