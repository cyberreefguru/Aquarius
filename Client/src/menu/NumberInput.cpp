/*
 * NumberInput.cpp
 *
 *  Created on: Jan 8, 2024
 *      Author: cyberreefguru
 */
#include "NumberInput.h"
#include "DisplayManager.h"

NumberInput::NumberInput(menu_label_t label, menu_title_t title, menu_prompt_t prompt, uint32_t *value, uint8_t numDigits, uint8_t decimal)
{
    this->menuLabel = label;
    this->menuTitle = title;
    this->menuPrompt = prompt;

    this->value = value;
    this->numDigits = numDigits;
    this->curDigit = 0;
    this->decimal = decimal;
    this->inputBuff = (uint8_t *)new uint8_t[numDigits];
    initializeValue();
}

NumberInput::~NumberInput()
{
    free(inputBuff);
}

void NumberInput::onDisplay(bool active)
{
    Log.traceln("NumberInput::onDisplay - BEGIN");

    if (menuPrompt == nullptr)
    {
        Log.errorln("NumberInput::onDisplay - Item missing labels!");
        return;
    }

    Log.traceln("NumberInput::onDisplay: value=%d", *value);

    displayManager.print(menuPrompt);
    for (uint8_t i = 0; i < numDigits; i++)
    {
        uint8_t index = (numDigits - 1) - i;
        Log.traceln("NumberInput::onDisplay: digit=%d, value=%d", index, inputBuff[index]);
        if( decimal > 0 && i == decimal)
        {
            displayManager.print(".");
        }
        if (index == curDigit && active)
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
    displayManager.println();

    Log.traceln("NumberInput::onDisplay - END");
}

void NumberInput::onButtonUp()
{
    Log.traceln("NumberInput::onButtonUp - curDigit=%d, v=%d", curDigit, inputBuff[curDigit]);
    if (inputBuff[curDigit] == 9)
    {
        inputBuff[curDigit] = 0;
    }
    else
    {
        inputBuff[curDigit] = (inputBuff[curDigit] + 1);
    }
    Log.traceln("NumberInput::onButtonUp - curDigit=%d, v=%d", curDigit, inputBuff[curDigit]);
    onDisplay(false);
}

void NumberInput::onButtonDown()
{
    Log.traceln("NumberInput::onButtonDown - curDigit=%d, v=%d", curDigit, inputBuff[curDigit]);
    if (inputBuff[curDigit] == 0)
    {
        inputBuff[curDigit] = 9;
    }
    else
    {
        inputBuff[curDigit] = (inputBuff[curDigit] - 1);
    }
    Log.traceln("NumberInput::onButtonDown - curDigit=%d, v=%d", curDigit, inputBuff[curDigit]);
    onDisplay(false);
}

void NumberInput::onButtonLeft()
{
    Log.traceln("NumberInput::onButtonLeft - curDigit=%d, v=%d", curDigit, inputBuff[curDigit]);
    if (curDigit == (numDigits - 1))
    {
        curDigit = 0;
        // active = false;
    }
    else
    {
        curDigit++;
    }
    Log.traceln("NumberInput::onButtonLeft - curDigit=%d, v=%d", curDigit, inputBuff[curDigit]);
    onDisplay(false);
    // return b;
}

void NumberInput::onButtonRight()
{
    Log.traceln("NumberInput::onButtonRight - curDigit=%d, v=%d", curDigit, inputBuff[curDigit]);
    if (curDigit == 0)
    {
        curDigit = numDigits-1;
        // active = false;
    }
    else
    {
        curDigit--;
    }
    Log.traceln("NumberInput::onButtonRight - curDigit=%d, v=%d", curDigit, inputBuff[curDigit]);
    onDisplay(false);
    // return b;
}

void NumberInput::onButtonPush()
{
    // active = false;
    curDigit = 0;
}

void NumberInput::setValue()
{
    uint32_t v = 0;
    uint8_t base = 1;
    // Set value based on input
    for (uint8_t i = 0; i < numDigits; i++)
    {
        v += inputBuff[i] * base;
        base *= 10;
    }
    *value = v;
    // Log.traceln("NumberInput::setValue - %d", *value);
}

void NumberInput::initializeValue()
{
    // Log.traceln("NumberInput::initializeValue - %d", *value);
    uint8_t base = 1;
    for (uint8_t i = 0; i < numDigits; i++)
    {
        this->inputBuff[i] = (*value / base) % 10;
        // Log.traceln("NumberInput::initializeValue - i=%d, v=%d, b=%d. ib=%d", i, *value, base, inputBuff[i]);

        base *= 10;
    }
}