/*
 * ListMenuItem.cpp
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */
#include "ListMenu.h"

LabelListMenu::LabelListMenu(const char *title, const char *label, MenuItem **items, uint8_t numItems)
{
    this->title = title;
    this->label = label;
    this->items = items;
    this->numItems = numItems;

    windowSize = menuManager.getScreenMaxY(); // subtract for menu name
    windowStart = 0;
    activeIndex = windowStart;
}

LabelListMenu::~LabelListMenu()
{
}


void LabelListMenu::onDisplay()
{
    Log.traceln("LabelListMenu::onDisplay - BEGIN");

    if (items == nullptr || numItems == 0)
    {
        Log.errorln("LabelListMenu::onDisplay - no children to display");
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
        // Log.traceln("LabelListMenu::onDisplay - item.title='%s', item.label='%s'", item->getTitle(), item->getLabel());
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
    Log.traceln("LabelListMenu::onDisplay - END");
}


void LabelListMenu::onButtonPush()
{
    MenuItem *item = items[activeIndex];
    Log.traceln("Press label: %s", item->getLabel());
    menuManager.push(item);
    item->onDisplay();
}
