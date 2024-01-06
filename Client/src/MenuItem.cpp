/*
 * MenuItem.cpp
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */
#include "MenuManager.h"

MenuItem::MenuItem()
{
}

MenuItem::~MenuItem()
{
}

MenuItem::MenuItem(const char *title, const char *label)
{
    this->title = title;
    this->label = label;
}

void MenuItem::onDisplay()
{
    Log.traceln("MenuItem::onDisplay");

    // if (label != nullptr)
    // {
    //     displayManager.clear();
    //     displayManager.setCursor(0, 0);
    //     if (active)
    //     {
    //         displayManager.setTextColor(BLACK, WHITE);
    //     }
    //     else
    //     {
    //        displayManager.setTextColor(WHITE);
    //     }
    //     displayManager.println(label);
    //     displayManager.setTextColor(WHITE);
    //     displayManager.setRefresh(true);
    // }
    // else
    // {
    //     Log.errorln("MenuItem::onDisplay - Menu Item has no label!");
    // }
    // Log.traceln("MenuItem::onDisplay - END");
}

void MenuItem::onEvent(ButtonEvent be)
{
    Log.traceln("MenuItem::onEvent - %s", ++be);
}