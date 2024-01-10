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

#include "NumberInput.h"

class NumberInputItem : public MenuItem
{
public:
    NumberInputItem(){}
    // NumberInputItem(menu_label_t label, menu_title_t title, uint32_t *value, uint8_t numDigits);
    NumberInputItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt, uint32_t *value, uint8_t numDigits);
    virtual ~NumberInputItem();

    virtual void onDisplay() override;
    virtual void onButtonUp() override;
    virtual void onButtonDown() override;
    virtual void onButtonLeft() override;
    virtual void onButtonRight() override;
    virtual void onButtonPush() override;

protected:
    NumberInput *item =nullptr;
    uint8_t curInput = 0;

};

#endif