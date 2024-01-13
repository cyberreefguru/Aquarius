/*
 * SimpleMenuItem.h
 *
 *  Created on: Jan 6, 2024
 *      Author: cyberreefguru
 */

#ifndef SMI_H
#define SMI_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

// #include "MenuItem.h"
#include "MenuManager.h"

class SimpleMenuItem : public MenuItem
{
public:
    SimpleMenuItem(menu_title_t title);
    SimpleMenuItem(menu_label_t label, menu_title_t title);
    SimpleMenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt);
    virtual ~SimpleMenuItem();
    //virtual void onDisplay();
    virtual void onDisplay(bool active) override;
    void onButtonPush() override;
    void onButtonLeft() override;
    void onButtonRight() override;
};

#endif