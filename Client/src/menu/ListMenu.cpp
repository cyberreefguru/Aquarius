/**
 * @file ListMenu.cpp
 * @brief displays a list of menu items via label; if button pushed, pushes that item to the stack
 * @date Jan 7, 2024
 * @author cyberreefguru
 */
#include "ListMenu.h"
#include "DisplayManager.h"
#include "MenuManager.h"

/**
 * @brief Constructor
 * @param label
 * @param title
 * @param prompt
 */
ListMenu::ListMenu(menu_label_t label, menu_title_t title, menu_prompt_t prompt)
{
    this->menuLabel = label;
    this->menuTitle = title;
    this->menuPrompt = prompt;

    windowSize = menuManager.getScreenMaxY() - 1; // subtract for menu name
    windowStart = 0;
    activeIndex = windowStart;
}

/**
 * @brief Desctructor
 */
ListMenu::~ListMenu()
{
}

/**
 * @brief Initializes the ListMenu with the items to display
 * @param items List of pointers to MenuItems
 * @param numItems The number of items
 */
void ListMenu::initialize(MenuItem **items, uint8_t numItems)
{
    if (items != nullptr && numItems > 0)
    {
        for (uint8_t i = 0; i < numItems; i++)
        {
            this->items.add(items[i]);
        }
    }
}

/**
 * @brief Initializes the ListMenu with the items to display
 * @param items List of pointers to MenuItems
 */
void ListMenu::initialize(ArrayList<MenuItem *> *items)
{
    this->items.addAll(*items);
}

/**
 * @brief Renders the list of menu item by displaying each item's label
 * @param active if true, highlight item (unused)
 */
void ListMenu::onDisplay(bool active)
{
    // Log.traceln("ListMenu::onDisplay - BEGIN");

    uint8_t size = items.size();

    if (size == 0)
    {
        Log.errorln("ListMenu::onDisplay - no children to display");
        return;
    }
    else
    {
        Log.errorln("ListMenu::onDisplay - display %d children", size);
    }

    displayManager.clear();
    displayManager.setCursor(0, 0);
    displayManager.println(menuTitle);
    uint8_t windowEnd = windowStart + windowSize - 1;
    if (windowEnd >= size)
    {
        windowEnd = size - 1;
    }
    Log.traceln("ListMenu::onDisplay - start=%d, end=%d, ai=%d, ws=%d, size=%d", windowStart, windowEnd, activeIndex, windowSize, size);
    for (uint8_t i = windowStart; i <= windowEnd; i++)
    {
        MenuItem *item = items.get(i);
        if (item != nullptr)
        {
            // Log.traceln("ListMenu::onDisplay - item[%d].label='%s'", i, item->getMenuLabel());
            item->onLabelDisplay(i == activeIndex);
        }
        else
        {
            Log.errorln("ListMenu::onDisplay - item[%d] is null!", i);
        }
    }
    displayManager.setRefresh(true);
    // Log.traceln("ListMenu::onDisplay - END");
}

/**
 * @brief overrides onButtonUp to move to previous item
 */
void ListMenu::onButtonUp()
{
    activatePrevious();
    onDisplay(false);
}

/**
 * @brief overrides onButtonDown to move to next item
 */
void ListMenu::onButtonDown()
{
    activateNext();
    onDisplay(false);
}

/**
 * @brief overrides onButtonLeft to move return to previous menu item
 */
void ListMenu::onButtonLeft()
{
    menuManager.popAndDisplay();
}

/**
 * @brief overrides onButtonRight act as button push
 */
void ListMenu::onButtonRight()
{
    onButtonPush();
}

/**
 * @brief overrides onButtonPush to push active item onto menu stack
 */
void ListMenu::onButtonPush()
{
    menuManager.push(items[activeIndex]);
}

/**
 * @brief returns active menu item
 * @return currently active menu item
 */

MenuItem *ListMenu::getActive()
{
    if (activeIndex >= 0 && activeIndex < items.size())
    {
        return items[activeIndex];
    }
    else
    {
        Log.errorln("ListMenu:getActive - index out of bounds; returning null");
        return nullptr;
    }
}

/**
 * @brief returns active menu item index
 * @return active menu item index
 */
uint8_t ListMenu::getActiveIndex()
{
    return activeIndex;
}

/**
 * @brief activate the next menu item in the list; wraps to first if at last
 * 
 */
void ListMenu::activateNext()
{
    uint8_t windowEnd = windowStart + windowSize;
    Log.traceln("ListMenu::activateNext - start=%d, end=%d, active=%d, size=%d", windowStart, windowEnd, activeIndex, windowSize);
    if (activeIndex == (windowEnd - 1))
    {
        // We are at the end of the window
        // See if we're also at the end of the list
        if (activeIndex == items.size() - 1)
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
    if (activeIndex > items.size() - 1)
    {
        Log.warningln("ListMenu::activateNext - active index FUBARed; reseting");
        activeIndex = 0;
    }
    Log.traceln("ListMenu::activateNext - start=%d, end=%d, active=%d, size=%d", windowStart, windowEnd, activeIndex, windowSize);
}

/**
 * @brief activates previous menu item in list; wraps to last if at first
 */
void ListMenu::activatePrevious()
{
    uint8_t windowEnd = windowStart + windowSize;
    uint8_t size = items.size();

    Log.traceln("ListMenu::activatePrevious - start=%d, end=%d, active=%d, size=%d", windowStart, windowEnd, activeIndex, windowSize);
    if (activeIndex == windowStart)
    {
        // We are at the top of the window
        // See if we're also at the top of the list
        if (activeIndex == 0)
        {
            // We are at the start of the list
            // Side window to end of list
            if (windowSize >= size)
            {
                // Windows size > number of items
                // Set window to 0 and active to last item
                windowStart = 0;
                activeIndex = size - 1;
            }
            else
            {
                // Window is < number items
                // Compute starting point
                windowStart = size - windowSize;
                activeIndex = size - 1;
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
    if (activeIndex > items.size() - 1)
    {
        Log.warningln("ListMenu::activatePrevious - active index FUBARed; reseting");
        activeIndex = 0;
    }
    Log.traceln("ListMenu::activatePrevious - start=%d, end=%d, active=%d, size=%d", windowStart, windowEnd, activeIndex, windowSize);
}