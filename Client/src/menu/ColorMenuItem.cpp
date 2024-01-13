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
    this->menuTitle = (menu_title_t)color->name;
    this->menuLabel = (menu_label_t)color->name;
}

ColorMenuItem::~ColorMenuItem()
{
}

void ColorMenuItem::onDisplay(bool active)
{
    Log.traceln("ColorMenuItem::onDisplay - BEGIN");
    displayManager.println(color->name);
    Log.traceln("ColorMenuItem::onDisplay - END");
}

void ColorMenuItem::onButtonPush()
{
        Log.traceln("Saving %s to value", color->name);
        // TODO - save color
        menuManager.pop();
        menuManager.display();
}