/*
 * MultiActionItem.h
 *
 *  Created on: Jan 8, 2024
 *      Author: cyberreefguru
 */
#ifndef MultiActionItem_H
#define MultiActionItem_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

// #include "ActionMenuItem.h"
// #include "MenuManager.h"


class MultiActionItem : public MenuItem
{
public:
    // MultiActionItem(){}
    MultiActionItem(menu_label_t label, menu_title_t title, ActionMenuItem **i, uint8_t numItems);
    virtual ~MultiActionItem();

    // virtual void onDisplay();
    virtual void onDisplay(bool active) override;
    virtual void onButtonUp() override;
    virtual void onButtonDown() override;
    virtual void onButtonLeft() override;
    virtual void onButtonRight() override;
    virtual void onButtonPush() override;

    virtual void onOk();
    virtual void onCancel();


protected:
    uint8_t curItem = 0;
    ActionMenuItem *ok = nullptr;
    ActionMenuItem *cancel = nullptr;

};

#endif