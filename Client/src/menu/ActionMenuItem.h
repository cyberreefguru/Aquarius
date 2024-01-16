/*
 * ActionMenuItem.h
 *
 *  Created on: Jan 12, 2024
 *      Author: cyberreefguru
 */

#ifndef ActionMenuItem_H
#define ActionMenuItem_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "MenuItem.h"

///@brief type definition for onDisplay callback
typedef std::function<void(bool active)> DisplayCallback;

///@brief type definitino for onAction callback
typedef std::function<void()> ActionCallback;

///@brief type definitino for onButtonXXX callback
typedef std::function<void()> ButtonCallback;

class ActionMenuItem : public MenuItem
{
public:
    ActionMenuItem() {}
    ActionMenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt);
    ActionMenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt, ActionCallback cb);
    virtual ~ActionMenuItem() {}

    void setActionCallback(ActionCallback cb);
    void setDisplayCallback(DisplayCallback cb);
    void setButtonCallback(ButtonCallback up, ButtonCallback down,
                           ButtonCallback left, ButtonCallback right,
                           ButtonCallback push);

    virtual void onAction();
    virtual void onDisplay(bool active);
    virtual void onButtonUp() override;
    virtual void onButtonDown() override;
    virtual void onButtonLeft() override;
    virtual void onButtonRight() override;
    virtual void onButtonPush() override;

protected:
    DisplayCallback doDisplay = nullptr;
    ActionCallback doAction = nullptr;
    ButtonCallback doButtonUp = nullptr;
    ButtonCallback doButtonDown = nullptr;
    ButtonCallback doButtonLeft = nullptr;
    ButtonCallback doButtonRight = nullptr;
    ButtonCallback doButtonPush = nullptr;
};

#endif