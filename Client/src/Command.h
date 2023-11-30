/*
 * Event.h
 *
 *  Created on: Nov 26, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

enum class CommandType
{
    ACTION,
    RESPONSE,
    LOG,
    NONE,
} ;
inline constexpr unsigned operator+ (CommandType const val) { return static_cast<unsigned>(val); }

enum class ActionType
{
    ACTIVATE,
    DEACTIVATE,
    GET_STATUS,
    GET_PARAM,
    SET_PARAM,
    REGISTER,
    NONE,
} ;
inline constexpr unsigned operator+ (ActionType const val) { return static_cast<unsigned>(val); }

enum class Status
{
    OK,
    ERROR,
};
inline constexpr unsigned operator+ (Status const val) { return static_cast<unsigned>(val); }

enum class LogLevel
{
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
};
inline constexpr unsigned operator+ (LogLevel const val) { return static_cast<unsigned>(val); }


class Command
{
public:
    Command();

    CommandType getType();
    void setType(CommandType t);
    ActionType getAction();
    void setAction(ActionType t);
    uint8_t getSourceId();
    void setSourceId(uint8_t id);
    uint8_t getTargetId();
    void setTargetId(uint8_t id);
    String getParameters();
    void setParameters(String s);
    uint32_t getTime();
    void setTime(uint32_t time);
    
protected:
    CommandType type = CommandType::NONE;
    ActionType action = ActionType::NONE;
    uint8_t sourceId = 0;
    uint8_t targetId = 0;
    String parameters = "";
    uint32_t time = 0;
};