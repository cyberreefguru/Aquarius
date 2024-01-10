/*
 * NumberInputItem.cpp
 *
 *  Created on: Dec 31, 2023
 *      Author: cyberreefguru
 */
#include "NumberInputItem.h"

// NumberInputItem::NumberInputItem(menu_label_t label, menu_title_t title, uint32_t *value, uint8_t numDigits)
// {
//     // NumberInputItem(label, title, "> ", value, numDigits);
//     this->menuTitle = title;
//     this->menuLabel = label;
//     this->menuPrompt = "> ";

//     this->item = new NumberInput(title, value,  numDigits);
//     this->items = {(MenuItem**)&item};
//     this->numItems = 1;
//     this->curInput = 0;

// }

NumberInputItem::NumberInputItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt, uint32_t *value, uint8_t numDigits)
{
    this->menuTitle = title;
    this->menuLabel = label;
    this->menuPrompt = prompt;

    this->item = new NumberInput(label, title, prompt, value, numDigits);
    this->items = {(MenuItem **)&item};
    this->numItems = 1;
    this->curInput = 0;
    this->item->active =true;
}

NumberInputItem::~NumberInputItem()
{
    free(item);
    free(items);
}

void NumberInputItem::onDisplay()
{
    Log.traceln("NumberInputItem::onDisplay - BEGIN");
    displayManager.clear();
    displayManager.setCursor(0, 0);
    displayManager.println(menuTitle);
    items[0]->onDisplay();
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

void NumberInputItem::onButtonUp()
{
    Log.traceln("NumberInputItem::onButtonUp: curInput=%d", curInput);
    if (curInput == 0)
    {
        // @ Input
        ((NumberInput *)items[curInput])->active = true; // make sure it's active
        ((NumberInput *)items[curInput])->onButtonUp();  // call input up
    }
    else if (curInput == 1)
    {
        // @ OK; move to input
        curInput = 0; // move to input
        ((NumberInput *)items[curInput])->active = true;
        //((NumberInput *)items[curInput])->curDigit = 0;
    }
    else if (curInput == 2)
    {
        // @ Cancel; move to input
        curInput = 0; // move to input
        ((NumberInput *)items[curInput])->active = true;
        //((NumberInput *)items[curInput])->curDigit = 0;
    }
    onDisplay();
}

void NumberInputItem::onButtonDown()
{
    Log.traceln("NumberInputItem::onButtonDown: curInput=%d", curInput);
    if (curInput == 0)
    {
        // @ Input
        ((NumberInput *)items[curInput])->active = true;  // make sure it's active
        ((NumberInput *)items[curInput])->onButtonDown(); // call input down
    }
    else if (curInput == 1)
    {
        // @ OK; move to input
        curInput = 0; // move to input
        ((NumberInput *)items[curInput])->active = true;
    }
    else if (curInput == 2)
    {
        // @ Cancel; move to input
        curInput = 0; // move to input
        ((NumberInput *)items[curInput])->active = true;
    }
    onDisplay();
}

void NumberInputItem::onButtonLeft()
{
    Log.traceln("NumberInputItem::onButtonLeft: curInput=%d", curInput);

    if (curInput == 0)
    {
        // @ Input; Send event to input item
        ((NumberInput *)items[curInput])->onButtonLeft();
    }
    else if (curInput == 1)
    {
        // @ OK; move to last input item
        curInput = 0;
        ((NumberInput *)items[curInput])->active = true;
    }
    else if (curInput == 2)
    {
        // @ Cancel; Move to OK
        curInput--;
    }
    onDisplay();
}

void NumberInputItem::onButtonRight()
{
    Log.traceln("NumberInputItem::onButtonRight: curInput=%d", curInput);

    if (curInput == 0)
    {
        // @ Input; Send event to input item
        ((NumberInput *)items[curInput])->onButtonRight();
    }
    else if (curInput == 1)
    {
        // @ OK; move to cancel
        curInput++; // Move to canel
    }
    else if (curInput == 2)
    {
        // @ Cancel; move to first item
        curInput = 0;
        ((NumberInput *)items[curInput])->active = true;
        ((NumberInput *)items[curInput])->curDigit = ((NumberInput *)items[curInput])->numDigits - 1;
    }
    onDisplay();
}

void NumberInputItem::onButtonPush()
{
    Log.traceln("NumberInputItem::onButtonPush: curInput=%d", curInput);

    if (curInput == 0)
    {
        // @ Input
        ((NumberInput *)items[curInput])->onButtonPush();
        curInput=1; // Advance to OK
        onDisplay();
    }
    else if (curInput == 1)
    {
        // @ OK; Save values
        curInput = 0;
        ((NumberInput *)items[curInput])->setValue();
        ((NumberInput *)items[curInput])->active = true;

        // Save value and pop us off the menu
        menuManager.pop();
        // display the currnet top of the queue
        menuManager.display();
    }
    else if (curInput == 2)
    {
        // @ Cancel; reset input value to original
        curInput = 0;
        ((NumberInput *)items[curInput])->initializeValue();
        ((NumberInput *)items[curInput])->active = true;

        // Save value and pop us off the menu
        menuManager.pop();
        // display the currnet top of the queue
        menuManager.display();
    }
}