/*
 * PreferenceManager.cpp
 *
 *  Created on: Nov 17, 2023
 *      Author: cyberreefguru
 */
#include "PreferenceManager.h"

/** Global instance of preference manager */
PreferenceManager prefManager;

/** Constructor */
PreferenceManager::PreferenceManager()
{
}

bool PreferenceManager::initialize()
{
    Log.infoln("Initializing preferences...");
    bool b = false;

    zeroBuffers();

    if( preferences.begin(NAMESPACE, false) )
    {
        if( preferences.isKey(KEY_CONFIGURED) == false)
        {
            Log.infoln("Reseting preferences...");

            // If we have no configured key, reset everything
            reset();
        }

        Log.infoln("Reading preferences...");
        preferences.getBytes(KEY_HOST_NAME, hostname, MAX_HOSTNAME);
        preferences.getBytes(KEY_WIFI_SSID, wifi_ssid, MAX_SSID);
        preferences.getBytes(KEY_WIFI_PASSWORD, wifi_pass, MAX_PASSWORD);
        preferences.getBytes(KEY_MQTT_USER, mqtt_user, MAX_USER_ID);
        preferences.getBytes(KEY_MQTT_PASSWORD, mqtt_pass, MAX_PASSWORD);
        
        Log.infoln("Hostname: %s", hostname);
        Log.infoln("SSID: %s, Pwd: %s", wifi_ssid, wifi_pass);
        Log.infoln("Mqtt User: %s, Pwd: %s", mqtt_user, mqtt_pass);
        
        Log.infoln("Preferences initialized!");
    }
    else
    {
        Log.errorln("Error starting preferences!");
    }


    return b;
}

void PreferenceManager::zeroBuffers()
{
    // Zero buffers
    memset(hostname, 0, MAX_HOSTNAME);
    memset(wifi_ssid, 0, MAX_SSID);
    memset(wifi_pass, 0, MAX_PASSWORD);
    memset(mqtt_user, 0, MAX_USER_ID);
    memset(mqtt_pass, 0, MAX_PASSWORD);
}

void PreferenceManager::resetBuffers()
{
    strncpy(hostname, DEFAULT_HOST_NAME, strnlen(DEFAULT_HOST_NAME, MAX_HOSTNAME));
    strncpy(wifi_ssid, DEFAULT_WIFI_SSID, strnlen(DEFAULT_WIFI_SSID, MAX_SSID));
    strncpy(wifi_pass, DEFAULT_WIFI_PASSWORD, strnlen(DEFAULT_WIFI_PASSWORD, MAX_PASSWORD));
    strncpy(mqtt_user, DEFAULT_MQTT_USER, strnlen(DEFAULT_MQTT_USER, MAX_USER_ID));
    strncpy(mqtt_pass, DEFAULT_MQTT_PASSWORD, strnlen(DEFAULT_MQTT_PASSWORD, MAX_PASSWORD));
}
void PreferenceManager::reset()
{
    // Zero buffers
    zeroBuffers();

    // Reset Buffers
    resetBuffers();

    preferences.putUChar(KEY_CONFIGURED, true);
    preferences.putUChar(KEY_NODE_ID, DEFAULT_NODE_ID);
    preferences.putBytes(KEY_HOST_NAME, hostname, strnlen(hostname, MAX_HOSTNAME));
    preferences.putBytes(KEY_WIFI_SSID, wifi_ssid, strnlen(wifi_ssid, MAX_SSID));
    preferences.putBytes(KEY_WIFI_PASSWORD, wifi_pass, strnlen(wifi_pass, MAX_PASSWORD));
    preferences.putUChar(KEY_WIFI_RETRIES, DEFAULT_WIFI_RETRIES);
    preferences.putULong(KEY_WIFI_DELAY, DEFAULT_WIFI_DELAY);
    preferences.putULong(KEY_WIFI_TIMEOUT, DEFAULT_WIFI_TIMEOUT);
    preferences.putBytes(KEY_MQTT_USER, mqtt_user, strnlen(mqtt_user, MAX_USER_ID));
    preferences.putBytes(KEY_MQTT_PASSWORD, mqtt_pass, strnlen(mqtt_pass, MAX_PASSWORD));
    preferences.putUChar(KEY_MQTT_RETRIES, DEFAULT_MQTT_RETRIES);
    preferences.putULong(KEY_MQTT_DELAY, DEFAULT_MQTT_DELAY);
    preferences.putULong(KEY_MQTT_TIMEOUT, DEFAULT_MQTT_TIMEOUT);
    preferences.putULong(KEY_COLOR_INITIALIZE, DEFAULT_COLOR_INITIALIZE);
    preferences.putULong(KEY_COLOR_DEACTIVE, DEFAULT_COLOR_DEACTIVE);
    preferences.putULong(KEY_COLOR_ACTTIVE, DEFAULT_COLOR_ACTTIVE);
    preferences.putULong(KEY_COLOR_SEND, DEFAULT_COLOR_SEND);
    preferences.putULong(KEY_COLOR_PROCESS, DEFAULT_COLOR_PROCESS);
    preferences.putULong(KEY_COLOR_RECEIVE, DEFAULT_COLOR_RECEIVE);
    preferences.putULong(KEY_COLOR_WAIT, DEFAULT_COLOR_WAIT);
    preferences.putULong(KEY_COLOR_CONNECT, DEFAULT_COLOR_CONNECT);
    preferences.putULong(KEY_COLOR_ERROR, DEFAULT_COLOR_ERROR);
    preferences.putShort(KEY_SERVO_START, DEFAULT_SERVO_START);
    preferences.putShort(KEY_SERVO_STOP, DEFAULT_SERVO_STOP);
    preferences.putShort(KEY_SENSOR_THRESHOLD, DEFAULT_SENSOR_THRESHOLD);
    preferences.putUChar(KEY_DISPLAY_SIZE, DEFAULT_DISPLAY_SIZE);

}

uint8_t PreferenceManager::getId()
{
    return preferences.getUChar(KEY_NODE_ID, DEFAULT_NODE_ID);
}

// uint32_t PreferenceManager::getDelay()
// {
//     return preferences.getULong(KEY_DELAY, DEFAULT_DELAY);
// }

char * PreferenceManager::getWifiSsid()
{
    return wifi_ssid;
}

char* PreferenceManager::getWifiPassword()
{
    return wifi_pass;
}

uint8_t PreferenceManager::getWifiRety()
{
    return preferences.getUChar(KEY_WIFI_RETRIES, 10);
}

uint32_t PreferenceManager::getWifiDelay()
{
    return preferences.getULong(KEY_WIFI_DELAY, 500);
}

uint32_t PreferenceManager::getWifiTimeout()
{
    return preferences.getULong(KEY_WIFI_TIMEOUT, 10 * 1000);
}

char* PreferenceManager::getMqttUserId()
{
    return mqtt_user;
}

char* PreferenceManager::getMqttPassword()
{
    return mqtt_pass;
}
uint8_t PreferenceManager::getMqttRety()
{
    return preferences.getUChar(KEY_MQTT_RETRIES, 10);
}
uint32_t PreferenceManager::getMqttDelay()
{
    return preferences.getULong(KEY_MQTT_DELAY, 500);
}
uint32_t PreferenceManager::getMqttTimeout()
{
    return preferences.getULong(KEY_MQTT_TIMEOUT, 10 * 1000);
}

uint32_t PreferenceManager::getInitializeColor()
{
    return preferences.getULong(KEY_COLOR_INITIALIZE, 0x0000F700);
}
uint32_t PreferenceManager::getDeactiveColor()
{
    return preferences.getULong(KEY_COLOR_DEACTIVE, 0x00000000);
}
uint32_t PreferenceManager::getActiveColor()
{
    return preferences.getULong(KEY_COLOR_ACTTIVE, 0x00C800C8);
}
uint32_t PreferenceManager::getSendColor()
{
    return preferences.getULong(KEY_COLOR_SEND, 0x0000FFFF);
}
uint32_t PreferenceManager::getProcessColor()
{
    return preferences.getULong(KEY_COLOR_PROCESS, 0x0000FFFF);
}
uint32_t PreferenceManager::getReceiveColor()
{
    return preferences.getULong(KEY_COLOR_RECEIVE, 0x0000FFFF);
}
uint32_t PreferenceManager::getWaitColor()
{
    return preferences.getULong(KEY_COLOR_WAIT, 0x000000FF);
}
uint32_t PreferenceManager::getConnectColor()
{
    return preferences.getULong(KEY_COLOR_CONNECT, 0x000000FF);
}
uint32_t PreferenceManager::getErrorColor()
{
    return preferences.getULong(KEY_COLOR_ERROR, 0x00FF0000);
}
uint8_t PreferenceManager::getServoStart()
{
    return preferences.getShort(KEY_SERVO_START, 0);
}
uint8_t PreferenceManager::getServoStop()
{
    return preferences.getShort(KEY_SERVO_STOP, 180);
}
uint8_t PreferenceManager::getSensorThreshold()
{
    return preferences.getShort(KEY_SENSOR_THRESHOLD, 128);
}
uint8_t PreferenceManager::getDisplaySize()
{
    return preferences.getUChar(KEY_DISPLAY_SIZE);
}


void PreferenceManager::set( char const *key, uint8_t v)
{
    preferences.putUChar(key, v);
}
void PreferenceManager::set(char const *key, uint16_t v)
{
    preferences.putUShort(key, v);
}
void PreferenceManager::set(char const *key, uint32_t v)
{
    preferences.putULong(key, v);
}
void PreferenceManager::set(char const *key, char *v, uint8_t len)
{
    preferences.putBytes(key, v, len);
}
