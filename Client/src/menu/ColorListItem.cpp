/*
 * ColorListItem.cpp
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */
#include "MenuManager.h"

ColorListItem::ColorListItem(const char *title, const char *label)
{
    this->title = title;
    this->label = label;
    this->numItems = numMenuColors;

    windowSize = menuManager.getScreenMaxY(); // subtract for menu name
    windowStart = 0;
    activeIndex = windowStart;

}

ColorListItem::~ColorListItem()
{
}

void ColorListItem::onDisplay()
{
    Log.traceln("ColorListItem::onDisplay - BEGIN");

    displayManager.clear();
    displayManager.setCursor(0, 0);
    displayManager.println(title);
    uint8_t windowEnd = windowStart + windowSize - 1;
    // Log.traceln("start=%d, end=%d, index=%d, size=%d", windowStart, windowEnd, activeIndex, windowSize);
    for (uint8_t i = windowStart; i < windowEnd; i++)
    {

        if (i == activeIndex)
        // if (item->isActive())
        {
            displayManager.setTextColor(BLACK, WHITE);
        }
        else
        {
            displayManager.setTextColor(WHITE);
        }
        displayManager.println(menuColors[i]->name);
        displayManager.setTextColor(WHITE);
    }
    displayManager.setRefresh(true);
    Log.traceln("ColorListItem::onDisplay - END");
}

void ColorListItem::onEvent(ButtonEvent be)
{
    Log.traceln("ColorListItem::onEvent - %s", ++be);
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
        break;
    case ButtonEvent::PUSH:
        Log.traceln("Saving color: %s", menuColors[activeIndex]->name);
        menuManager.pop();
        menuManager.display();
        break;
    default:
        break;
    }
}