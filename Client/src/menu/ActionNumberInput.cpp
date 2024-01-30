/**
 * @brief Widget that allows the user to enter a number using buttons.
 * @note widget does not print title - it only renders the number input areas;
 *       must be encapsulated in a menu item for proper use.
 * @file ActionNumberInput.cpp
 * @date Jan 8, 2024
 * @author cyberreefguru
 */
#include "ActionNumberInput.h"
#include "DisplayManager.h"

/**
 * @brief constructor
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

/**
 * @brief destructor
 */
ActionNumberInput::~ActionNumberInput()
{
    free(inputBuff);
}

/**
 * @brief Displays the number input item; renders prompt and then 'numdigits' of input area
 * @param active
 */
void ActionNumberInput::onDisplay(bool active)
{
    // Log.traceln("ActionNumberInput::onDisplay - BEGIN");

    // Call user provided callback if it exits
    if (doDisplay != nullptr)
    {
        doDisplay(active);
    }
    {
        // No callback, render item
        if (menuPrompt == nullptr)
        {
            Log.errorln("ActionNumberInput::onDisplay - Item missing labels!");
            return;
        }

        displayManager.print(menuPrompt);
        for (uint8_t i = 0; i < numDigits; i++)
        {
            uint8_t index = (numDigits - 1) - i;
            // Log.traceln("ActionNumberInput::onDisplay: digit=%d, value=%d", index, inputBuff[index]);
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
            if ((decimal > 0) && (index == decimal))
            {
                displayManager.print(".");
            }
        }
    }
    // Log.traceln("ActionNumberInput::onDisplay - END");
}

/**
 * @brief responds to button up by increasing the input value by one; rolls over from 9 to 0
 */
void ActionNumberInput::onButtonUp()
{
    Log.traceln("ActionNumberInput::onButtonUp - BEGIN - %s > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
    if (doButtonUp != nullptr)
    {
        doButtonUp();
    }
    else
    {
        increment(1);
        // if (inputBuff[curDigit] == 9)
        // {
        //     inputBuff[curDigit] = 0;
        // }
        // else
        // {
        //     inputBuff[curDigit] = (inputBuff[curDigit] + 1);
        // }
    }
    Log.traceln("ActionNumberInput::onButtonUp - END - %s > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
}

/**
 * @brief responds to button down by decreasing the input value by one; rolls over from 0 to 9
 */
void ActionNumberInput::onButtonDown()
{
    Log.traceln("ActionNumberInput::onButtonDown - BEGIN - %s > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
    if (doButtonDown != nullptr)
    {
        doButtonDown();
    }
    else
    {
        increment(-1);
        // if (inputBuff[curDigit] == 0)
        // {
        //     inputBuff[curDigit] = 9;
        // }
        // else
        // {
        //     inputBuff[curDigit] = (inputBuff[curDigit] - 1);
        // }
    }
    Log.traceln("ActionNumberInput::onButtonDown - END - %s > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
}

/**
 * @brief responds to button left by moving between digits; wraps as required
 */
void ActionNumberInput::onButtonLeft()
{
    Log.traceln("ActionNumberInput::onButtonLeft - BEGIN - '%s' > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
    if (doButtonLeft != nullptr)
    {
        doButtonLeft();
    }
    else
    {
        previousDigit();
        // if (curDigit == (numDigits - 1))
        // {
        //     curDigit = 0;
        // }
        // else
        // {
        //     curDigit++;
        // }
    }
    Log.traceln("ActionNumberInput::onButtonLeft - END - %s > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
}

/**
 * @brief responds to button right by moving between digits; wraps as required
 */
void ActionNumberInput::onButtonRight()
{
    Log.traceln("ActionNumberInput::onButtonRight - BEGIN - %s > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
    if (doButtonRight != nullptr)
    {
        doButtonRight();
    }
    else
    {
        nextDigit();
        // if (curDigit == 0)
        // {
        //     curDigit = numDigits - 1;
        // }
        // else
        // {
        //     curDigit--;
        // }
    }
    Log.traceln("ActionNumberInput::onButtonRight - END - %s > curDigit=%d, v=%d", menuLabel, curDigit, inputBuff[curDigit]);
}

/**
 * @brief responds to button push; resets curDigit to 0.
 */
void ActionNumberInput::onButtonPush()
{
    Log.traceln("ActionNumberInput::onButtonPush - %s", menuLabel);
    if (doButtonPush != nullptr)
    {
        doButtonPush();
    }
    else
    {
        curDigit = 0;
    }
}

bool ActionNumberInput::increment(int8_t amount)
{
    bool b = false;
    int8_t i = (int8_t)inputBuff[curDigit] + amount;
    if (i > 9 || i < 0)
    {
        b = true;
    }
    i = i%10;
    if( i<0 )
    {
        i = 10 + i;
    }
    inputBuff[curDigit] = i;
    return b;
}

bool ActionNumberInput::nextDigit()
{
    bool b = false;
    if (curDigit == 0)
    {
        curDigit = numDigits - 1;
        b = true;
    }
    else
    {
        curDigit--;
    }
    return b;
}

bool ActionNumberInput::previousDigit()
{
    bool b = false;
    if (curDigit == (numDigits - 1))
    {
        curDigit = 0;
        b = true;
    }
    else
    {
        curDigit++;
    }
    return b;
}

// void ActionNumberInput::setMsb()
// {
//     curDigit = numDigits-1;
// }
// void ActionNumberInput::setLsb()
// {
//     curDigit = 0;
// }


/**
 * @brief returns value represented by inputs
 * @note returns INTEGER value; decimal is not acknowledged
 * @return integer value represented by inputs
 */
uint32_t ActionNumberInput::getValue()
{
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

/**
 * @brief Sets the value of the inputs to the specified number
 * @note does NOT observe decimal point
 * @param v number to initialize inputs to
 */
void ActionNumberInput::setValue(uint32_t v)
{
    Log.traceln("ActionNumberInput::setValue - value=%d", v);
    uint8_t base = 1;
    for (uint8_t i = 0; i < numDigits; i++)
    {
        this->inputBuff[i] = (v / base) % 10;
        // Log.traceln("ActionNumberInput::initializeValue - i=%d, v=%d, b=%d. ib=%d", i, *value, base, inputBuff[i]);
        base *= 10;
    }
}