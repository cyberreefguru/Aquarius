/*
 * Event.h
 *
 *  Created on: Nov 26, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

enum class Command
{
    ACTIVATE,
    DEACTIVATE,
    STATUS,
    SET,
    GET,
    LOG,
    NONE,
} ;
inline constexpr unsigned operator+ (Command const val) { return static_cast<unsigned>(val); }

class CommandEvent
{
public:
    CommandEvent();

    Command getType();
    void setType(Command t);
    uint8_t getSourceId();
    void setSourceId(uint8_t id);
    String getParameters();
    void setParameters(String msg);
    uint32_t getEventTime();
    void setEventTime(uint32_t time);
    
protected:
    uint32_t time = 0;
    Command type = Command::NONE;
    uint8_t sourceId = 0;
    uint8_t targetId = 0;
    String params;
};