/*
 * Configuration.h
 *
 *  Created on: Nov 17, 2023
 *      Author: cyberreefguru
 */
#pragma once

#include <Preferences.h>

#define NAMESPACE                   "aquarius"

#define KEY_NODE_ID					"id"
#define KEY_DELAY					"delay"

#define KEY_HOST_NAME				"wifi_hostname"
#define KEY_WIFI_SSID				"wifi_ssid"
#define KEY_WIFI_PASSWORD			"wifi_password"
#define KEY_WIFI_RETRIES			"wifi_retries"
#define KEY_WIFI_DELAY		       	"wifi_delay"
#define KEY_WIFI_TIMEOUT    		"wifi_timeout"

#define KEY_MQTT_SERVER				"mqtt_server"
#define KEY_MQTT_PORT				"mqtt_port"
#define KEY_MQTT_USER				"mqtt_user"
#define KEY_MQTT_PASSWORD			"mqtt_pass"
#define KEY_MQTT_RETRIES			"mqtt_retries"
#define KEY_MQTT_DELAY		       	"mqtt_delay"
#define KEY_MQTT_TIMEOUT    		"mqtt_timeout"

#define KEY_COLOR_INITIALIZE   		"color_initialize"
#define KEY_COLOR_DEACTIVE   		"color_deactive"
#define KEY_COLOR_ACTTIVE      		"color_active"
#define KEY_COLOR_SEND         		"color_send"
#define KEY_COLOR_PROCESS   		"color_process"
#define KEY_COLOR_RECEIVE   		"color_receive"
#define KEY_COLOR_WAIT         		"color_wait"
#define KEY_COLOR_CONNECT   		"color_connect"
#define KEY_COLOR_ERROR        		"color_error"
#define KEY_SERVO_START        		"servo_start"
#define KEY_SERVO_STOP         		"servo_stop"
#define KEY_SENSOR_THRESHOLD   		"sensor_threshold"


class Configuration {

public:
	Configuration();
	bool initialize();

    uint8_t getId();
    uint32_t getDelay();

    String getWifiSsid();
    String getWifiPassword();
    uint8_t getWifiRety();
    uint32_t getWifiDelay();
    uint32_t getWifiTimeout();

    String getMqttUid();
    String getMqttPassword();
    uint8_t getMqttRety();
    uint32_t getMqttDelay();
    uint32_t getMqttTimeout();

    uint32_t getInitializeColor();
    uint32_t getDeactiveColor();
    uint32_t getActiveColor();
    uint32_t getSendColor();
    uint32_t getProcessColor();
    uint32_t getReceiveColor();
    uint32_t getWaitColor();
    uint32_t getConnectColor();
    uint32_t getErrorColor();

    uint8_t getServoStart();
    uint8_t getServoStop();

    uint8_t getSensorThreshold();

private:
	boolean config = false;
    Preferences preferences;

    char* getString(char* key);
    uint32_t getInt32(char* key);
    uint16_t getInt16(char* key);
    uint8_t getInt8(char* key);

    void set(char * key, uint8_t v);
    void set(char * key, uint16_t v);
    void set(char * key, uint32_t v);
    void set(char * key, char* v);
    void set(char * key, String v);

};
