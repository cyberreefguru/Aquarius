/*
 * Target.h
 *
 *  Created on: Jan 12, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <ArduinoJson.h>

#define TARGET_MAX_SIZE 8

class Target
{
public:
    Target();
    virtual ~Target(){}
    
    uint8_t sourceNodeId = 0;
    uint8_t targetNodeId = 0;
    uint32_t startDelay = 0;
    uint32_t endDelay = 0;

    uint32_t fromJson(char* buffer); // turn into char[]
    const JsonDocument& toJson(char* buff); // turn into jsondocument
    StaticJsonDocument<TARGET_MAX_SIZE> json;

};