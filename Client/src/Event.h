/*
 * Event.h
 *
 *  Created on: Nov 26, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

enum class Event
{
    ACTIVE,
    DEACTIVE,
    WIFI_DOWN,
    WIFI_UP,
    MQTT_DOWN,
    MQTT_UP,
    INITIALIZING,
    WAITING,
    MSG_RECEIVED,
    PROCESSING,
    SENT,
    ERROR
};
inline constexpr unsigned operator+ (Event const val) { return static_cast<unsigned>(val); }