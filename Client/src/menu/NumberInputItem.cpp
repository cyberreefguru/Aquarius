/*
 * ExitMenuItem.h
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */

#include "MenuManager.h"

NumberInputItem::NumberInputItem(const char* title, uint8_t numChars)
{
    Log.traceln("NumberInputItem: BEGIN");
    this->title = title;
    this->items = nullptr;
    this->numItems = 0;
    this->numDigits = numDigits;
    this->curDigit = numDigits-1;
    this->inputBuff = new uint8_t[numDigits];
    memset(inputBuff, 0, numDigits);

    Log.traceln("NumberInputItem: BEGIN");
}

NumberInputItem::~NumberInputItem()
{
    free(inputBuff);
}

void NumberInputItem::onEvent(ButtonEvent be)
{
    Log.traceln("NumberInputItem.onEvent: BEGIN");
    Log.traceln("NumberInputItem.onEvent: curDigit=%d, numDigits=%d", curDigit, numDigits);

    switch(be)
    
    {
        case ButtonEvent::PUSH:
            // Save value and return
            break;
        case ButtonEvent::LEFT:
            curDigit = (curDigit-1)%numDigits;
            break;
        case ButtonEvent::RIGHT:
            curDigit = (curDigit+1)%numDigits;
            break;
        case ButtonEvent::DOWN:
            inputBuff[curDigit] = (inputBuff[curDigit]++)%9;
            break;
        case ButtonEvent::UP:
            inputBuff[curDigit] = (inputBuff[curDigit]--)%9;
            break;
    }
    displayManager.setRefresh(true);

    Log.traceln("NumberInputItem.onEvent: END");

}

void NumberInputItem::onDisplay()
{
    Log.traceln("NumberInputItem::onDisplay: BEGIN");
    if (title != nullptr)
    {
        displayManager.clear();
        displayManager.setCursor(0, 0);

        displayManager.println(title);
        displayManager.print("> ");
        for(uint8_t i=0; i<numDigits; i++)
        {
            uint8_t index = (numDigits-1) - i;

            Log.traceln("NumberInputItem::onDisplay: digit=%d", index);
            if( index == curDigit )
            {
                displayManager.setTextColor(BLACK, WHITE);
            }
            else
            {
                displayManager.setTextColor(WHITE);
            }
            displayManager.print( inputBuff[index]);
            displayManager.setTextColor(WHITE);
        }
        displayManager.setRefresh(true);
    }
    else
    {
        Log.errorln("Menu Item has no title!");
    }
    Log.traceln("NumberInputItem::onDisplay: END");
}
