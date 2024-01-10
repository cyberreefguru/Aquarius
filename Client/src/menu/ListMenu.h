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

// #include "menu/MenuItem.h"
#include "MenuManager.h"

class ListMenu : public MenuItem
{
public:
    ListMenu() {}
    ListMenu(menu_label_t label, menu_title_t title, MenuItem **items, uint8_t numItems);
    virtual ~ListMenu();
    virtual void onDisplay() override;
    virtual void onButtonUp() override;
    virtual void onButtonDown() override;
    virtual void onButtonLeft() override;
    virtual void onButtonRight() override;
    virtual void onButtonPush() override;

protected:
    uint8_t activeIndex = 0;
    uint8_t windowSize = 0;
    uint8_t windowStart = 0;

    MenuItem *getActive();
    uint8_t getActiveIndex();
    void activateNext();
    void activatePrevious();

private:
};

class ColorListMenu : public ListMenu
{
public:
    ColorListMenu(menu_label_t label, menu_title_t title, menu_prompt_t prompt);
    virtual ~ColorListMenu();
    virtual void onDisplay() override;
    virtual void onButtonPush() override;

    // std::bind(&MainMenu::save, this)
    // onActivateCallback(item, b);
};

#endif