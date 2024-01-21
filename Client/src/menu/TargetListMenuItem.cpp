/**
 * @file TargetListMenuItem.cpp
 * @brief Menu item that lists all targets for editing
 * @note Must call initialize before using this item
 * @date Jan 19, 2024
 * @author cyberreefguru
*/
#include "TargetListMenuItem.h"
#include "DisplayManager.h"
#include "MenuManager.h"
#include "TargetManager.h"

TargetListMenuItem::TargetListMenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt)
{
    this->menuLabel = label;
    this->menuTitle = title;
    this->menuPrompt = prompt;

    windowSize = menuManager.getScreenMaxY(); // subtract for menu name
    windowStart = 0; // TODO - set according to current selected value
    activeIndex = windowStart;
}

TargetListMenuItem::~TargetListMenuItem()
{
    // Clean up target menu list by freeing all memory
    uint8_t size = items.size();
    for(uint8_t i=0;i<size; i++)
    {
        MenuItem* item = items[i];
        items.removeAt(i);
        delete(item);
    }
    items.clear();
}

void TargetListMenuItem::initialize()
{
    Log.traceln("TargetListMenuItem::initialize - BEGIN");

    ArrayList<Target*> *targets = targetManager.getTargetList();
    
    Log.traceln("TargetListMenuItem::initialize - targets: %s", prefManager.getTargetsBuffer() );

    if( targets != nullptr )
    {
        uint8_t size = targets->size();
   
        Log.traceln("TargetListMenuItem::initialize - size=%d", size);
        for(uint8_t i=0;i<size; i++)
        {
            TargetMenuItem *tmi = new TargetMenuItem(targets->get(i));
            Log.traceln("TargetListMenuItem::initialize - target=%s", tmi->getMenuLabel());
            items.add( tmi);
        }
    }
    else
    {
        Log.errorln("TargetListMenuItem::initialize - targets is null");
    }
    Log.traceln("TargetListMenuItem::initialize - END");

}
