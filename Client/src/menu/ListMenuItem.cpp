/*
 * ListMenuItem.cpp
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */
#include "MenuManager.h"

ListMenuItem::ListMenuItem()
{
}

ListMenuItem::~ListMenuItem()
{
}

ListMenuItem::ListMenuItem(const char *title, MenuItem **items, uint8_t numItems)
{
    this->title = title;
    this->items = items;
    this->numItems = numItems;
}

void ListMenuItem::onDisplay()
{
    Log.traceln("ListMenuItem::onDisplay - BEGIN");

    if (items == nullptr || numItems == 0)
    {
        Log.errorln("ListMenuItem::onDisplay - no children to display");
        return;
    }

    displayManager.clear();
    displayManager.setCursor(0,0);
    displayManager.println(title);
    for (uint8_t i = 0; i < numItems; i++)
    {
        MenuItem *item = items[i];
        if (item->isActive())
        {
            displayManager.setTextColor(BLACK, WHITE);
        }
        else
        {
            displayManager.setTextColor(WHITE);
        }
        displayManager.println(item->getTitle());
        displayManager.setTextColor(WHITE);
    }
    displayManager.setRefresh(true);
    Log.traceln("ListMenuItem::onDisplay - END");
}

void ListMenuItem::onEvent(ButtonEvent be)
{
    Log.traceln("ListMenuItem::onEvent - %s", ++be);
    switch (be)
    {
    case ButtonEvent::UP:
        activatePrevious();
        onDisplay();
        break;
    case ButtonEvent::DOWN:
        activateNext();
        onDisplay();
        break;
    case ButtonEvent::LEFT:
        active = true;
        menuManager.pop();
        break;
    case ButtonEvent::RIGHT:
    case ButtonEvent::PUSH:
        if (items == nullptr || numItems == 0)
        {
            Log.warningln("ListMenuItem::onEvent - No children to push!");
        }
        else
        {
            MenuItem *item = getActive();
            if (item != nullptr)
            {
                menuManager.push(item);
                item->onDisplay();
            }
            else
            {
                Log.errorln("ListMenuItem::onEvent - No active item to push!");
            }
        }
        break;
    default:
        break;
    }
}

MenuItem *ListMenuItem::getActive()
{
    MenuItem *item = nullptr;

    if (items != nullptr && numItems > 0)
    {
        for (uint8_t i = 0; i < numItems; i++)
        {
            if (items[i]->isActive())
            {
                item = items[i];
                break;
            }
        }
    }
    else
    {
        Log.warningln("ListMenuItem:getActive - No children items");
    }

    return item;
}

uint8_t ListMenuItem::getActiveIndex()
{
    uint8_t index = 0;
    if (items != nullptr && numItems > 0)
    {
        for (uint8_t i = 0; i < numItems; i++)
        {
            if (items[i]->isActive())
            {
                index = i;
                break;
            }
        }
    }
    else
    {
        Log.warningln("ListMenuItem:getActiveIndex - No children items");
    }
    return index;
}

void ListMenuItem::activateNext()
{
    if (items != nullptr && numItems > 0)
    {
        uint8_t cur = getActiveIndex();
        items[cur]->setActive(false);
        if ((cur + 1) == numItems)
        {
            cur = 0;
            windowStart = 0;
        }
        else
        {
            cur += 1;
            if (cur == (windowStart + 6))
            {
                windowStart += 1;
            }
        }
        items[cur]->setActive(true);
    }
    else
    {
        Log.warningln("ListMenuItem:activateNext - No children items");
    }
}

void ListMenuItem::activatePrevious()
{
    if (items != nullptr && numItems > 0)
    {
        uint8_t cur = getActiveIndex();
        items[cur]->setActive(false);
        if (cur == 0)
        {
            cur = numItems - 1;
            windowStart = cur - 5;
        }
        else
        {
            cur -= 1;
            if (cur == (windowStart - 1))
            {
                windowStart = cur;
            }
        }
        items[cur]->setActive(true);
    }
    else
    {
        Log.warningln("ListMenuItem::activatePrevious - No children items");
    }
}