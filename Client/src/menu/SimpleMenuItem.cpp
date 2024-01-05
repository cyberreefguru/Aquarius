/*
 * ExitMenuItem.h
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */

#include "MenuManager.h"

SimpleMenuItem::SimpleMenuItem(const char *title)
{
    Log.traceln("SimpleMenuItem: BEGIN");
    this->title = title;
    this->label = title;
    Log.traceln("SimpleMenuItem: BEGIN");
}

SimpleMenuItem::~SimpleMenuItem()
{
}

void SimpleMenuItem::onDisplay()
{
    Log.traceln("SimpleMenuItem::onDisplay - BEGIN");
    if (label != nullptr)
    {
        displayManager.clear();
        displayManager.setCursor(0, 0);
        if (active)
        {
            displayManager.setTextColor(BLACK, WHITE);
        }
        else
        {
            displayManager.setTextColor(WHITE);
        }
        displayManager.println(label);
        displayManager.setTextColor(WHITE);
        displayManager.setRefresh(true);
    }
    else
    {
        Log.errorln("Menu Item has no label!");
    }
    Log.traceln("SimpleMenuItem::onDisplay - END");
}

void SimpleMenuItem::onEvent(ButtonEvent be)
{
    Log.traceln("SimpleMenuItem.onEvent - BEGIN");
    switch (be)
    {
    case ButtonEvent::UP:
        break;
    case ButtonEvent::DOWN:
        break;
    case ButtonEvent::LEFT:
    case ButtonEvent::PUSH:
        menuManager.pop();
        menuManager.display();
        break;
    case ButtonEvent::RIGHT:
        break;
    default:
        break;
    }
    Log.traceln("SimpleMenuItem.onEvent - END");
}
