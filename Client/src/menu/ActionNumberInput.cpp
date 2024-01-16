/**
 * @file ActionNumberInput.cpp
 *
 *  @date Jan 8, 2024
 *  @author cyberreefguru
 */
#include "ActionNumberInput.h"
#include "DisplayManager.h"

/**
 * @brief 
 * @param prompt 
 * @param doAction 
 * @param numDigits 
 * @param decimal 
 */
ActionNumberInput::ActionNumberInput(menu_prompt_t prompt, ActionCallback doAction, uint8_t numDigits, uint8_t decimal)
{
    this->menuLabel = prompt;
    this->menuTitle = prompt;
    this->menuPrompt = prompt;

    this->doAction = doAction;

    this->numDigits = numDigits;
    this->curDigit = 0;
    this->decimal = decimal;
    this->inputBuff = (uint8_t *)new uint8_t[numDigits];
}

ActionNumberInput::~ActionNumberInput()
{
    free(inputBuff);
}

// void ActionNumberInput::onAction()
// {
//     setValue();
// }

void ActionNumberInput::onDisplay(bool active)
{
    Log.traceln("ActionNumberInput::onDisplay - BEGIN");

    if (menuLabel == nullptr || menuPrompt == nullptr)
    {
        Log.errorln("ActionNumberInput::onDisplay - Item missing labels!");
        return;
    }

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

uint32_t ActionNumberInput::getValue()
{
    Log.traceln("ActionNumberInput::getValue - BEGIN");

    uint32_t v = 0;
    uint8_t base = 1;
    // Set value based on input
    for (uint8_t i = 0; i < numDigits; i++)
    {
        v += inputBuff[i] * base;
        base *= 10;
    }
    Log.traceln("ActionNumberInput::getValue - value - %d", v);

    return v;
}

void ActionNumberInput::setValue(uint32_t v)
{
    Log.traceln("ActionNumberInput::initializeValue - value=%d", v);
    uint8_t base = 1;
    for (uint8_t i = 0; i < numDigits; i++)
    {
        this->inputBuff[i] = (v / base) % 10;
        // Log.traceln("ActionNumberInput::initializeValue - i=%d, v=%d, b=%d. ib=%d", i, *value, base, inputBuff[i]);
        base *= 10;
    }
    Log.traceln("ActionNumberInput::initializeValue - END");
}