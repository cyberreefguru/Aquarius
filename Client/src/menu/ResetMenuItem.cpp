/*
 * ResetMenuItem.h
 *
 *  Created on: Jan 14, 2024
 *      Author: cyberreefguru
 */

#include "ResetMenuItem.h"
// #include "DisplayManager.h"
// #include "MenuManager.h"

ResetMenuItem::ResetMenuItem(ActionCallback cb)
{
    this->menuTitle = "Factory Reset?";
    this->menuLabel = "> Factory Reset";
    this->menuPrompt = "Push to Reset";
    this->doAction = cb;
}

void ResetMenuItem::onDisplay(bool active)
{
    MenuItem::onDisplay(true);
}