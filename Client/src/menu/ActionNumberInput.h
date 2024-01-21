/**
 * @file ActionNumberInput.h
 * @brief Allows user to input a number using buttons. Requires onAction to be called to set value.
 * @date Jan 8, 2024
 * @author cyberreefguru
 */
#ifndef ActionNumberInput_H
#define ActionNumberInput_H

#include <Arduino.h>
#include <ArduinoLog.h>

#include "MenuItem.h"


class ActionNumberInput : public MenuItem
{
public:
    ActionNumberInput() {}
    ActionNumberInput(menu_prompt_t prompt, ActionCallback onAction, uint8_t numDigits, uint8_t decimal=0);
    ~ActionNumberInput();

    void setValue(uint32_t v);
    uint32_t getValue();

    void onDisplay(bool active) override;
    //void onAction() override;
    void onButtonUp() override;
    void onButtonDown() override;
    void onButtonLeft() override;
    void onButtonRight() override;
    void onButtonPush() override;

    bool increment(int8_t amount=1);
    bool nextDigit();
    bool previousDigit();
    // void setMsb();
    // void setLsb();

protected:
    uint8_t curDigit;
    uint8_t numDigits;
    uint8_t decimal;
    uint8_t *inputBuff = nullptr;
};

#endif