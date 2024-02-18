/*
 * ActionEvent.h
 *
 *  Created on: Nov 26, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

enum class ActionEvent
{
    ACTIVE=0,
    DEACTIVE,
    WIFI_DOWN,
    WIFI_UP,
    MQTT_DOWN,
    MQTT_UP,
    INITIALIZING,
    CONFIGURE,
    WAITING,
    MSG_RECEIVED,
    PROCESSING,
    SENT,
    NODE_ID_CHANGE,
    COMMAND_COMPLETE,
    RESPONSE_COMPLETE,
    ERROR,
};
inline constexpr unsigned operator+ (ActionEvent const val) { return static_cast<unsigned>(val); }
inline const char* operator++(ActionEvent const e)
{
    switch (e)
    {
    case ActionEvent::ACTIVE:
        return "ACTIVE";
        break;
    case ActionEvent::DEACTIVE:
        return "DEACTIVE";
        break;
    case ActionEvent::WIFI_DOWN:
        return "WIFI_DOWN";
        break;
    case ActionEvent::WIFI_UP:
        return "WIFI_UP";
        break;
    case ActionEvent::MQTT_DOWN:
        return "MQTT_DOWN";
        break;
    case ActionEvent::MQTT_UP:
        return "MQTT_UP";
        break;
    case ActionEvent::INITIALIZING:
        return "INITIALIZING";
        break;
    case ActionEvent::CONFIGURE:
        return "CONFIGURE";
        break;
    case ActionEvent::WAITING:
        return "WAITING";
        break;
    case ActionEvent::MSG_RECEIVED:
        return "MSG_RECEIVED";
        break;
    case ActionEvent::PROCESSING:
        return "PROCESSING";
        break;
    case ActionEvent::SENT:
        return "SENT";
        break;
    case ActionEvent::NODE_ID_CHANGE:
        return "NODE_ID_CHANGE";
        break;
    case ActionEvent::COMMAND_COMPLETE:
        return "COMMAND_COMPLETE";
        break;
    case ActionEvent::RESPONSE_COMPLETE:
        return "RESPONSE_COMPLETE";
        break;
    case ActionEvent::ERROR:
        return "ERROR";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}