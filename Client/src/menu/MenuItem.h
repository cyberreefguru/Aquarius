/*
 * MenuItem.h
 *
 *  Created on: Jan 7, 2024
 *      Author: cyberreefguru
 */

#pragma once

#ifndef MenuItem_H
#define MenuItem_H

#include <Arduino.h>
#include <ArduinoLog.h>

#include "ButtonEvent.h"

/// @brief type for menu titles
typedef const char *menu_title_t;

/// @brief type for menu labels
typedef const char *menu_label_t;

/// @brief type for menu prompts
typedef const char *menu_prompt_t;

///@brief type definition for onDisplay callback
typedef std::function<void(bool active)> DisplayCallback;

///@brief type definitino for onAction callback
typedef std::function<void()> ActionCallback;

///@brief type definitino for onButtonXXX callback
typedef std::function<void()> ButtonCallback;

/**
 * @brief base class for menu items; provide default funtionality that can be overriden
 */
class MenuItem
{
public:
    MenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt);
    virtual ~MenuItem(){}

    const char *getMenuLabel()
    {
        return menuLabel;
    }
    const char *getMenuTitle()
    {
        return menuTitle;
    }
    const char *getMenuPrompt()
    {
        return menuPrompt;
    }

    void setActionCallback(ActionCallback cb);
    void setDisplayCallback(DisplayCallback cb);
    void setLabelDisplayCallback(DisplayCallback cb);
    void setButtonCallback(ButtonCallback up, ButtonCallback down,
                           ButtonCallback left, ButtonCallback right,
                           ButtonCallback push);

    virtual void onEvent(ButtonEvent be);
    virtual void onDisplay(bool active);
    virtual void onLabelDisplay(bool active);
    virtual void onAction();
    virtual void onButtonUp();
    virtual void onButtonDown();
    virtual void onButtonLeft();
    virtual void onButtonRight();
    virtual void onButtonPush();

protected:
    MenuItem();
    const char *menuLabel;      // shown when in a list
    const char *menuTitle;      // shown when onDisplay called
    const char *menuPrompt;     // shown when onDisplay called

    DisplayCallback doDisplay = nullptr;
    DisplayCallback doLabelDisplay = nullptr;
    ActionCallback doAction = nullptr;
    ButtonCallback doButtonUp = nullptr;
    ButtonCallback doButtonDown = nullptr;
    ButtonCallback doButtonLeft = nullptr;
    ButtonCallback doButtonRight = nullptr;
    ButtonCallback doButtonPush = nullptr;

};

#endif