/**
 * @file ActionNumberInput.cpp
 *
 *  @date Jan 8, 2024
 *  @author cyberreefguru
 */
#include "ActionNumberInput.h"
#include "DisplayManager.h"

ActionNumberInput::ActionNumberInput(menu_label_t label, menu_title_t title, menu_prompt_t prompt, uint32_t *value, uint8_t numDigits, uint8_t decimal)
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

ActionNumberInput::~ActionNumberInput()
{
    free(inputBuff);
}

void ActionNumberInput::onAction()
{
    setValue();
}

void ActionNumberInput::onDisplay(bool active)
{
    Log.traceln("ActionNumberInput::onDisplay - BEGIN");

    if (menuLabel == nullptr || menuPrompt == nullptr)
    {
        Log.errorln("ActionNumberInput::onDisplay - Item missing labels!");
        return;
    }

    Log.traceln("ActionNumberInput::onDisplay - %s > value=%d", menuLabel, *value);

    displayManager.print(menuPrompt);
    for (uint8_t i = 0; i < numDigits; i++)
    {
        uint8_t index = (numDigits - 1) - i;
        // Log.traceln("ActionNumberInput::onDisplay: digit=%d, value=%d", index, inputBuff[index]);
        if (decimal > 0 && i == decimal)
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
    // displayManager.println();

    Log.traceln("ActionNumberInput::onDisplay - END");
}

void ActionNumberInput::onButtonUp()
{
    Log.traceln("ActionNumberInput::onButtonUp - %s > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
    if (inputBuff[curDigit] == 9)
    {
        inputBuff[curDigit] = 0;
    }
    else
    {
        inputBuff[curDigit] = (inputBuff[curDigit] + 1);
    }
    Log.traceln("ActionNumberInput::onButtonUp - %s > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
    onDisplay(false);
}

void ActionNumberInput::onButtonDown()
{
    Log.traceln("ActionNumberInput::onButtonDown - %s > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
    if (inputBuff[curDigit] == 0)
    {
        inputBuff[curDigit] = 9;
    }
    else
    {
        inputBuff[curDigit] = (inputBuff[curDigit] - 1);
    }
    Log.traceln("ActionNumberInput::onButtonDown - %s > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
    onDisplay(false);
}

void ActionNumberInput::onButtonLeft()
{
    Log.traceln("ActionNumberInput::onButtonLeft - %s > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
    if (curDigit == (numDigits - 1))
    {
        curDigit = 0;
        // active = false;
    }
    else
    {
        curDigit++;
    }
    Log.traceln("ActionNumberInput::onButtonLeft - %s > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
    onDisplay(false);
    // return b;
}

void ActionNumberInput::onButtonRight()
{
    Log.traceln("ActionNumberInput::onButtonRight - %s > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
    if (curDigit == 0)
    {
        curDigit = numDigits - 1;
        // active = false;
    }
    else
    {
        curDigit--;
    }
    Log.traceln("ActionNumberInput::onButtonRight - %s > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
    onDisplay(false);
    // return b;
}

void ActionNumberInput::onButtonPush()
{
    // active = false;
    curDigit = 0;
}

void ActionNumberInput::setValue()
{
    Log.traceln("ActionNumberInput::setValue - current value - %d", *value);

    uint32_t v = 0;
    uint8_t base = 1;
    // Set value based on input
    for (uint8_t i = 0; i < numDigits; i++)
    {
        v += inputBuff[i] * base;
        base *= 10;
    }
    *value = v;
    Log.traceln("ActionNumberInput::setValue - new value - %d", *value);
}

void ActionNumberInput::initializeValue()
{
    Log.traceln("ActionNumberInput::initializeValue - current value - %d", *value);
    uint8_t base = 1;
    for (uint8_t i = 0; i < numDigits; i++)
    {
        this->inputBuff[i] = (*value / base) % 10;
        // Log.traceln("ActionNumberInput::initializeValue - i=%d, v=%d, b=%d. ib=%d", i, *value, base, inputBuff[i]);
        base *= 10;
    }
    Log.traceln("ActionNumberInput::initializeValue - new value - %d", *value);
}