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

#include "ListMenu.h"
#include "ActionButtonItem.h"

class MultiActionItem : public ListMenu
{
public:
    MultiActionItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt);
    virtual ~MultiActionItem();

    void initialize(MenuItem **items, uint8_t numItems) override;
    void initialize(ArrayList<MenuItem*> *items) override;

    virtual void onDisplay(bool active) override;
    virtual void onButtonUp() override;
    virtual void onButtonDown() override;
    virtual void onButtonLeft() override;
    virtual void onButtonRight() override;
    virtual void onButtonPush() override;

    virtual void onOk();
    virtual void onCancel();

protected:
    MultiActionItem(){}
    virtual void initialize();

    uint8_t curItem = 0;
    ActionButtonItem *ok = nullptr;
    ActionButtonItem *cancel = nullptr;

};

#endif