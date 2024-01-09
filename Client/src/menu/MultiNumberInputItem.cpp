/*
 * MultiNumberInputItem.cpp
 *
 *  Created on: Jan 8, 2024
 *      Author: cyberreefguru
 */
#include "MultiNumberInputItem.h"

MultiNumberInputItem::MultiNumberInputItem(const char *title, const char *label, MenuItem *items[], uint8_t numItems)
{
    this->title = title;
    this->label = label;
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
    if (label == nullptr)
    {
        Log.errorln("MultiNumberInputItem::onDisplay - Label is null!");
        return;
    }

    displayManager.clear();
    displayManager.setCursor(0, 0);
    displayManager.println(title);
    for (uint8_t i = 0; i < numItems; i++)
    {
        Log.traceln("Displaying Number Input %d", i);
        ((NumberInput *)items[i])->onDisplay();
        // inputs[i].onDisplay();
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
        // @ OK
        ((NumberInput *)items[numItems - 1])->active = true;
        ((NumberInput *)items[numItems - 1])->curDigit = 0;
        curInput--; // move to last input
    }
    else if (curInput == numItems + 1)
    {
        // @ Cancel
        curInput--; // move to OK
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
        // @ OK
        curInput++; // move to cancel
    }
    else if (curInput == numItems + 1)
    {
        // @ Cancel
        ((NumberInput *)items[0])->active = true;
        ((NumberInput *)items[0])->curDigit = 0;
        curInput = 0; // move to first input
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
        if (((NumberInput *)items[curInput])->active == false)
        {
            // cur item is no longer active; overflowed to left
            if (curInput == numItems - 1)
            {
                // Last input - move to previous input
                curInput--;

                // Active the input item
                ((NumberInput *)items[curInput])->curDigit = 0;
                ((NumberInput *)items[curInput])->active = true;
            }
            else if (curInput == 0)
            {
                // First input - advance to Cancel
                curInput = numItems + 1;
            }
        }
    }
    else if (curInput == numItems)
    {
        // @ OK; move to last input item
        curInput = numItems - 1;
        ((NumberInput *)items[curInput])->active = true;
        ((NumberInput *)items[curInput])->curDigit = 0;
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
        if (((NumberInput *)items[curInput])->active == false)
        {
            // cur item no longer active; overflowed to right
            if (curInput == numItems - 1)
            {
                // Last input - advance to OK
                curInput++;
            }
            else if (curInput == 0)
            {
                // First input; move to next input
                curInput++;
                ((NumberInput *)items[curInput])->curDigit = ((NumberInput *)items[curInput])->numDigits-1;
                ((NumberInput *)items[curInput])->active = true;
            }
        }
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
        ((NumberInput *)items[curInput])->curDigit = ((NumberInput *)items[curInput])->numDigits-1;
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
        if (curInput == numItems - 1)
        {
            // Last input - move to OK
            curInput++;
        }
        else if (curInput == 0)
        {
            // First input - move to next input
            curInput++;
            ((NumberInput *)items[curInput])->active = true;
            ((NumberInput *)items[curInput])->curDigit = 0;
        }
        onDisplay();
    }
    else if (curInput == numItems)
    {
        // @ OK; Save values
        for (uint8_t i = 0; i < numItems; i++)
        {
            ((NumberInput *)items[i])->setValue();
        }

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
        }

        // Save value and pop us off the menu
        menuManager.pop();
        // display the currnet top of the queue
        menuManager.display();
    }
}