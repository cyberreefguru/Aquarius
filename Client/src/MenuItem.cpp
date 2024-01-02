/*
 * MenuItem.cpp
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */
#include "MenuManager.h"

MenuItem::MenuItem()
{
}

MenuItem::MenuItem(const char *title)
{
    this->title = title;
}

void MenuItem::initialize(const char *title, MenuItem **items, uint8_t numItems)
{
    this->title = title;
    this->items = items;
    this->numItems = numItems;
}

void MenuItem::onDisplay()
{
    if (title != nullptr)
    {
        Log.traceln("MenuItem.title: %s, Active: %d", title, active);
        if (active)
        {
            displayManager.setTextColor(BLACK, WHITE);
        }
        else
        {
           displayManager.setTextColor(WHITE);
        }
        displayManager.println(title);
        displayManager.setTextColor(WHITE);
    }
    else
    {
        Log.errorln("Menu Item has no title!");
    }
}

void MenuItem::onEvent(ButtonEvent be)
{
    Log.traceln("MenuItem::onEvent - %s", ++be);
    switch (be)
    {
    case ButtonEvent::UP:
        activatePrevious();
        break;
    case ButtonEvent::DOWN:
        activateNext();
        break;
    case ButtonEvent::LEFT:
        active = true;
        menuManager.pop();
        break;
    case ButtonEvent::RIGHT:
        if( numItems == 0 )
        {
            Log.warningln("No children to push!");
        }
        else
        {
            menuManager.push(getActive());
        }
        break;
    case ButtonEvent::PUSH:
        if( numItems == 0 )
        {
            Log.warningln("No children to push!");
        }
        else
        {
            menuManager.push(getActive());
        }
        break;
    default:
        break;
    }
}

MenuItem *MenuItem::getActive()
{
    MenuItem *item = nullptr;

    if (items != nullptr && numItems > 0)
    {
        for (uint8_t i = 0; i < numItems; i++)
        {
            if (items[i]->active)
            {
                item = items[i];
                break;
            }
        }
    }

    return item;
}

uint8_t MenuItem::getActiveIndex()
{
    uint8_t index = 0;

    if (items != nullptr && numItems > 0)
    {
        for (uint8_t i = 0; i < numItems; i++)
        {
            if (items[i]->active)
            {
                index = i;
                // TODO - we may need to adjust window here
                break;
            }
        }
    }

    return index;
}

void MenuItem::activateNext()
{
    if (numItems > 0)
    {
        uint8_t cur = getActiveIndex();
        items[cur]->active = false;
        if ((cur+1) == numItems)
        {
            cur=0;
            windowStart = 0;
        }
        else
        {
            cur += 1;
            if( cur == (windowStart+6) )
            {
                windowStart += 1;
            }
        }
        items[cur]->active = true;
    }
    else
    {
        Log.warningln("No children items");
    }
}

void MenuItem::activatePrevious()
{
    if (numItems > 0)
    {
        uint8_t cur = getActiveIndex();
        items[cur]->active = false;
        if (cur == 0)
        {
            cur=numItems-1;
            windowStart = cur-5;
        }
        else
        {
            cur -= 1;
            if( cur == (windowStart-1))
            {
                windowStart = cur;
            }
        }
        items[cur]->active = true;
    }
    else
    {
        Log.warningln("No children items");
    }
}