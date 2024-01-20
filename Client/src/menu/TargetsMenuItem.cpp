/**
 * @file TargetsMenuItem.cpp
 * @brief Menu item that lists all targets for editing
 * @date Jan 19, 2024
 * @author cyberreefguru
*/
#include "TargetsMenuItem.h"
#include "DisplayManager.h"
#include "MenuManager.h"
#include "TargetManager.h"

TargetsMenuItem::TargetsMenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt)
{
    this->menuLabel = label;
    this->menuTitle = title;
    this->menuPrompt = prompt;

    windowSize = menuManager.getScreenMaxY(); // subtract for menu name
    windowStart = 0; // TODO - set according to current selected value
    activeIndex = windowStart;
}

TargetsMenuItem::~TargetsMenuItem()
{
    free(items);
}

void TargetsMenuItem::initialize()
{
    Log.traceln("TargetsMenuItem::initialize - BEGIN");

    // ArrayList<TargetMenuItem*> *targetMenuItems;
    ArrayList<Target*> *targets = targetManager.getTargets();
    if( targets != nullptr )
    {
        numItems = targets->size();
        Log.traceln("TargetsMenuItem::TargetsMenuItem - size=%d", numItems);
        items = (MenuItem**)(new TargetMenuItem* [numItems]);

        for(uint8_t i=0;i<numItems; i++)
        {
            items[i] = new TargetMenuItem(targets->get(i));
        }
    }
    else
    {
        Log.errorln("TargetsMenuItem::TargetsMenuItem - targets is null");
    }
    Log.traceln("TargetsMenuItem::initialize - END");

}

// void TargetsMenuItem::onDisplay(bool active)
// {
//     Log.traceln("TargetsMenuItem::onDisplay - BEGIN");

//     displayManager.clear();
//     displayManager.setCursor(0, 0);
//     displayManager.println(menuTitle);
//     uint8_t windowEnd = windowStart + windowSize - 1;
//     if( windowEnd > numItems )
//     {
//         windowEnd = numItems-1;
//     }
//     Log.traceln("TargetsMenuItem::onDisplay - start=%d, end=%d, ai=%d, ws=%d, ni=%d", windowStart, windowEnd, activeIndex, windowSize, numItems);
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
//     Log.traceln("TargetsMenuItem::onDisplay - END");
// }

// void TargetsMenuItem::onButtonPush()
// {
//     Log.traceln("Saving color: %s", menuColors[activeIndex]->name);

//     prefManager.set(key, (uint32_t)menuColors[activeIndex]->value);
    
//     menuManager.pop();
//     menuManager.display();
// }
