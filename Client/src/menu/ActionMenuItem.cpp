/*
 * AcitonMenuItem.cpp
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */

#include "ActionMenuItem.h"
// #include "MenuManager.h"

ActionMenuItem::ActionMenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt, ActionCallback cb)
{
    this->menuTitle = title;
    this->menuLabel = label;
    this->menuPrompt = prompt;
    this->doAction = cb;
}

void ActionMenuItem::setDisplayCallback(DisplayCallback cb)
{
    doDisplay = cb;
}

void ActionMenuItem::setActionCallback(ActionCallback cb)
{
    doAction = cb;
}

void ActionMenuItem::setButtonCallback(ButtonCallback up, ButtonCallback down,
                                       ButtonCallback left, ButtonCallback right,
                                       ButtonCallback push)
{
    doButtonUp = up;
    doButtonDown = down;
    doButtonLeft = left;
    doButtonRight = right;
    doButtonPush = push;
}

void ActionMenuItem::onDisplay(bool active)
{
    Log.traceln("ActionMenuItem::onDisplay - BEGIN");

    if (doDisplay != nullptr)
    {
        Log.traceln("ActionMenuItem::onDisplay - using callback");
        doDisplay();
        return;
    }

    Log.traceln("ActionMenuItem::onDisplay - no callback; rendering");

    if (menuLabel == nullptr || menuPrompt == nullptr)
    {
        Log.errorln("Item missing labels!");
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

    Log.traceln("ActionMenuItem::onDisplay - END");
}

void ActionMenuItem::onAction()
{
    if (doAction != nullptr)
    {
        doAction();
    }
}

void ActionMenuItem::onButtonUp()
{
    if (doButtonUp != nullptr)
    {
        doButtonUp();
    }
}

void ActionMenuItem::onButtonDown()
{
    if (doButtonDown != nullptr)
    {
        doButtonDown();
    }
}

void ActionMenuItem::onButtonLeft()
{
    if (doButtonLeft != nullptr)
    {
        doButtonLeft();
    }
}

void ActionMenuItem::onButtonRight()
{
    if (doButtonRight != nullptr)
    {
        doButtonRight();
    }
}

void ActionMenuItem::onButtonPush()
{
    if (doButtonPush != nullptr)
    {
        doButtonPush();
    }
}