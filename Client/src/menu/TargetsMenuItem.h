/**
 * @file TargetsMenuItem.h
 * @brief Menu item that lists all targets for editing
 * @date Jan 19, 2024
 * @author cyberreefguru
*/
#ifndef TargetsMenuItem_H
#define TargetsMenuItem_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "ArrayList.h"

#include "ListMenu.h"

#include "TargetMenuItem.h"


class TargetsMenuItem : public ListMenu
{
public:
    TargetsMenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt);
    virtual ~TargetsMenuItem();
    void initialize();
    
protected:

};

#endif