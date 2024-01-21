/**
 * @file TargetMenuItem.h
 * @brief Menu item that renders a target for editing
 * @date Jan 19, 2024
 * @author cyberreefguru
 */
#ifndef TargetMenuItem_H
#define TargetMenuItem_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "Target.h"
#include "MultiButtonItem.h"
#include "ActionNumberInput.h"
#include "ActionButtonItem.h"

using namespace std::placeholders;
#include <functional>
#include <utility>


class TargetMenuItem : public MultiButtonItem
{
public:
    TargetMenuItem(Target *target);
    virtual ~TargetMenuItem();

protected:
    virtual void initialize();
    void doNodeId();
    void doStartDelay();
    void doStopDelay();
    void doOk();
    void doCancel();
    void doDelete();
    // void doNumberLeft();
    // void doNumberRight();
    // void doButtonLeft();
    // void doButtonRight();

private:
    Target *target;
    ActionNumberInput *iNodeId = nullptr;
    ActionNumberInput *iStartDelay = nullptr;
    ActionNumberInput *iStopDelay = nullptr;
    ActionButtonItem *iOk = nullptr;
    ActionButtonItem *iCancel = nullptr;
    ActionButtonItem *iDelete = nullptr;
};

#endif