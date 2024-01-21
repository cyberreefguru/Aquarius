/*
 * ColorMenuItem.h
 *
 *  Created on: Jan 4, 2023
 *      Author: cyberreefguru
 */

#include "ColorMenuItem.h"

#include "menu/MenuColor.h"

// #include "DisplayManager.h"
// #include "MenuManager.h"

/**
 * @brief Constuctor
 * @param color 
 */
ColorMenuItem::ColorMenuItem(const MenuColor *color)
{
    this->color = color;
    // // NOTE - this eats up a lot of memory.
    // // There are 10 menu lists, and 22 things in each list, and 22 per item (~4.8K of SRAM)
    // memset(buf, 0, 22);
    // snprintf(buf, 21, "> %s", color->name);
    this->menuLabel = color->label;
    this->menuTitle = color->name;
    this->menuPrompt = color->name;

}

/**
 * @brief Destructor
 */
ColorMenuItem::~ColorMenuItem()
{

}

// void ColorMenuItem::onDisplay(bool active)
// {
//     Log.traceln("ColorMenuItem::onDisplay - BEGIN");
//     displayManager.println(color->name);
//     Log.traceln("ColorMenuItem::onDisplay - END");
// }

// void ColorMenuItem::onButtonPush()
// {
//         Log.traceln("Saving %s to value", color->name);
//         // TODO - save color
//         menuManager.pop();
//         menuManager.display();
// }