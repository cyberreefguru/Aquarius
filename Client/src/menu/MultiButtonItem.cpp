/**
 * @brief Renders specified menu items and specified buttons.
 * @note Sends ButtonEvent to currently active item; only sends push to buttons
 * @note Must call initialize before using this item
 * @file MultiButtonItem.cpp
 * @date Jan 21, 2024
 * @author cyberreefguru
 */
#include "MultiButtonItem.h"
#include "MenuManager.h"
#include "DisplayManager.h"

using namespace std::placeholders;

/**
 * @brief Constructor
 * @param label
 * @param title
 * @param prompt
 */
MultiButtonItem::MultiButtonItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt)
{
    this->menuTitle = title;
    this->menuLabel = label;
    this->menuPrompt = prompt;
    initialize();
}

/**
 * @brief Destructor
 */
MultiButtonItem::~MultiButtonItem()
{
}

/**
 * @brief Overrides initialize to call super and derived
 * @param items
 * @param numItems
 */
void MultiButtonItem::initialize(MenuItem **items, uint8_t numItems)
{
    ListMenu::initialize(items, numItems);
    initialize();
}

/**
 * @brief Overrides initialize to call super and derived
 * @param items
 */
void MultiButtonItem::initialize(ArrayList<MenuItem *> *items)
{
    ListMenu::initialize(items);
    initialize();
}

/**
 * @brief Overrides initialize to call super and derived
 * @param items
 */
void MultiButtonItem::initialize(ArrayList<MenuItem *> *items, ArrayList<ActionButtonItem *> *buttons)
{
    ListMenu::initialize(items);
    this->buttons.addAll(*buttons);
    initialize();
}

/**
 * @brief Internal initializaiton routine
 */
void MultiButtonItem::initialize()
{
}

/**
 * @brief Adds a item to item list
 */
void MultiButtonItem::addItem(MenuItem *item)
{
    items.add(item);
}

/**
 * @brief Adds a button to button list
 */
void MultiButtonItem::addButton(ActionButtonItem *button)
{
    buttons.add(button);
}

/**
 * @brief Overrides ListMenu onDisplay and renders all items and buttons
 * @param active
 */
void MultiButtonItem::onDisplay(bool active)
{
    Log.traceln("MultiButtonItem::onDisplay - BEGIN");

    if (menuTitle == nullptr)
    {
        Log.errorln("MultiButtonItem::onDisplay - title is null!");
        return;
    }

    uint8_t itemSize = items.size();
    uint8_t buttonSize = buttons.size();
    if (itemSize == 0)
    {
        Log.warningln("MultiButtonItem::onDisplay - multi-item has no items");
    }
    if (buttonSize == 0)
    {
        Log.warningln("MultiButtonItem::onDisplay - multi-item has no buttons");
    }
    if (itemSize == 0 && buttonSize == 0)
    {
        Log.errorln("MultiButtonItem::onDisplay - no items to display!");
        return;
    }

    // TODO - LOCK DISPLAY

    displayManager.clear();
    displayManager.setCursor(0, 0);
    displayManager.println(menuTitle);
    displayManager.addCursorY(4); // put a little gap between title and menu item

    for (uint8_t i = 0; i < itemSize; i++)
    {
        Log.traceln("MultiButtonItem::onDisplay - Displaying MenuItem[%d], activeIndex=%d", i, activeIndex);
        items[i]->onDisplay((activeIndex == i));
        // displayManager.println(); // new line between items
        displayManager.setCursorX(0);               // go to start of line
        displayManager.addCursorY(FONT_HEIGHT + 2); // put a little gap between menu items
    }

    displayManager.addCursorY(2); // put a little gap beween items and buttons

    for (uint8_t i = 0; i < buttonSize; i++)
    {
        Log.traceln("MultiButtonItem::onDisplay - Displaying Button[%d], activeIndex=%d", i, activeIndex);
        buttons[i]->onDisplay((activeIndex == (i + itemSize)));
        displayManager.addCursorX(2); // put a little gap between button items
    }

    displayManager.setRefresh(true);

    // TODO - UNLOCK DISPLAY

    Log.traceln("MultiButtonItem::onDisplay - END");
}

void MultiButtonItem::onButtonUp()
{
    if (inItemRange())
    {
        // Current within items area; send action to item
        Log.traceln("MultiButtonItem::onButtonUp - sending event to component");
        items[activeIndex]->onButtonUp();
        onDisplay(false);
    }
    else
    {
        activatePrevious();
        onDisplay(false);
    }
    Log.traceln("MultiButtonItem::onButtonUp - activeIndex=%d", activeIndex);
}

void MultiButtonItem::onButtonDown()
{
    if (inItemRange())
    {
        // Current within items area; send action to item
        Log.traceln("MultiButtonItem::onButtonDown - sending event to component");
        items[activeIndex]->onButtonDown();
        onDisplay(false);
    }
    else
    {
        activateNext();
        onDisplay(false);
    }
    Log.traceln("MultiButtonItem::onButtonDown - activeIndex=%d", activeIndex);
}

void MultiButtonItem::onButtonLeft()
{
    if (inItemRange())
    {
        // Current within items area; send action to item
        Log.traceln("MultiButtonItem::onButtonLeft - sending event to component");
        items[activeIndex]->onButtonLeft();
        onDisplay(false);
    }
    else
    {
        activatePrevious();
        onDisplay(false);
    }
    Log.traceln("MultiButtonItem::onButtonLeft - activeIndex=%d", activeIndex);
}

void MultiButtonItem::onButtonRight()
{
    if (inItemRange())
    {
        // Current within items area; send action to item
        Log.traceln("MultiButtonItem::onButtonRight - sending event to component");
        items[activeIndex]->onButtonRight();
        onDisplay(false);
    }
    else
    {
        activateNext();
        onDisplay(false);
    }
    Log.traceln("MultiButtonItem::onButtonRight - activeIndex=%d", activeIndex);
}

void MultiButtonItem::onButtonPush()
{
    if (inItemRange())
    {
        activateNext();
        onDisplay(false);
    }
    else
    {
        buttons[getActiveButtonIndex()]->onButtonPush();
    }

    Log.traceln("MultiButtonItem::onButtonPush - activeIndex=%d", activeIndex);
}

/**
 * @brief moves active index to next menu item in the list
 */
void MultiButtonItem::activateNext()
{
    uint8_t itemSize = items.size();
    uint8_t buttonSize = buttons.size();
    uint8_t size = itemSize + buttonSize;

    if (activeIndex > (size - 1))
    {
        // This should never happen, but let's protect ourselves
        activeIndex = 0;
    }
    else if (activeIndex < (size - 1))
    {
        // We are in range, advance to next item
        activeIndex++;
    }
    else if (activeIndex == (size - 1))
    {
        // We are at the end of the list, wrap around
        activeIndex = 0;
    }
}

/**
 * @brief moves active index to previous menu item in the list
 */
void MultiButtonItem::activatePrevious()
{
    uint8_t itemSize = items.size();
    uint8_t buttonSize = buttons.size();
    uint8_t size = itemSize + buttonSize;

    if (activeIndex > (size - 1))
    {
        // This should never happen, but let's protect ourselves
        activeIndex = 0;
    }
    else if (activeIndex == 0)
    {
        // We are at the begining of the list, wrap around
        activeIndex = (size - 1);
    }
    else if (activeIndex > 0)
    {
        // We are in range, advance to previous item
        activeIndex--;
    }
}

/**
 * @brief tests if active index is within item range
 * @return true if in range; false otherwise
 */
bool MultiButtonItem::inItemRange()
{
    bool b = false;
    uint8_t itemSize = items.size();
    uint8_t buttonSize = buttons.size();
    uint8_t size = itemSize + buttonSize;

    if (activeIndex > (size - 1))
    {
        Log.errorln("MultiButtonItem::inItemRange - active index out of max range: %d", activeIndex);
        activeIndex = 0;
    }
    if (activeIndex >= 0 && activeIndex < itemSize)
    {
        b = true;
    }

    return b;
}

/**
 * @brief tests if active index is within item range
 * @return true if in range; false otherwise
 */
bool MultiButtonItem::inButtonRange()
{
    bool b = false;
    uint8_t itemSize = items.size();
    uint8_t buttonSize = buttons.size();
    uint8_t size = itemSize + buttonSize;

    if (activeIndex > (size - 1))
    {
        Log.errorln("MultiButtonItem::inButtonRange - active index out of max range: %d", activeIndex);
        activeIndex = 0;
    }
    if ((activeIndex >= itemSize) && (activeIndex < size))
    {
        b = true;
    }
    return b;
}

uint8_t MultiButtonItem::getActiveItemIndex()
{
    uint8_t itemSize = items.size();
    uint8_t buttonSize = buttons.size();
    uint8_t size = itemSize + buttonSize;

    if (activeIndex > (size - 1))
    {
        Log.errorln("MultiButtonItem::getActiveItemIndex - active index out of max range: %d", activeIndex);
        activeIndex = 0;
    }
    return activeIndex;
}

uint8_t MultiButtonItem::getActiveButtonIndex()
{
    uint8_t itemSize = items.size();
    uint8_t buttonSize = buttons.size();
    uint8_t size = itemSize + buttonSize;
    uint8_t index = 0;
    if (activeIndex > (size - 1))
    {
        Log.errorln("MultiButtonItem::getActiveButtonIndex - active index out of max range: %d", activeIndex);
        activeIndex = 0;
    }
    if ((activeIndex >= itemSize) && (activeIndex < size))
    {
        index = activeIndex - itemSize;
    }
    return index;
}
