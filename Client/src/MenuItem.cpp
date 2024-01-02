/*
 * MenuItem.cpp
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */
#include "MenuItem.h"

MenuItem::MenuItem()
{
}

void MenuItem::initialize(const char *title, MenuItem *items, uint8_t numItems)
{
    this->title = title;
    this->items = items;
    this->numItems = numItems;
}

void MenuItem::onActivate(bool b)
{
    active = b;
}

void MenuItem::onDisplay()
{
    if (onDisplayCallback == nullptr)
    {
        displayManager.clear();
        if (title != nullptr)
            displayManager.println(title);
        if (numItems > 0 && items != nullptr)
        {
            for (uint8_t i = 0; i < numItems; i++)
            {
                items[i].onDisplay();
            }
        }
    }
    else
    {
        onDisplayCallback();
    }
}

void MenuItem::onEvent(ButtonEvent be)
{
    if (onEventCallback != nullptr)
    {
        Log.traceln("Event callback");
        onEventCallback(be);
    }
    else
    {

        if (active)
        {
            Log.traceln("MenuItem active but no action.");
        }
        else
        {
            if (numItems > 0 && items != nullptr)
            {
                for (uint8_t i = 0; i < numItems; i++)
                {
                    if (items[i].active)
                    {
                        items[i].onEvent(be);
                    }
                }
            }
        }
    }
}

void MenuItem::setEventCallback(std::function<void(ButtonEvent be)> cb)
{
    this->onEventCallback = cb;
}
void MenuItem::setDisplayCallback(MenuCallback cb)
{
    this->onDisplayCallback = cb;
}

void MenuItem::setActivateCallback(MenuCallback cb)
{
    this->onActivateCallback = cb;
}
