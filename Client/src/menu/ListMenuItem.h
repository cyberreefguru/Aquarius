/*
 * ListMenuItem.h
 *
 *  Created on: Jan 6, 2024
 *      Author: cyberreefguru
 */

#ifndef ListMenuItem_H
#define ListMenuItem_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

// #include "menu/MenuItem.h"
#include "MenuManager.h"

class LabelListMenu : public MenuItem
{
public:
    LabelListMenu(){}
    LabelListMenu(const char *title, const char *label, MenuItem** items, uint8_t numItems);
    virtual ~LabelListMenu();
    virtual void onEvent(ButtonEvent be);
    virtual void onDisplay();

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


class ColorListItem : public LabelListMenu
{
public:
    ColorListItem(const char *title, const char *label);
    virtual ~ColorListItem();
    virtual void onDisplay();
    virtual void onEvent(ButtonEvent be);

//std::bind(&MainMenu::save, this)
//onActivateCallback(item, b);

};

#endif