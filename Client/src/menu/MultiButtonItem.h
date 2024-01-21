/*
 * MultiButtonItem.h
 *
 *  Created on: Jan 21, 2024
 *      Author: cyberreefguru
 */
#ifndef MultiButtonItem_H
#define MultiButtonItem_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "ListMenu.h"
#include "ActionButtonItem.h"

class MultiButtonItem : public ListMenu
{
public:
    MultiButtonItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt);
    virtual ~MultiButtonItem();

    void initialize(MenuItem **items, uint8_t numItems) override;
    void initialize(ArrayList<MenuItem*> *items) override;
    void initialize(ArrayList<MenuItem*> *items, ArrayList<ActionButtonItem*> *buttons);

    virtual void onDisplay(bool active) override;
    virtual void onButtonUp() override;
    virtual void onButtonDown() override;
    virtual void onButtonLeft() override;
    virtual void onButtonRight() override;
    virtual void onButtonPush() override;

    void addItem(MenuItem *item);
    void addButton(ActionButtonItem *button);

protected:
    MultiButtonItem(){}
    virtual void initialize();
    virtual void activateNext() override;
    virtual void activatePrevious() override;
    virtual bool inItemRange();
    virtual bool inButtonRange();
    virtual uint8_t getActiveItemIndex();
    virtual uint8_t getActiveButtonIndex();

    ArrayList<ActionButtonItem*> buttons;
};

#endif