/*
 * NumberInputItem.h
 *
 *  Created on: Jan 7, 2024
 *      Author: cyberreefguru
 */
#ifndef NumberInputItem_H
#define NumberInputItem_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

// #include "MenuItem.h"
#include "MenuManager.h"

enum class ActiveComponent
{
    INPUT_AREA=0,
    OK_BUTTON,
    CANCEL_BUTTON
};

inline constexpr unsigned operator+(ActiveComponent const val) { return static_cast<unsigned>(val); }
inline const char* operator++(ActiveComponent const val)
{
    switch (val)
    {
    case ActiveComponent::INPUT_AREA:
        return "INPUT";
        break;
    case ActiveComponent::OK_BUTTON:
        return "OK";
        break;
    case ActiveComponent::CANCEL_BUTTON:
        return "CANCEL";
        break;
    }
}

class NumberInputItem : public MenuItem
{
public:
    NumberInputItem(){}
    NumberInputItem(const char *title, const char *label);
    void initialize(uint32_t *value, uint8_t numChars = 2);
    virtual ~NumberInputItem();

    uint32_t getValue();
    void setValue();

    virtual void onDisplay() override;
    virtual void onButtonUp() override;
    virtual void onButtonDown() override;
    virtual void onButtonLeft() override;
    virtual void onButtonRight() override;
    virtual void onButtonPush() override;

protected:
    uint32_t *value;
    uint8_t numDigits = 2;
    uint8_t curDigit = numDigits - 1;
    byte *inputBuff = nullptr;
    ActiveComponent activeComponent = ActiveComponent::INPUT_AREA;
};

class BrightnessInputItem : public NumberInputItem
{
public:
    BrightnessInputItem(const char *title, const char *label);
    virtual void onButtonPush() override;


};

#endif