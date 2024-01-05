/*
 * MenuItem.cpp
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */
#include "MenuManager.h"

MenuItem::MenuItem()
{
}

MenuItem::~MenuItem()
{
}

MenuItem::MenuItem(const char *title, const char *label)
{
    this->title = title;
    this->label = label;
}

// void MenuItem::initialize(const char *label, MenuItem **items, uint8_t numItems)
// {
//     this->label = label;
//     this->items = items;
//     this->numItems = numItems;
// }

// void MenuItem::setChildren(MenuItem** items, uint8_t numItems)
// {
//     this->items = items;
//     this->numItems = numItems;
// }


void MenuItem::onDisplay()
{
    Log.traceln("MenuItem::onDisplay - BEGIN");

    if (label != nullptr)
    {
        displayManager.clear();
        displayManager.setCursor(0, 0);
        if (active)
        {
            displayManager.setTextColor(BLACK, WHITE);
        }
        else
        {
           displayManager.setTextColor(WHITE);
        }
        displayManager.println(label);
        displayManager.setTextColor(WHITE);
        displayManager.setRefresh(true);
    }
    else
    {
        Log.errorln("MenuItem::onDisplay - Menu Item has no label!");
    }
    Log.traceln("MenuItem::onDisplay - END");
}

void MenuItem::onEvent(ButtonEvent be)
{
    Log.traceln("MenuItem::onEvent - %s", ++be);
}

// MenuItem *MenuItem::getActive()
// {
//     MenuItem *item = nullptr;
    
//     if( numItems == 0 && active == true )
//     {
//         item = this;
//     }
//     else if (items != nullptr && numItems > 0)
//     {
//         for (uint8_t i = 0; i < numItems; i++)
//         {
//             if (items[i]->active)
//             {
//                 item = items[i];
//                 break;
//             }
//         }
//     }

//     return item;
// }

// uint8_t MenuItem::getActiveIndex()
// {
//     // Log.traceln("Getting Active Index");
//     uint8_t index = 0;
//     if (items != nullptr && numItems > 0)
//     {
//         for (uint8_t i = 0; i < numItems; i++)
//         {
//             if (items[i]->active)
//             {
//                 index = i;
//                 // Log.traceln("Found Index: %d", index);
//                 // TODO - we may need to adjust window here
//                 break;
//             }
//         }
//     }

//     // Log.traceln("Active Index: %d", index);
//     return index;
// }

// void MenuItem::activateNext()
// {
//     if (numItems > 0)
//     {
//         uint8_t cur = getActiveIndex();
//         items[cur]->active = false;
//         if ((cur+1) == numItems)
//         {
//             cur=0;
//             windowStart = 0;
//         }
//         else
//         {
//             cur += 1;
//             if( cur == (windowStart+6) )
//             {
//                 windowStart += 1;
//             }
//         }
//         items[cur]->active = true;
//     }
//     else
//     {
//         Log.warningln("No children items");
//     }
// }

// void MenuItem::activatePrevious()
// {
//     if (numItems > 0)
//     {
//         uint8_t cur = getActiveIndex();
//         items[cur]->active = false;
//         if (cur == 0)
//         {
//             cur=numItems-1;
//             windowStart = cur-5;
//         }
//         else
//         {
//             cur -= 1;
//             if( cur == (windowStart-1))
//             {
//                 windowStart = cur;
//             }
//         }
//         items[cur]->active = true;
//     }
//     else
//     {
//         Log.warningln("No children items");
//     }
// }