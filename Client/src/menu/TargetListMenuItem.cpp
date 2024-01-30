/**
 * @brief Menu item that lists all targets for editing
 * @file TargetListMenuItem.cpp
 * @note Must call initialize before using this item
 * @date Jan 19, 2024
 * @author cyberreefguru
 */
#include "TargetListMenuItem.h"
#include "DisplayManager.h"
#include "MenuManager.h"
#include "TargetManager.h"
#include "Helper.h"

TargetListMenuItem::TargetListMenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt)
{
    this->menuLabel = label;
    this->menuTitle = title;
    this->menuPrompt = prompt;

    windowSize = menuManager.getScreenMaxY(); // subtract for menu name
    windowStart = 0;                          // TODO - set according to current selected value
    activeIndex = windowStart;
}

TargetListMenuItem::~TargetListMenuItem()
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
 * @brief Initializes the list with the current targets
 */
void TargetListMenuItem::initialize()
{
    Log.traceln("TargetListMenuItem::initialize - BEGIN");

    // If we have items in the list, remove all of them and free them
    uint8_t isize = items.size();
    if (isize > 0)
    {
        clear();
    }

    Log.traceln("TargetListMenuItem::initialize - creating create item");
    tcmi = new TargetCreateMenuItem();
    items.add(tcmi);

    // Build menu items for each target
    ArrayList<Target *> *targets = targetManager.getTargetList();
    Log.traceln("TargetListMenuItem::initialize - targets: %s", prefManager.getTargetsBuffer());
    if (targets != nullptr)
    {
        uint8_t size = targets->size();
        Log.traceln("TargetListMenuItem::initialize - targets size=%d", size);

        for (uint8_t i = 0; i < size; i++)
        {
            // targetManager.dumpTargets("- ");
            Target *t = targets->get(i);
            Log.traceln("TargetListMenuItem::initialize - new menu item target[%d].nid='%d' @ %X", i, t->targetNodeId, t);
            TargetMenuItem *tmi = new TargetMenuItem(t);
            if( items.add(tmi) == false)
            {
                Helper::fatal("TargetListMenuItem::initialize - unable to add target menu item to list");
            }
            targetManager.dumpTargets("-- ");

            // Log.traceln("TargetListMenuItem::initialize - added new menu item[%i] - '%s'; target @ %X", i, tmi->getMenuLabel(), t);
        }
    }
    else
    {
        Log.errorln("TargetListMenuItem::initialize - targets is null");
    }
    Log.traceln("TargetListMenuItem::initialize - END");
}

void TargetListMenuItem::onDisplay(bool active)
{
    Log.traceln("TargetListMenuItem::onDisplay - BEGIN");

    // See if list of targets has changed
    // items should always equal target.size + 1 due to create item
    ArrayList<Target *> *targets = targetManager.getTargetList();

    uint8_t tsize = targets->size();
    uint8_t isize = items.size();
    if ((isize - 1) != tsize)
    {
        Log.traceln("TargetListMenuItem::onDisplay - target size (%d) <> menu size (%d)", tsize, isize);
        initialize();
        activeIndex = 0;
    }

    // Display items
    ListMenu::onDisplay(active);

    Log.traceln("TargetListMenuItem::onDisplay - END");
}

/**
 * @brief Clears menu list from all items
 */
void TargetListMenuItem::clear()
{
    Log.traceln("TargetListMenuItem::clear - BEGIN");

    // Destroy create menu item
    if (tcmi != nullptr)
    {
        items.remove(tcmi); // remove from list
        delete (tcmi); // Destory and free memory
        tcmi = nullptr;
    }

    // If we have items in the list, destroy and free them
    uint8_t isize = items.size();
    if (isize > 0)
    {
        for (uint8_t i = 0; i < isize; i++)
        {
            TargetMenuItem *tmi = (TargetMenuItem *)items.get(i);
            if (tmi != nullptr)
            {
                delete (tmi);
            }
        }
    }
    items.clear();

    Log.traceln("TargetListMenuItem::clear - END");
}
