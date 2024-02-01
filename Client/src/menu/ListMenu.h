/*
 * ListMenuItem.h
 *
 *  Created on: Jan 6, 2024
 *      Author: cyberreefguru
 */

#ifndef ListMenu_H
#define ListMenu_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "ArrayList.h"

#include "menu/MenuItem.h"

class ListMenu : public MenuItem
{
public:
    ListMenu(menu_label_t label, menu_title_t title, menu_prompt_t prompt);
    // ListMenu(menu_label_t label, menu_title_t title, menu_prompt_t prompt, MenuItem **items, uint8_t numItems);
    virtual ~ListMenu();

    virtual void initialize(MenuItem **items, uint8_t numItems);
    virtual void initialize(ArrayList<MenuItem*> *items);

    void onDisplay(bool active) override;
    virtual void onButtonUp() override;
    virtual void onButtonDown() override;
    virtual void onButtonLeft() override;
    virtual void onButtonRight() override;
    virtual void onButtonPush() override;

    void setSelectedIndex(uint8_t index);

protected:
    ListMenu() {}
    ArrayList<MenuItem*> items;

    uint8_t activeIndex = 0;
    uint8_t windowSize = 0;
    uint8_t windowStart = 0;
    const char* key = nullptr;

    MenuItem *getActive();
    uint8_t getActiveIndex();
    virtual void activateNext();
    virtual void activatePrevious();

private:
};

#endif