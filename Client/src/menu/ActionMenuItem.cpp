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
    if (menuLabel == nullptr)
    {
        Log.errorln("Menu Item has no label!");
        return;
    }

    if (active)
    {
        displayManager.setTextColor(BLACK, WHITE);
    }
    else
    {
        displayManager.setTextColor(WHITE);
    }
    displayManager.print(menuLabel);
    displayManager.setTextColor(WHITE);
    displayManager.setRefresh(true);
    Log.traceln("ActionMenuItem::onDisplay - END");
}

// void ActionMenuItem::onDisplay()
// {
//     onDisplay(false);
// }

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
    if (doButtonUp != nullptr)
    {
        doButtonUp();
    }
}

void ActionMenuItem::onButtonLeft()
{
    if (doButtonUp != nullptr)
    {
        doButtonUp();
    }
}

void ActionMenuItem::onButtonRight()
{
    if (doButtonUp != nullptr)
    {
        doButtonUp();
    }
}

void ActionMenuItem::onButtonPush()
{
    if (doButtonUp != nullptr)
    {
        doButtonUp();
    }
}