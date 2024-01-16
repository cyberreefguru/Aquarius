/*
 * NumberInput.h
 *
 *  Created on: Jan 8, 2024
 *      Author: cyberreefguru
 */
#ifndef NumberInput_H
#define NumberInput_H

#include <Arduino.h>
#include <ArduinoLog.h>

#include "MenuItem.h"

class NumberInput : public MenuItem
{
public:
    NumberInput() {}
    NumberInput(menu_label_t label, menu_title_t title, menu_prompt_t prompt, uint32_t *value, uint8_t numDigits, uint8_t decimal=0);
    ~NumberInput();

    void initializeValue();
    void setValue();

    void onDisplay(bool active) override;
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