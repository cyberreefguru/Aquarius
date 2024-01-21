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
#include "MultiActionItem.h"
#include "ActionNumberInput.h"

using namespace std::placeholders;
#include <functional>
#include <utility>


class TargetMenuItem : public MultiActionItem
{
public:
    TargetMenuItem(Target *target);
    virtual ~TargetMenuItem();

protected:
    void initialize() override;
    void doNodeId();
    void doStartDelay();
    void doStopDelay();
    void doDelete();

private:
    Target *target;
};

#endif