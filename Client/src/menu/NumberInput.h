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
#include "DisplayManager.h"

class NumberInput : public MenuItem
{
public:
    NumberInput() {}
    // NumberInput(menu_title_t title, uint32_t *value, uint8_t numDigits);
    NumberInput(menu_label_t label, menu_title_t title, menu_prompt_t prompt, uint32_t *value, uint8_t numDigits, uint8_t decimal=0);
    virtual ~NumberInput();

    void initializeValue();
    void setValue();

    virtual void onDisplay() override;
    virtual void onButtonUp() override;
    virtual void onButtonDown() override;
    virtual void onButtonLeft() override;
    virtual void onButtonRight() override;
    virtual void onButtonPush() override;

    uint32_t *value;
    uint8_t curDigit;
    uint8_t numDigits;
    uint8_t decimal;
    uint8_t *inputBuff = nullptr;
    bool active = false;
};

#endif