/*
 * ActionEvent.h
 *
 *  Created on: Nov 26, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <ArduinoJson.h>

#define CMD_MAX_PARAM_SIZE  128
#define CMD_MAX_SIZE        128+CMD_MAX_PARAM_SIZE

enum class CommandType
{
    ACTION=0,
    RESPONSE,
    LOG,
    NONE,
} ;
inline constexpr unsigned operator+ (CommandType const val) { return static_cast<unsigned>(val); }
inline const char* operator++(CommandType c)
{
    switch (c)
    {
    case CommandType::ACTION:
        return "ACTION";
        break;
    case CommandType::RESPONSE:
        return "RESPONSE";
        break;
    case CommandType::LOG:
        return "LOG";
        break;
    default:
        return "UNkNOWN";
        break;
    }
}

enum class ActionType
{
    ACTIVATE=0,
    DEACTIVATE,
    GET_STATUS,
    GET_PARAM,
    SET_PARAM,
    REGISTER,
    NONE,
} ;
inline constexpr unsigned operator+ (ActionType const val) { return static_cast<unsigned>(val); }
inline const char* operator++(ActionType a)
{
    switch (a)
    {
    case ActionType::ACTIVATE:
        return "ACTIVATE";
        break;
    case ActionType::DEACTIVATE:
        return "DEACTIVATE";
        break;
    case ActionType::GET_PARAM:
        return "GET_PARAM";
        break;
    case ActionType::SET_PARAM:
        return "SET_PARAM";
        break;
    case ActionType::GET_STATUS:
        return "GET_STATUS";
        break;
    case ActionType::REGISTER:
        return "REGISTER";
        break;
    default:
        return "UNkNOWN";
        break;
    }
}



enum class Status
{
    OK,
    ERROR,
};
inline constexpr unsigned operator+ (Status const val) { return static_cast<unsigned>(val); }
inline const char* operator++(Status a)
{
    switch (a)
    {
    case Status::OK:
        return "OK";
        break;
    case Status::ERROR:
        return "ERROR";
        break;
    default:
        return "UNkNOWN";
        break;
    }
}

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
inline const char* operator++(LogLevel a)
{
    switch (a)
    {
    case LogLevel::TRACE:
        return "TRACE";
        break;
    case LogLevel::DEBUG:
        return "DEBUG";
        break;
    case LogLevel::INFO:
        return "INFO";
        break;
    case LogLevel::WARN:
        return "WARN";
        break;
    case LogLevel::ERROR:
        return "ERROR";
        break;
    case LogLevel::FATAL:
        return "FATAL";
        break;
    default:
        return "UNkNOWN";
        break;
    }
}

// {\"cmd\": 2, \"k\": \"test key\", \"v\": \"test value\",\"t\": \"test string\"}

#define KEY_CMD_TYPE            "t"
#define KEY_CMD_ACTION          "a"
#define KEY_CMD_SOURCE_ID       "si"
#define KEY_CMD_TARGET_ID       "ti"
#define KEY_CMD_PARAMS          "p"
#define KEY_CMD_TIME            "ti"
#define KEY_CMD_DELAY           "d"
#define KEY_CMD_COLOR_INIT      "ci"
#define KEY_CMD_COLOR_CONN      "cc"
#define KEY_CMD_COLOR_WAIT      "cw"
#define KEY_CMD_COLOR_PROC      "cp"
#define KEY_CMD_COLOR_ACTIVE    "ca"
#define KEY_CMD_COLOR_DEACTIVE  "cd"
#define KEY_CMD_COLOR_WIFI_DOWN "wd"
#define KEY_CMD_COLOR_WIFI_UP   "wu"
#define KEY_CMD_COLOR_MQTT_DOWN "md"
#define KEY_CMD_COLOR_MQTT_UP   "mu"
#define KEY_CMD_COLOR_ERROR     "e"

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
    const JsonDocument& getParameters();
    void setParameters(char *s);
    uint32_t getDelay();
    void setDelay(uint32_t delay);
    uint32_t getTime();
    void setTime(uint32_t time);
    uint32_t fromJson(char* buffer); // turn into char[]
    const JsonDocument& toJson(char* buff); // turn into jsondocument
    
private:
    StaticJsonDocument<CMD_MAX_PARAM_SIZE> parameters;
    StaticJsonDocument<CMD_MAX_SIZE> jsonDocument;
    // CommandType type = CommandType::NONE;
    // ActionType action = ActionType::NONE;
    // uint8_t sourceId = 0;
    // uint8_t targetId = 0;
    // uint32_t time = 0;

};