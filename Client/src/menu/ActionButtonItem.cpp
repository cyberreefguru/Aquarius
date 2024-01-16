/*
 * AcitonMenuItem.cpp
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */

#include "ActionButtonItem.h"
#include "DisplayManager.h"
#include "MenuColor.h"

ActionButtonItem::ActionButtonItem(menu_prompt_t prompt, ActionCallback cb)
{
    this->menuTitle = prompt;
    this->menuLabel = prompt;
    this->menuPrompt = prompt;
    this->doAction = cb;
}

void ActionButtonItem::onDisplay(bool active)
{
    Log.traceln("ActionButtonItem::onDisplay - BEGIN");

    if (doDisplay != nullptr)
    {
        Log.traceln("ActionButtonItem::onDisplay - using callback");
        doDisplay(active);
        return;
    }

    if (menuPrompt == nullptr)
    {
        Log.errorln("Item missing labels!");
        return;
    }

    Log.traceln("ActionButtonItem::onDisplay - no callback; rendering %s", menuPrompt);

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

    Log.traceln("ActionButtonItem::onDisplay - END");
}