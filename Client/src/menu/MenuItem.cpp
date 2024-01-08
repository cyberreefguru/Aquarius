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

void MenuItem::onEvent(ButtonEvent be)
{
   Log.traceln("MenuItem.onEvent - BEGIN");
    switch (be)
    {
    case ButtonEvent::UP:
        onButtonUp();
        break;
    case ButtonEvent::DOWN:
        onButtonDown();
        break;
    case ButtonEvent::LEFT:
        onButtonLeft();
        break;
    case ButtonEvent::PUSH:
        onButtonPush();
        break;
    case ButtonEvent::RIGHT:
        onButtonRight();
        break;
    default:
        break;
    }
    Log.traceln("MenuItem.onEvent - END");
}

