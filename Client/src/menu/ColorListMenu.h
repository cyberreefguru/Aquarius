/*
 * ColorListMenu.h
 *
 *  Created on: Jan 7, 2024
 *      Author: cyberreefguru
 */
#ifndef ColorListMenu_H
#define ColorListMenu_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "ListMenu.h"


class ColorListMenu : public ListMenu
{
public:
    ColorListMenu(menu_label_t label, menu_title_t title, menu_prompt_t prompt, const char* key);
    virtual ~ColorListMenu();
    // virtual void onDisplay();
    virtual void onDisplay(bool active) override;
    virtual void onButtonPush() override;

    // std::bind(&MainMenu::save, this)
    // onActivateCallback(item, b);
};

#endif