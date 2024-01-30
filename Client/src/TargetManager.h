/**
 * @brief Manages all targets
 * @file TargetManager.h
 * @date Jan 17, 2024
 * @author cyberreefguru
 */
#ifndef TargetManager_H
#define TargetManager_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <ArduinoJson.h>

#include "ArrayList.h"
#include "Target.h"

#include "PreferenceManager.h"


class TargetManager
{
public:
    TargetManager();
    virtual ~TargetManager();

    void initialize();
    void add(Target * target);
    void remove(uint8_t targetIndex);
    void remove(Target *target);
    Target* get(uint8_t index);
    ArrayList<Target*> *getTargetList();
    void save();
    uint8_t size();
    void dumpTargets(const char *label);

protected: 
    ArrayList<Target*> targetList;
    // uint8_t numTargets = 0;
    uint32_t toString(char *buff, uint32_t size); // turn into char[]
    bool fromString(char *buff); // turn into jsondocument

    StaticJsonDocument<TARGET_BUFF_SIZE> targetJson;
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