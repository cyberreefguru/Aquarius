/*
 * MultiNumberInput.cpp
 *
 *  Created on: Jan 8, 2024
 *      Author: cyberreefguru
 */
#include "NumberInput.h"

NumberInput::NumberInput(const char *title, uint32_t *value, uint8_t numDigits)
{
    this->title = title;
    this->label = title;
    this->value = value;
    this->numDigits = numDigits;
    this->curDigit = 0;
    this->inputBuff = (uint8_t *)new uint8_t[numDigits];
    initializeValue();
}

NumberInput::~NumberInput()
{
    free(inputBuff);
}

void NumberInput::onDisplay()
{
    Log.traceln("NumberInput::onDisplay - BEGIN");
    if (title == nullptr)
    {
        Log.errorln("NumberInput::onDisplay - title is null!");
        return;
    }

    Log.traceln("NumberInput::onDisplay: value=%d", *value);

    displayManager.print(title);
    for (uint8_t i = 0; i < numDigits; i++)
    {
        uint8_t index = (numDigits - 1) - i;
        Log.traceln("NumberInput::onDisplay: digit=%d, value=%d", index, inputBuff[index]);
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
    Log.traceln("NumberInput::onButtonUp - curDigit=%d, v=%d, a=%d", curDigit, inputBuff[curDigit], active);
    if(active)
    {
        if (inputBuff[curDigit] == 9)
        {
            inputBuff[curDigit] = 0;
        }
        else
        {
            inputBuff[curDigit] = (inputBuff[curDigit] + 1);
        }
    }
    Log.traceln("NumberInput::onButtonUp - curDigit=%d, v=%d, a=%d", curDigit, inputBuff[curDigit], active);
    onDisplay();
}

void NumberInput::onButtonDown()
{
    Log.traceln("NumberInput::onButtonDown - curDigit=%d, v=%d, a=%d", curDigit, inputBuff[curDigit], active);
    if( active )
    {
        if (inputBuff[curDigit] == 0)
        {
            inputBuff[curDigit] = 9;
        }
        else
        {
            inputBuff[curDigit] = (inputBuff[curDigit] - 1);
        }
    }
    Log.traceln("NumberInput::onButtonDown - curDigit=%d, v=%d, a=%d", curDigit, inputBuff[curDigit], active);
    onDisplay();
}

void NumberInput::onButtonLeft()
{
    Log.traceln("NumberInput::onButtonLeft - curDigit=%d, v=%d, a=%d", curDigit, inputBuff[curDigit], active);
   // bool b = false;
    if( active )
    {
        if (curDigit == (numDigits - 1))
        {
            curDigit = 0;
            active = false;
        }
        else
        {
            curDigit++;
        }

    }
    Log.traceln("NumberInput::onButtonLeft - curDigit=%d, v=%d, a=%d", curDigit, inputBuff[curDigit], active);
    onDisplay();
    // return b;
}

void NumberInput::onButtonRight()
{
    Log.traceln("NumberInput::onButtonRight - curDigit=%d, v=%d, a=%d", curDigit, inputBuff[curDigit], active);
    // bool b = false;
    if( active )
    {
        if (curDigit == 0)
        {
            active = false;
        }
        else
        {
            curDigit--;
        }
    }
    Log.traceln("NumberInput::onButtonRight - curDigit=%d, v=%d, a=%d", curDigit, inputBuff[curDigit], active);
    onDisplay();
    // return b;
}


void NumberInput::onButtonPush()
{
    active = false;
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