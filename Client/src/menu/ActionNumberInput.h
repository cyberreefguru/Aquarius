/*
 * ActionNumberInput.h
 *
 *  Created on: Jan 8, 2024
 *      Author: cyberreefguru
 */
/**
 * @file ActionNumberInput.h
 * @brief Allows user to input a number using buttons. Requires onAction to be called to set value.
*/

#ifndef ActionNumberInput_H
#define ActionNumberInput_H

#include <Arduino.h>
#include <ArduinoLog.h>

#include "ActionMenuItem.h"


class ActionNumberInput : public ActionMenuItem
{
public:
    ActionNumberInput() {}
    ActionNumberInput(menu_label_t label, menu_title_t title, menu_prompt_t prompt, uint32_t *value, uint8_t numDigits, uint8_t decimal=0);
    ~ActionNumberInput();

    void initializeValue();
    void setValue();

    void onDisplay(bool active) override;
    void onAction() override;
    void onButtonUp() override;
    void onButtonDown() override;
    void onButtonLeft() override;
    void onButtonRight() override;
    void onButtonPush() override;

    uint32_t *value;
    uint8_t curDigit;
    uint8_t numDigits;
    uint8_t decimal;
    uint8_t *inputBuff = nullptr;
};

#endif