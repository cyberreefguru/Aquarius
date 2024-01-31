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
ColorMenuItem::ColorMenuItem(uint8_t index)
{
    this->index = index;
    this->menuLabel = menuColors[index]->label;
    this->menuTitle = menuColors[index]->name;
    this->menuPrompt = menuColors[index]->name;
}

/**
 * @brief Destructor
 */
ColorMenuItem::~ColorMenuItem()
{

}