/*
 * MultiActionItem.cpp
 *
 *  Created on: Jan 8, 2024
 *      Author: cyberreefguru
 */
#include "MenuManager.h"
#include "MultiActionItem.h"
#include "ActionMenuItem.h"

MultiActionItem::MultiActionItem(menu_label_t label, menu_title_t title, ActionMenuItem *items[], uint8_t numItems)
{
    this->menuTitle = title;
    this->menuLabel = label;
    this->menuPrompt = label;
    this->items = (MenuItem **)items;
    this->numItems = numItems;

    //     // ok = new ActionMenuItem("OK", "", "OK", this->item);
    //     // cancel = new ActionMenuItem("CANCEL", "", "CANCEL", this->item);
    this->ok = new ActionMenuItem("OK", "", "OK", std::bind(&MultiActionItem::onOk, this));
    this->cancel = new ActionMenuItem("CANCEL", "", "CANCEL", std::bind(&MultiActionItem::onCancel, this));
}

MultiActionItem::~MultiActionItem()
{
    // free(inputBuff);
    free(ok);
    free(cancel);
}

void MultiActionItem::onOk()
{
    // Execute action for each item
    for (uint8_t i = 0; i < numItems; i++)
    {
        ((ActionMenuItem *)items[i])->onAction();
    }

    // Reset and clear menu item
    onCancel();
}

void MultiActionItem::onCancel()
{
    // Reset current item
    curItem = 0;

    // Pop us off the menu
    menuManager.pop();

    // display the currnet top of the queue
    menuManager.display();
}

void MultiActionItem::onDisplay(bool active)
{
    Log.traceln("MultiActionItem::onDisplay - BEGIN");
    if (menuLabel == nullptr)
    {
        Log.errorln("MultiActionItem::onDisplay - Label is null!");
        return;
    }

    displayManager.clear();
    displayManager.setCursor(0, 0);
    displayManager.println(menuTitle);

    for (uint8_t i = 0; i < numItems; i++)
    {
        Log.traceln("Displaying Action[%d]", i);
        ((ActionMenuItem *)items[i])->onDisplay((curItem == i));
        displayManager.println(); // new line between items
    }

    displayManager.println(); // new line between items and buttons

    ok->onDisplay((curItem == numItems));
    displayManager.print("  ");
    cancel->onDisplay((curItem == numItems + 1));

    displayManager.setRefresh(true);

    Log.traceln("MultiActionItem::onDisplay - END");
}

void MultiActionItem::onButtonUp()
{
    Log.traceln("MultiActionItem::onButtonUp: curItem=%d", curItem);
    if (curItem >= 0 && curItem < numItems)
    {
        // @ Input; call up
        ((ActionMenuItem *)items[curItem])->onButtonUp();
    }
    else if (curItem == numItems)
    {
        // @ OK; move to next item
        curItem--; 
    }
    else if (curItem == numItems + 1)
    {
        // @ Cancel; move to first item
        curItem = 0;
    }
    onDisplay(false);
}

void MultiActionItem::onButtonDown()
{
    Log.traceln("MultiActionItem::onButtonDown: curItem=%d", curItem);
    if (curItem >= 0 && curItem < numItems)
    {
        // @ Input; call down
        ((ActionMenuItem *)items[curItem])->onButtonDown();
    }
    else if (curItem == numItems)
    {
        // @ OK; move to first item
        curItem = 0;
    }
    else if (curItem == numItems + 1)
    {
        // @ Cancel; move to first item
        curItem = 0;
    }
    onDisplay(false);
}

void MultiActionItem::onButtonLeft()
{
    Log.traceln("MultiActionItem::onButtonLeft: curItem=%d", curItem);

    if (curItem >= 0 && curItem < numItems)
    {
        // @ Input; Send event to item
        ((ActionMenuItem *)items[curItem])->onButtonLeft();
    }
    else if (curItem == numItems)
    {
        // @ OK; move to last item
        curItem = numItems - 1;
    }
    else if (curItem == numItems + 1)
    {
        // @ Cancel; Move to OK
        curItem--;
    }
    onDisplay(false);
}

void MultiActionItem::onButtonRight()
{
    Log.traceln("MultiActionItem::onButtonRight: curItem=%d", curItem);

    if (curItem >= 0 && curItem < numItems)
    {
        // @ Input; Send event to item
        ((ActionMenuItem *)items[curItem])->onButtonRight();
    }
    else if (curItem == numItems)
    {
        // @ OK; move to cancel
        curItem++;
    }
    else if (curItem == numItems + 1)
    {
        // @ Cancel; move to first item
        curItem = 0;
    }
    onDisplay(false);
}

void MultiActionItem::onButtonPush()
{
    Log.traceln("MultiActionItem::onButtonPush: curItem=%d", curItem);

    if (curItem >= 0 && curItem < numItems)
    {
        // @ Input; call item
        // ((ActionMenuItem *)items[curItem])->onButtonPush();

        // Advance to next item
        curItem++;
        onDisplay(false);
    }
    else if (curItem == numItems)
    {
        // @ OK; Call onOk
        onOk();
    }
    else if (curItem == numItems + 1)
    {
        // @ Cancel; call onCancel
        onCancel();
    }
}