/*
 * ColorMenuItem.h
 *
 *  Created on: Jan 4, 2023
 *      Author: cyberreefguru
 */

#include "ColorMenuItem.h"

ColorMenuItem::ColorMenuItem(const MenuColor *color)
{
    this->color = color;
    this->title = color->name;
    this->label = color->name;
}

ColorMenuItem::~ColorMenuItem()
{
}

void ColorMenuItem::onDisplay()
{
    Log.traceln("ColorMenuItem::onDisplay - BEGIN");
    Log.traceln("Saving Color: %s, %X", color->name, color->value);
        menuManager.pop();
        menuManager.pop();
        menuManager.display();
    Log.traceln("ColorMenuItem::onDisplay - END");
}

void ColorMenuItem::onEvent(ButtonEvent be)
{
    Log.traceln("ColorMenuItem.onEvent - BEGIN");
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
    Log.traceln("ColorMenuItem.onEvent - END");
}
