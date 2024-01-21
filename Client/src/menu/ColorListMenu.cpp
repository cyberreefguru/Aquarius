/*
 * ColorListMenu.cpp
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */
#include "ColorListMenu.h"
#include "ColorMenuItem.h"
#include "DisplayManager.h"
#include "MenuManager.h"

/**
 * @brief Constructor
 * @param label
 * @param title
 * @param prompt
 * @param key
 */
ColorListMenu::ColorListMenu(menu_label_t label, menu_title_t title, menu_prompt_t prompt, const char *key)
{
    this->menuLabel = label;
    this->menuTitle = title;
    this->menuPrompt = prompt;
    this->key = key;

    windowSize = menuManager.getScreenMaxY(); // subtract for menu name
    windowStart = 0;                          // TODO - set according to current selected value
    activeIndex = windowStart;

    for (uint8_t i = 0; i < numMenuColors; i++)
    {
        items.add(new ColorMenuItem(menuColors[i]));
    }
}

/**
 * @brief Destructor
 */
ColorListMenu::~ColorListMenu()
{
    // Clean up target menu list by freeing all memory
    uint8_t size = items.size();
    for (uint8_t i = 0; i < size; i++)
    {
        MenuItem *item = items[i];
        items.removeAt(i);
        delete (item);
    }
    items.clear();
}


// void ColorListMenu::onDisplay(bool active)
// {
//     Log.traceln("ColorListMenu::onDisplay - BEGIN");

//     uint8_t size = items.size();
//     displayManager.clear();
//     displayManager.setCursor(0, 0);
//     displayManager.println(menuTitle);
//     uint8_t windowEnd = windowStart + windowSize - 1;
//     if( windowEnd > size )
//     {
//         windowEnd = size-1;
//     }
//     Log.traceln("ColorListMenu::onDisplay - start=%d, end=%d, ai=%d, ws=%d, size=%d", windowStart, windowEnd, activeIndex, windowSize, size);
//     for (uint8_t i = windowStart; i <= windowEnd; i++)
//     {
//         if (i == activeIndex)
//         {
//             displayManager.setTextColor(BLACK, WHITE);
//         }
//         else
//         {
//             displayManager.setTextColor(WHITE);
//         }
//         displayManager.print(menuPrompt);
//         displayManager.println(menuColors[i]->name);
//         displayManager.setTextColor(WHITE);
//     }
//     displayManager.setRefresh(true);
//     Log.traceln("ColorListMenu::onDisplay - END");
// }

void ColorListMenu::onButtonPush()
{
    Log.traceln("Saving color: %s", menuColors[activeIndex]->name);

    prefManager.set(key, (uint32_t)menuColors[activeIndex]->value);
    menuManager.popAndDisplay();

    // menuManager.pop();
    // menuManager.display();
}
