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

#include "MenuManager.h"

enum class ActionMenuType
{
    OK = 0,
    CANCEL,
};
inline constexpr unsigned operator+(ActionMenuType const val) { return static_cast<unsigned>(val); }
inline const char *operator++(ActionMenuType c)
{
    switch (c)
    {
    case ActionMenuType::OK:
        return "OK";
        break;
    case ActionMenuType::CANCEL:
        return "CANCEL";
        break;
    }
}

typedef std::function<void()> ActionCallback;
typedef std::function<void()> ButtonCallback;

class ActionMenuItem : public MenuItem
{
public:
    ActionMenuItem() {}
    ActionMenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt, ActionCallback cb);
    virtual ~ActionMenuItem() {}

    void setActionCallback(ActionCallback cb);
    void setButtonCallback(ButtonCallback up, ButtonCallback down,
                           ButtonCallback left, ButtonCallback right,
                           ButtonCallback push);

    void onAction();
    void onDisplay(bool active);
    //virtual void onDisplay() override;
    virtual void onButtonUp() override;
    virtual void onButtonDown() override;
    virtual void onButtonLeft() override;
    virtual void onButtonRight() override;
    virtual void onButtonPush() override;


private:
    ActionCallback doAction = nullptr;
    ButtonCallback doButtonUp = nullptr;
    ButtonCallback doButtonDown = nullptr;
    ButtonCallback doButtonLeft = nullptr;
    ButtonCallback doButtonRight = nullptr;
    ButtonCallback doButtonPush = nullptr;
};

#endif