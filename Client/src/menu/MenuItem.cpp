/*
 * MenuItem.cpp
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */
#include "MenuManager.h" // TODO: fix this

MenuItem::MenuItem()
{
}

MenuItem::MenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt)
{
    this->menuTitle = title;
    this->menuLabel = label;
    this->menuPrompt = prompt;
}

MenuItem::~MenuItem()
{
}

void MenuItem::onEvent(ButtonEvent be)
{
   Log.traceln("MenuItem.onEvent - BEGIN");
    switch (be)
    {
    case ButtonEvent::UP:
        onButtonUp();
        break;
    case ButtonEvent::DOWN:
        onButtonDown();
        break;
    case ButtonEvent::LEFT:
        onButtonLeft();
        break;
    case ButtonEvent::RIGHT:
        onButtonRight();
        break;
    case ButtonEvent::PUSH:
        onButtonPush();
        break;
    default:
        break;
    }
    Log.traceln("MenuItem.onEvent - END");
}

