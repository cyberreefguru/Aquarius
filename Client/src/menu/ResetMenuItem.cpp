/*
 * ResetMenuItem.h
 *
 *  Created on: Jan 14, 2024
 *      Author: cyberreefguru
 */

#include "ResetMenuItem.h"

ResetMenuItem::ResetMenuItem()
{
    this->menuTitle = "Factory Reset?";
    this->menuLabel = "> Factory Reset";
    this->menuPrompt = "Push to Reset";
    this->items = nullptr;
    this->numItems = 0;
}

void ResetMenuItem::onDisplay(bool active)
{
    Log.traceln("ResetMenuItem::onDisplay - BEGIN");

    if (menuLabel == nullptr)
    {
        Log.errorln("Menu Item has no label!");
        return;
    }

    displayManager.clear();
    displayManager.setCursor(0, 0);
    displayManager.println(menuTitle);

    if (active)
    {
        displayManager.setTextColor(BLACK, WHITE);
    }
    else
    {
        displayManager.setTextColor(WHITE);
    }
    displayManager.print(menuPrompt);
    displayManager.setTextColor(WHITE);
    displayManager.setRefresh(true);

    Log.traceln("ResetMenuItem::onDisplay - END");
}

void ResetMenuItem::onButtonUp()
{
    onButtonRight();
}

void ResetMenuItem::onButtonDown()
{
    onButtonRight();
}

void ResetMenuItem::onButtonLeft()
{
    onButtonRight();
}

void ResetMenuItem::onButtonRight()
{
    menuManager.pop();
    menuManager.display();
}

void ResetMenuItem::onButtonPush()
{
    Log.infoln("Reseting to factory settings...");
    prefManager.reset();
    Log.infoln("Reset!");
    onButtonRight();
}
