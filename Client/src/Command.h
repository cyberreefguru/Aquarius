/*
 * Event.h
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

// {\"cmd\": 2, \"k\": \"test key\", \"v\": \"test value\",\"t\": \"test string\"}

#define KEY_TYPE            "t"
#define KEY_ACTION          "a"
#define KEY_SOURCE_ID       "si"
#define KEY_TARGET_ID       "ti"
#define KEY_PARAMS          "p"
#define KEY_TIME            "ti"
#define KEY_DELAY           "d"
#define KEY_COLOR_INIT      "ci"
#define KEY_COLOR_CONN      "cc"
#define KEY_COLOR_WAIT      "cw"
#define KEY_COLOR_PROC      "cp"
#define KEY_COLOR_ACTIVE    "ca"
#define KEY_COLOR_DEACTIVE  "cd"
#define KEY_COLOR_WIFI_DOWN "wd"
#define KEY_COLOR_WIFI_UP   "wu"
#define KEY_COLOR_MQTT_DOWN "md"
#define KEY_COLOR_MQTT_UP   "mu"
#define KEY_COLOR_ERROR     "e"

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