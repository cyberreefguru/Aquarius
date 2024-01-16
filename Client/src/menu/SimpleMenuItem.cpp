/*
 * SimpleMenuItem.cpp
 *
 *  Created on: Jan 6, 2024
 *      Author: cyberreefguru
 */

#include "SimpleMenuItem.h"
#include "DisplayManager.h"
#include "MenuManager.h"

SimpleMenuItem::~SimpleMenuItem()
{
    this->menuTitle = "";
    this->menuLabel = menuTitle;
    this->menuPrompt = menuTitle;
}

SimpleMenuItem::SimpleMenuItem(menu_title_t title)
{
    this->menuTitle = title;
    this->menuLabel = menuTitle;
    this->menuPrompt = "";
}

SimpleMenuItem::SimpleMenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt)
{
    this->menuTitle = title;
    this->menuLabel = label;
    this->menuPrompt = prompt;
}

void SimpleMenuItem::onDisplay(bool active)
{
    Log.traceln("SimpleMenuItem::onDisplay - BEGIN");
    if (menuLabel != nullptr)
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
        displayManager.println(menuLabel);
        displayManager.setTextColor(WHITE);
        displayManager.setRefresh(true);
    }
    else
    {
        Log.errorln("Menu Item has no label!");
    }
    Log.traceln("SimpleMenuItem::onDisplay - END");
}

void SimpleMenuItem::onButtonLeft()
{
    onButtonPush();
}

void SimpleMenuItem::onButtonRight()
{
    onButtonPush();
}
void SimpleMenuItem::onButtonPush()
{
    menuManager.pop();
    menuManager.display();
}