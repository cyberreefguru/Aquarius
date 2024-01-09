/*
 * MultiNumberInputItem.h
 *
 *  Created on: Jan 8, 2024
 *      Author: cyberreefguru
 */
#ifndef MultiNumberInputItem_H
#define MultiNumberInputItem_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "NumberInput.h"
#include "MenuManager.h"


class MultiNumberInputItem : public MenuItem
{
public:
    MultiNumberInputItem(){}
    MultiNumberInputItem(const char *title, const char *label, MenuItem **items, uint8_t numItems);
    virtual ~MultiNumberInputItem();

    virtual void onDisplay() override;
    virtual void onButtonUp() override;
    virtual void onButtonDown() override;
    virtual void onButtonLeft() override;
    virtual void onButtonRight() override;
    virtual void onButtonPush() override;

protected:
    // NumberInput *inputs;
    uint8_t curInput = 0;
};

#endif