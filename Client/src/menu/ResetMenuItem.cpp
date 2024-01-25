/**
 * @brief menu item to reset preferences
 * @file TargetCreateMenuItem.h
 * @date Jan 14, 2024
 * @author cyberreefguru
 * 
*/
#include "ResetMenuItem.h"

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