/*
 * MultiNumberInputItem.cpp
 *
 *  Created on: Jan 8, 2024
 *      Author: cyberreefguru
 */
#include "MultiNumberInputItem.h"

MultiNumberInputItem::MultiNumberInputItem(menu_label_t label, menu_title_t title, MenuItem *items[], uint8_t numItems)
{
    this->menuTitle = title;
    this->menuLabel = label;
    this->menuPrompt = label;
    this->items = items;
    this->numItems = numItems;

    if (numItems > 0)
    {
        ((NumberInput *)items[0])->active = true;
    }
}

MultiNumberInputItem::~MultiNumberInputItem()
{
    // free(inputBuff);
}

void MultiNumberInputItem::onDisplay()
{
    Log.traceln("MultiNumberInputItem::onDisplay - BEGIN");
    if (menuLabel == nullptr)
    {
        Log.errorln("MultiNumberInputItem::onDisplay - Label is null!");
        return;
    }

    displayManager.clear();
    displayManager.setCursor(0, 0);
    displayManager.println(menuTitle);
    for (uint8_t i = 0; i < numItems; i++)
    {
        Log.traceln("Displaying NumberInput[%d]", i);
        items[i]->onDisplay();
    }

    displayManager.println();

    if (curInput == numItems)
    {
        displayManager.setTextColor(BLACK, WHITE);
    }
    else
    {
        displayManager.setTextColor(WHITE);
    }
    displayManager.print("OK");
    displayManager.setTextColor(WHITE);

    displayManager.print("  ");

    if (curInput == numItems + 1)
    {
        displayManager.setTextColor(BLACK, WHITE);
    }
    else
    {
        displayManager.setTextColor(WHITE);
    }
    displayManager.print("CANCEL");
    displayManager.setTextColor(WHITE);

    displayManager.setRefresh(true);

    Log.traceln("MultiNumberInputItem::onDisplay - END");
}

void MultiNumberInputItem::onButtonUp()
{
    Log.traceln("MultiNumberInputItem::onButtonUp: curInput=%d", curInput);
    if (curInput >= 0 && curInput < numItems)
    {
        // @ Input
        ((NumberInput *)items[curInput])->active = true; // make sure it's active
        ((NumberInput *)items[curInput])->onButtonUp();  // call input up
    }
    else if (curInput == numItems)
    {
        // @ OK; move to input
        curInput--; // move to last input
        ((NumberInput *)items[curInput])->active = true;
    }
    else if (curInput == numItems + 1)
    {
        // @ Cancel; move to input
        curInput = 0; // move to input
        ((NumberInput *)items[curInput])->active = true;
    }
    onDisplay();
}

void MultiNumberInputItem::onButtonDown()
{
    Log.traceln("MultiNumberInputItem::onButtonDown: curInput=%d", curInput);
    if (curInput >= 0 && curInput < numItems)
    {
        // @ Input
        ((NumberInput *)items[curInput])->active = true;  // make sure it's active
        ((NumberInput *)items[curInput])->onButtonDown(); // call input down
    }
    else if (curInput == numItems)
    {
        // @ OK; move to input
        curInput = 0; // move to first input
        ((NumberInput *)items[curInput])->active = true;
    }
    else if (curInput == numItems + 1)
    {
        // @ Cancel; move to input
        curInput = 0; // move to first input
        ((NumberInput *)items[curInput])->active = true;
    }
    onDisplay();
}

void MultiNumberInputItem::onButtonLeft()
{
    Log.traceln("MultiNumberInputItem::onButtonLeft: curInput=%d", curInput);

    if (curInput >= 0 && curInput < numItems)
    {
        // @ Input; Send event to input item
        ((NumberInput *)items[curInput])->onButtonLeft();
    }
    else if (curInput == numItems)
    {
        // @ OK; move to last input item
        curInput = numItems - 1;
        ((NumberInput *)items[curInput])->active = true;
    }
    else if (curInput == numItems + 1)
    {
        // @ Cancel; Move to OK
        curInput--;
    }
    onDisplay();
}

void MultiNumberInputItem::onButtonRight()
{
    Log.traceln("MultiNumberInputItem::onButtonRight: curInput=%d", curInput);

    if (curInput >= 0 && curInput < numItems)
    {
        // @ Input; Send event to input item
        ((NumberInput *)items[curInput])->onButtonRight();
    }
    else if (curInput == numItems)
    {
        // @ OK; move to cancel
        curInput++; // Move to canel
    }
    else if (curInput == numItems + 1)
    {
        // @ Cancel; move to first item
        curInput = 0;
        ((NumberInput *)items[curInput])->active = true;
        //((NumberInput *)items[curInput])->curDigit = ((NumberInput *)items[curInput])->numDigits - 1;
    }
    onDisplay();
}

void MultiNumberInputItem::onButtonPush()
{
    Log.traceln("MultiNumberInputItem::onButtonPush: curInput=%d", curInput);

    if (curInput >= 0 && curInput < numItems)
    {
        // @ Input
        ((NumberInput *)items[curInput])->onButtonPush();
        curInput++;
        if (curInput < numItems)
        {
            ((NumberInput *)items[curInput])->active = true;
        }
        onDisplay();
    }
    else if (curInput == numItems)
    {
        // @ OK; Save values
        for (uint8_t i = 0; i < numItems; i++)
        {
            ((NumberInput *)items[i])->setValue();
            ((NumberInput *)items[i])->active = false;
        }
        curInput=0;
        ((NumberInput *)items[curInput])->active = true;

        // Save value and pop us off the menu
        menuManager.pop();
        // display the currnet top of the queue
        menuManager.display();
    }
    else if (curInput == numItems + 1)
    {
        // @ Cancel; reset input value to original
        for (uint8_t i = 0; i < numItems; i++)
        {
            ((NumberInput *)items[i])->initializeValue();
            ((NumberInput *)items[i])->active = false;
        }
        curInput=0;
        ((NumberInput *)items[curInput])->active = true;

        // Save value and pop us off the menu
        menuManager.pop();
        // display the currnet top of the queue
        menuManager.display();
    }
}