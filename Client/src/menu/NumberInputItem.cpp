/*
 * NumberInputItem.cpp
 *
 *  Created on: Dec 31, 2023
 *      Author: cyberreefguru
 */
#include "NumberInputItem.h"

NumberInputItem::NumberInputItem(const char *title, const char *label)
{
    this->title = title;
    this->label = label;
    this->value = value;
    this->items = nullptr;
    this->numItems = 0;
    this->numDigits = 0;
    this->curDigit = 0;
}

NumberInputItem::~NumberInputItem()
{
    free(inputBuff);
}

void NumberInputItem::initialize(uint32_t *value, uint8_t numDigits)
{
    if (value != 0)
    {
        this->value = value;
        this->numDigits = numDigits;
        this->inputBuff = new uint8_t[numDigits];

        for (uint8_t i = 0; i < numDigits; i++)
        {
            uint8_t base = 1;
            this->inputBuff[i] = (*value / base) % 10;
            base *= 10;
        }

        Log.traceln("NumberInputItem::initialize - value=%i, d[1]=%d, d[0]=%d", *value, inputBuff[1], inputBuff[0]);
    }
}

void NumberInputItem::onEvent(ButtonEvent be)
{
    uint32_t v = 0;
    uint8_t base = 1;
    Log.traceln("NumberInputItem.onEvent - %s", ++be);
    Log.traceln("NumberInputItem.onEvent - curDigit=%d, numDigits=%d", curDigit, numDigits);
    Log.traceln("NumberInputItem.onEvent - value=%i, d[1]=%d, d[0]=%d", *value, inputBuff[1], inputBuff[0]);

    switch (be)
    {
    case ButtonEvent::PUSH:
        // Set value based on input
        for (uint8_t i = 0; i < numDigits; i++)
        {
            v += inputBuff[i]*base;
            base *= 10;
        }
        *value = v;
        Log.traceln("NumberInputItem.onEvent - value=%i, d[1]=%d, d[0]=%d", *value, inputBuff[1], inputBuff[0]);

        // Save value and pop us off the menu
        menuManager.pop();
        // display the currnet top of the queue
        menuManager.display();
        return;
        break;
    case ButtonEvent::LEFT:
        if (curDigit == (numDigits - 1))
        {
            curDigit = 0;
        }
        else
        {
            curDigit = curDigit + 1;
        }
        break;
    case ButtonEvent::RIGHT:
        if (curDigit == 0)
        {
            curDigit = numDigits - 1;
        }
        else
        {
            curDigit = curDigit - 1;
        }
        break;
    case ButtonEvent::DOWN:
        if (inputBuff[curDigit] == 0)
        {
            inputBuff[curDigit] = 9;
        }
        else
        {
            inputBuff[curDigit] = (inputBuff[curDigit] - 1);
        }
        break;
    case ButtonEvent::UP:
        if (inputBuff[curDigit] == 9)
        {
            inputBuff[curDigit] = 0;
        }
        else
        {
            inputBuff[curDigit] = (inputBuff[curDigit] + 1);
        }
        break;
    }
    Log.traceln("NumberInputItem.onEvent - curDigit=%d, numDigits=%d", curDigit, numDigits);
    Log.traceln("NumberInputItem.onEvent - value=%i, d[1]=%d, d[0]=%d", *value, inputBuff[1], inputBuff[0]);

    onDisplay();

    Log.traceln("NumberInputItem.onEvent - END");
}

void NumberInputItem::onDisplay()
{
    Log.traceln("NumberInputItem::onDisplay - BEGIN");
    if (label != nullptr)
    {
        displayManager.clear();
        displayManager.setCursor(0, 0);
        displayManager.println(title);
        displayManager.print("> ");
        for (uint8_t i = 0; i < numDigits; i++)
        {
            uint8_t index = (numDigits - 1) - i;

            Log.traceln("NumberInputItem::onDisplay: digit=%d", index);
            if (index == curDigit)
            {
                displayManager.setTextColor(BLACK, WHITE);
            }
            else
            {
                displayManager.setTextColor(WHITE);
            }
            displayManager.print(inputBuff[index]);
            displayManager.setTextColor(WHITE);
        }
        displayManager.setRefresh(true);
    }
    else
    {
        Log.errorln("Menu Item has no label!");
    }
    Log.traceln("NumberInputItem::onDisplay - END");
}
