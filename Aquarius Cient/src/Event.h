/*
 * Event.h
 *
 *  Created on: Nov 26, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

enum class State
{
    ACTIVE,
    DEACTIVE,
    WIFI_DOWN,
    WIFI_UP,
    MQTT_DOWN,
    MQTT_UP,
    INITIALIZING,
    WAITING,
    RECEIVING,
    PROCESSING,
    SENDING,
    RECEIVED,
    SENT,
    ERROR
};
inline constexpr unsigned operator+ (State const val) { return static_cast<unsigned>(val); }

enum class EventType
{
    COMMAND,
    RESPONSE,
    STATUS,
    REGISTER,
    LOG,
    NONE,
} ;
inline constexpr unsigned operator+ (EventType const val) { return static_cast<unsigned>(val); }

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

class Event
{
public:
    Event();
    Event(EventType type, uint8_t sourcdId, String msg);

    EventType getEventType();
    void setEventType(EventType t);
    uint8_t getSourceId();
    void setSourceId(uint8_t id);
    String getMessage();
    void setMessage(String msg);
    uint32_t getEventTime();
    void setEventTime(uint32_t time);
    
protected:
    uint32_t time = 0;
    EventType type = EventType::NONE;
    uint8_t sourceId = 0;
    String msg;
};