/*
 * Configuration.cpp
 *
 *  Created on: Nov 17, 2023
 *      Author: cyberreefguru
 */
#include "Configuration.h"

Configuration::Configuration()
{
}

bool Configuration::initialize()
{
    bool b = false;

    preferences.begin(NAMESPACE, false);

    return b;
}

uint8_t Configuration::getId()
{
    return preferences.getUChar(KEY_NODE_ID, 1);
}

uint32_t Configuration::getDelay()
{
    return preferences.getULong(KEY_DELAY, 500);
}

String Configuration::getWifiSsid()
{
    return preferences.getString(KEY_WIFI_SSID, String("aquarius") );
}

String Configuration::getWifiPassword()
{
    return preferences.getString(KEY_WIFI_PASSWORD, String("imsecure"));
}

uint8_t Configuration::getWifiRety()
{
    return preferences.getUChar(KEY_WIFI_RETRIES, 10);
}

uint32_t Configuration::getWifiDelay()
{
    return preferences.getULong(KEY_WIFI_DELAY, 500);
}

uint32_t Configuration::getWifiTimeout()
{
    return preferences.getULong(KEY_WIFI_TIMEOUT, 10*1000);
}

String Configuration::getMqttUid()
{
    return preferences.getString(KEY_MQTT_USER, String("mqtt"));
}

String Configuration::getMqttPassword()
{
    return preferences.getString(KEY_MQTT_PASSWORD, String("imsecure"));
}
uint8_t Configuration::getMqttRety()
{
    return preferences.getUChar(KEY_MQTT_RETRIES, 10);
}
uint32_t Configuration::getMqttDelay()
{
    return preferences.getULong(KEY_MQTT_DELAY, 500);
}
uint32_t Configuration::getMqttTimeout()
{
    return preferences.getULong(KEY_MQTT_TIMEOUT, 10*1000);
}

uint32_t Configuration::getInitializeColor()
{
    return preferences.getULong(KEY_COLOR_INITIALIZE, 0x0000F700);
}
uint32_t Configuration::getDeactiveColor()
{
    return preferences.getULong(KEY_COLOR_DEACTIVE, 0x00000000);
}
uint32_t Configuration::getActiveColor()
{
    return preferences.getULong(KEY_COLOR_ACTTIVE, 0x00C800C8);
}
uint32_t Configuration::getSendColor()
{
    return preferences.getULong(KEY_COLOR_SEND, 0x0000FFFF);
}
uint32_t Configuration::getProcessColor()
{
    return preferences.getULong(KEY_COLOR_PROCESS, 0x0000FFFF);
}
uint32_t Configuration::getReceiveColor()
{
    return preferences.getULong(KEY_COLOR_RECEIVE, 0x0000FFFF);
}
uint32_t Configuration::getWaitColor()
{
    return preferences.getULong(KEY_COLOR_WAIT, 0x000000FF);
}
uint32_t Configuration::getConnectColor()
{
    return preferences.getULong(KEY_COLOR_CONNECT, 0x000000FF);
}
uint32_t Configuration::getErrorColor()
{
    return preferences.getULong(KEY_COLOR_ERROR, 0x00FF0000);
}
uint8_t Configuration::getServoStart()
{
    return preferences.getShort(KEY_SERVO_START, 0);
}
uint8_t Configuration::getServoStop()
{
    return preferences.getShort(KEY_SERVO_STOP, 180);
}
uint8_t Configuration::getSensorThreshold()
{
    return preferences.getShort(KEY_SENSOR_THRESHOLD, 128);
}
