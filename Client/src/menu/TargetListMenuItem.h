/**
 * @file TargetListMenuItem.h
 * @brief Menu item that lists all targets for editing
 * @date Jan 19, 2024
 * @author cyberreefguru
*/
#ifndef TargetListMenuItem_H
#define TargetListMenuItem_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "ArrayList.h"

#include "ListMenu.h"

#include "TargetMenuItem.h"


class TargetListMenuItem : public ListMenu
{
public:
    TargetListMenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt);
    virtual ~TargetListMenuItem();
    void initialize();
    
protected:

};

#endif