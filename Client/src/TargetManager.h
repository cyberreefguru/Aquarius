/*
 * TargetManager.h
 *
 *  Created on: Jan 17, 2024
 *      Author: cyberreefguru
 */
#ifndef TargetManager_H
#define TargetManager_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <ArduinoJson.h>

#include "Target.h"
#include "PreferenceManager.h"

class TargetManager
{
public:
    TargetManager();
    virtual ~TargetManager();

    void initialize();
    void addTarget(Target * target);
    void removeTarget(uint8_t targetIndex);
    Target** getTargets();


protected: 
    uint32_t toString(char *buff, uint32_t size); // turn into char[]
    bool fromString(char *buff); // turn into jsondocument

    // Target **targets = nullptr;
    // char targetsBuffer[TARGET_BUFF_SIZE];
    StaticJsonDocument<TARGET_BUFF_SIZE> targetJson;
    Target *targets = nullptr;
    uint8_t numTargets = 0;


};

// end of add your includes here
#ifdef __cplusplus
    extern "C"
    {
#endif

    extern TargetManager targetManager;

#ifdef __cplusplus
} // extern "C"
#endif

#endif