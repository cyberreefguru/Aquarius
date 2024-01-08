/*
 * ColorListMenu.cpp
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */
#include "ColorListMenu.h"

ColorListMenu::ColorListMenu(const char *title, const char *label)
{
    this->title = title;
    this->label = label;
    this->numItems = numMenuColors;

    windowSize = menuManager.getScreenMaxY(); // subtract for menu name
    windowStart = 0;
    activeIndex = windowStart;
}

ColorListMenu::~ColorListMenu()
{
}

void ColorListMenu::onDisplay()
{
    Log.traceln("ColorListMenu::onDisplay - BEGIN");

    displayManager.clear();
    displayManager.setCursor(0, 0);
    displayManager.println(title);
    uint8_t windowEnd = windowStart + windowSize - 1;
    // Log.traceln("start=%d, end=%d, index=%d, size=%d", windowStart, windowEnd, activeIndex, windowSize);
    for (uint8_t i = windowStart; i < windowEnd; i++)
    {

        if (i == activeIndex)
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
    Log.traceln("ColorListMenu::onDisplay - END");
}

void ColorListMenu::onButtonPush()
{
    Log.traceln("Saving color: %s", menuColors[activeIndex]->name);

    // TODO - save color
    
    menuManager.pop();
    menuManager.display();
}
