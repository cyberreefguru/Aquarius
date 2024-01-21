/**
 * @brief Renders button with specified text (prompt) or calls doDisplay
 * @note does NOT override doAction or onAction
 * @file ActionButtonItem.h
 * @date Jan 12, 2024
 * @author cyberreefguru
 */
#ifndef ActionButtonItem_H
#define ActionButtonItem_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "MenuItem.h"

class ActionButtonItem : public MenuItem
{
public:
    ActionButtonItem() {}
    ActionButtonItem(menu_prompt_t prompt);
    ActionButtonItem(menu_prompt_t prompt, ActionCallback cb);
    virtual ~ActionButtonItem() {}

    virtual void onDisplay(bool active) override;
};

#endif