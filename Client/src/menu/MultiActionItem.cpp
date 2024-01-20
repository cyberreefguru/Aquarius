/**
 * @brief Renders specified menu items and adds OK/CANCEL buttons.
 * @note Calls onAction when OK pushed; pops item from stack when CANCEL pushed.
 * @file MultiActionItem.cpp
 * @date Jan 8, 2024
 * @author cyberreefguru
 */
#include "MultiActionItem.h"
#include "MenuManager.h"
#include "DisplayManager.h"

using namespace std::placeholders;

MultiActionItem::MultiActionItem(menu_label_t label, menu_title_t title, MenuItem *items[], uint8_t numItems)
{
    this->menuTitle = title;
    this->menuLabel = label;
    this->menuPrompt = label;
    this->items = items;
    this->numItems = numItems;

    this->ok = new ActionButtonItem("OK", std::bind(&MultiActionItem::onOk, this));
    this->cancel = new ActionButtonItem("CANCEL", std::bind(&MultiActionItem::onCancel, this));
}

MultiActionItem::~MultiActionItem()
{
    // free(inputBuff);
    free(ok);
    free(cancel);
}

void MultiActionItem::onOk()
{
    Log.traceln("MultiActionItem::onOk - BEGIN");

    // Execute action for each item
    for (uint8_t i = 0; i < numItems; i++)
    {
        Log.traceln("MultiActionItem::onOk - calling onAction for item %d", i);
        items[i]->onAction();
    }

    // Reset and clear menu item
    onCancel();

    Log.traceln("MultiActionItem::onOk - END");
}

void MultiActionItem::onCancel()
{
    Log.traceln("MultiActionItem::onCancel - BEGIN");

    // Reset current item
    curItem = 0;

    // Pop us off the menu
    menuManager.pop();

    // display the currnet top of the queue
    menuManager.display();

    Log.traceln("MultiActionItem::onCancel - END");
}

void MultiActionItem::onDisplay(bool active)
{
    Log.traceln("MultiActionItem::onDisplay - BEGIN");

    if (menuTitle == nullptr)
    {
        Log.errorln("MultiActionItem::onDisplay - title is null!");
        return;
    }

    displayManager.clear();
    displayManager.setCursor(0, 0);
    displayManager.println(menuTitle);
    displayManager.addCursorY(4); // put a little gap beween title and menu item

    for (uint8_t i = 0; i < numItems; i++)
    {
        Log.traceln("MultiActionItem::onDisplay - Displaying MenuItem[%d], curItem=%d", i, curItem);
        items[i]->onDisplay((curItem == i));
        displayManager.println(); // new line between items
        displayManager.addCursorY(2); // put a little gap beween title and menu item
    }

    displayManager.addCursorY(2); // put a little gap beween item and next item
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
        Log.traceln("MultiActionItem::onButtonUp: In component, sending button to component");
        items[curItem]->onButtonUp();
    }
    else if (curItem == numItems)
    {
        // @ OK; move to next item
        Log.traceln("MultiActionItem::onButtonDown: on OK, moving to last component");
        curItem--; 
    }
    else if (curItem == numItems + 1)
    {
        // @ Cancel; move to first item
        Log.traceln("MultiActionItem::onButtonDown: on CANCEL, moving to first component");
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
        Log.traceln("MultiActionItem::onButtonDown: In component, sending button to component");
        items[curItem]->onButtonDown();
    }
    else if (curItem == numItems)
    {
        // @ OK; move to first item
        Log.traceln("MultiActionItem::onButtonDown: on OK, moving to first component");
        curItem = 0;
    }
    else if (curItem == numItems + 1)
    {
        // @ Cancel; move to first item
        Log.traceln("MultiActionItem::onButtonDown: on CANCEL, moving to first component");
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
        Log.traceln("MultiActionItem::onButtonLeft: In component, sending button to component");
        items[curItem]->onButtonLeft();
    }
    else if (curItem == numItems)
    {
        // @ OK; move to last item
        Log.traceln("MultiActionItem::onButtonLeft: on OK, moving to last component");
        curItem--;
    }
    else if (curItem == numItems + 1)
    {
        // @ Cancel; Move to OK
        Log.traceln("MultiActionItem::onButtonLeft: on CANCEL, moving to OK");
        curItem--;
    }
    onDisplay(false);
}

void MultiActionItem::onButtonRight()
{
    Log.traceln("MultiActionItem::onButtonRight: BEGIN - curItem=%d", curItem);

    if (curItem >= 0 && curItem < numItems)
    {
        // @ Input; Send event to item
        Log.traceln("MultiActionItem::onButtonRight: In component, sending button to component");
        items[curItem]->onButtonRight();
    }
    else if (curItem == numItems)
    {
        // @ OK; move to cancel
        Log.traceln("MultiActionItem::onButtonRight: on OK, moving to CANCEl");
        curItem++;
    }
    else if (curItem == numItems + 1)
    {
        // @ Cancel; move to first item
        Log.traceln("MultiActionItem::onButtonRight: on CANCEL, moving to first component");
        curItem = 0;
    }
    onDisplay(false);
    Log.traceln("MultiActionItem::onButtonRight: END - curItem=%d", curItem);
}

void MultiActionItem::onButtonPush()
{
    Log.traceln("MultiActionItem::onButtonPush: BEGIN - curItem=%d", curItem);

    if (curItem >= 0 && curItem < numItems)
    {
        // @ Input; call item
        // ((ActionMenuItem *)items[curItem])->onButtonPush();

        // Advance to next item
        Log.traceln("MultiActionItem::onButtonPush: In component, moving to next menu item");
        curItem++;
        onDisplay(false);
    }
    else if (curItem == numItems)
    {
        // @ OK; Call onOk
        Log.traceln("MultiActionItem::onButtonPush: In OK, calling onOK");
        onOk();
    }
    else if (curItem == numItems + 1)
    {
        // @ Cancel; call onCancel
        Log.traceln("MultiActionItem::onButtonPush: In CANCEL, calling onCANCEL");
        onCancel();
    }
    Log.traceln("MultiActionItem::onButtonPush: END - curItem=%d", curItem);

}