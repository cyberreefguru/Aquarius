/*
 * ActionButtonItem.h
 *
 *  Created on: Jan 12, 2024
 *      Author: cyberreefguru
 */

#ifndef ActionButtonItem_H
#define ActionButtonItem_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "ActionMenuItem.h"


class ActionButtonItem : public ActionMenuItem
{
public:
    ActionButtonItem() {}
    ActionButtonItem(menu_prompt_t prompt, ActionCallback cb);
    virtual ~ActionButtonItem() {}

    virtual void onDisplay(bool active) override;

private:

};

#endif