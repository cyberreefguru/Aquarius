/**
 * @brief Displays list of ColorList
 * @file ColorListMenu.cpp
 * @date Dec 31, 2023
 * @author cyberreefguru
 * 
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

/**
 * @brief overrrifs buttong push and saves the value to preferences.
 * 
 */
void ColorListMenu::onButtonPush()
{
    Log.traceln("Saving color: %s", menuColors[activeIndex]->name);

    prefManager.set(key, (uint32_t)menuColors[activeIndex]->value);
    menuManager.popAndDisplay();

}
