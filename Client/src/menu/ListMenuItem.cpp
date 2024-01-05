/*
 * ListMenuItem.cpp
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */
#include "MenuManager.h"

ListMenuItem::~ListMenuItem()
{
}

ListMenuItem::ListMenuItem(const char *title, const char *label, MenuItem **items, uint8_t numItems)
{
    this->title = title;
    this->label = label;
    this->items = items;
    this->numItems = numItems;

    windowSize = menuManager.getScreenMaxY(); // subtract for menu name
    windowStart = 0;
    activeIndex = windowStart;
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
    displayManager.setCursor(0, 0);
    displayManager.println(title);
    uint8_t windowEnd = windowStart + windowSize - 1;
    // Log.traceln("start=%d, end=%d, index=%d, size=%d", windowStart, windowEnd, activeIndex, windowSize);
    for (uint8_t i = windowStart; i < windowEnd; i++)
    {
        MenuItem *item = items[i];
        // Log.traceln("ListMenuItem::onDisplay - item.title='%s', item.label='%s'", item->getTitle(), item->getLabel());
        if (i == activeIndex)
        // if (item->isActive())
        {
            displayManager.setTextColor(BLACK, WHITE);
        }
        else
        {
            displayManager.setTextColor(WHITE);
        }
        displayManager.println(item->getLabel());
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
        menuManager.display();
        break;
    case ButtonEvent::RIGHT:
    case ButtonEvent::PUSH:
        if (items == nullptr || numItems == 0)
        {
            Log.warningln("ListMenuItem::onEvent - No children to push!");
        }
        else
        {
            menuManager.push(items[activeIndex]);
            items[activeIndex]->onDisplay();
        }
        break;
    default:
        break;
    }
}

MenuItem *ListMenuItem::getActive()
{
    return items[activeIndex];
    // MenuItem *item = nullptr;

    // if (items != nullptr && numItems > 0)
    // {
    //     for (uint8_t i = 0; i < numItems; i++)
    //     {
    //         if (items[i]->isActive())
    //         {
    //             item = items[i];
    //             break;
    //         }
    //     }
    // }
    // else
    // {
    //     Log.warningln("ListMenuItem:getActive - No children items");
    // }

    // return item;
}

uint8_t ListMenuItem::getActiveIndex()
{
    return activeIndex;
    // uint8_t index = 0;
    // if (items != nullptr && numItems > 0)
    // {
    //     for (uint8_t i = 0; i < numItems; i++)
    //     {
    //         if (items[i]->isActive())
    //         {
    //             index = i;
    //             break;
    //         }
    //     }
    // }
    // else
    // {
    //     Log.warningln("ListMenuItem:getActiveIndex - No children items");
    // }
    // return index;
}

void ListMenuItem::activateNext()
{
    uint8_t windowEnd = windowStart + windowSize - 1;
    Log.traceln("ListMenuItem::activateNext - start=%d, end=%d, active=%d, size=%d", windowStart, windowEnd, activeIndex, windowSize);
    if (activeIndex == (windowEnd - 1))
    {
        // We are at the end of the window
        // See if we're also at the end of the list
        if (activeIndex == numItems - 1)
        {
            // we're out of items--cycle to top
            windowStart = 0;
            activeIndex = 0;
        }
        else
        {
            // We are not at the end of the list, but
            // but we are at the end of the window
            // Advance the window one place
            windowStart++;
            activeIndex++;
        }
    }
    else
    {
        // We are within the window, advance index
        activeIndex++;
    }
    Log.traceln("ListMenuItem::activateNext - start=%d, end=%d, active=%d, size=%d", windowStart, windowEnd, activeIndex, windowSize);
}

void ListMenuItem::activatePrevious()
{
    uint8_t windowEnd = windowStart + windowSize - 1;
    Log.traceln("ListMenuItem::activatePrevious - start=%d, end=%d, active=%d, size=%d", windowStart, windowEnd, activeIndex, windowSize);
    if (activeIndex == windowStart)
    {
        // We are at the top of the window
        // See if we're also at the top of the list
        if (activeIndex == 0)
        {
            // We are at the start of the list
            // Side window to end of list
            if (windowSize >= numItems)
            {
                // Windows size > number of items
                // Set window to 0 and active to last item
                windowStart = 0;
                activeIndex = numItems - 1;
            }
            else
            {
                // Window is < number items
                // Compute starting point
                windowStart = numItems - windowSize + 1;
                activeIndex = numItems - 1;
            }
        }
        else
        {
            Log.traceln("We're not at the top of the list, roll window");
            // We are not at the top of the list
            // Pull window up one
            windowStart--;
            activeIndex--;
        }
    }
    else
    {
        // We are within the window, advance index
        activeIndex--;
    }
    Log.traceln("ListMenuItem::activatePrevious - start=%d, end=%d, active=%d, size=%d", windowStart, windowEnd, activeIndex, windowSize);
}