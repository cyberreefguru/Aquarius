/*
 * PreferenceManager.h
 *
 *  Created on: Nov 17, 2023
 *      Author: cyberreefguru
 */
#pragma once

#include <ArduinoLog.h>
#include <Preferences.h>

#define NAMESPACE "aquarius"

#define KEY_VERSION "version"
#define KEY_CONFIGURED "configured"

#define KEY_NODE_ID "id"
// #define KEY_DELAY "delay"

#define KEY_HOST_NAME "wifi_hostname"
#define KEY_WIFI_SSID "wifi_ssid"
#define KEY_WIFI_PASSWORD "wifi_password"
#define KEY_WIFI_RETRIES "wifi_retries"
#define KEY_WIFI_DELAY "wifi_delay"
#define KEY_WIFI_TIMEOUT "wifi_timeout"

#define KEY_MQTT_SERVER "mqtt_server"
#define KEY_MQTT_PORT "mqtt_port"
#define KEY_MQTT_USER "mqtt_user"
#define KEY_MQTT_PASSWORD "mqtt_pass"
#define KEY_MQTT_RETRIES "mqtt_retries"
#define KEY_MQTT_DELAY "mqtt_delay"
#define KEY_MQTT_TIMEOUT "mqtt_timeout"

#define KEY_COLOR_INITIALIZE "color_initialize"
#define KEY_COLOR_DEACTIVE "color_deactive"
#define KEY_COLOR_ACTTIVE "color_active"
#define KEY_COLOR_SEND "color_send"
#define KEY_COLOR_PROCESS "color_process"
#define KEY_COLOR_RECEIVE "color_receive"
#define KEY_COLOR_WAIT "color_wait"
#define KEY_COLOR_CONNECT "color_connect"
#define KEY_COLOR_ERROR "color_error"

#define KEY_SERVO_START "servo_start"
#define KEY_SERVO_STOP "servo_stop"

#define KEY_SENSOR_THRESHOLD "sensor_threshold"

#define KEY_DISPLAY_SIZE "display_size"

#define DEFAULT_NODE_ID 1
#define DEFAULT_DELAY 500

#define DEFAULT_HOST_NAME "aquarius 1"
#define DEFAULT_WIFI_SSID "aquarius"
#define DEFAULT_WIFI_PASSWORD "iamsecure"
#define DEFAULT_WIFI_RETRIES 10
#define DEFAULT_WIFI_DELAY 500
#define DEFAULT_WIFI_TIMEOUT 10 * 1000

#define DEFAULT_MQTT_SERVER "192.168.30.210"
#define DEFAULT_MQTT_PORT 1883
#define DEFAULT_MQTT_USER "mqtt_user"
#define DEFAULT_MQTT_PASSWORD "mqtt"
#define DEFAULT_MQTT_RETRIES 10
#define DEFAULT_MQTT_DELAY 500
#define DEFAULT_MQTT_TIMEOUT 10 * 1000

#define DEFAULT_COLOR_INITIALIZE 0x0000F700
#define DEFAULT_COLOR_DEACTIVE 0x00000000
#define DEFAULT_COLOR_ACTTIVE 0x00C800C8
#define DEFAULT_COLOR_SEND 0x0000FFFF
#define DEFAULT_COLOR_PROCESS 0x0000FFFF
#define DEFAULT_COLOR_RECEIVE 0x0000FFFF
#define DEFAULT_COLOR_WAIT 0x000000FF
#define DEFAULT_COLOR_CONNECT 0x000000FF
#define DEFAULT_COLOR_ERROR 0x00FF0000

#define DEFAULT_SERVO_START 0
#define DEFAULT_SERVO_STOP 180

#define DEFAULT_SENSOR_THRESHOLD 128

#define DEFAULT_DISPLAY_SIZE DisplaySize::Regular

#define MAX_HOSTNAME 64
#define MAX_SSID 32
#define MAX_USER_ID 32
#define MAX_PASSWORD 32

class PreferenceManager
{

public:
    PreferenceManager();
    bool initialize();

    void reset();

    uint8_t getId();
    uint32_t getDelay();

    char *getWifiSsid();
    char *getWifiPassword();
    uint8_t getWifiRety();
    uint32_t getWifiDelay();
    uint32_t getWifiTimeout();

    char *getMqttUserId();
    char *getMqttPassword();
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

    uint8_t getDisplaySize();

    void set(char const *key, uint8_t v);
    void set(char const *key, uint16_t v);
    void set(char const *key, uint32_t v);
    void set(char const *key, char *v, uint8_t len);

private:
    boolean config = false;
    Preferences preferences;

    void resetBuffers();
    void zeroBuffers();

    char hostname[64];

    char wifi_ssid[32];
    char wifi_pass[32];

    char mqtt_user[32];
    char mqtt_pass[32];
};

class DisplaySize
{
public:
    enum SizeType : uint8_t
    {
        Regular = 0,
        Large
    };

    DisplaySize() = default;
    constexpr DisplaySize(SizeType v) : size(v) {}

    operator SizeType() const { return size; }

    constexpr bool operator==(DisplaySize s) const { return size == s.size; }
    constexpr bool operator!=(DisplaySize s) const { return size != s.size; }
    constexpr bool operator==(SizeType st) const { return size == st; }
    constexpr bool operator!=(SizeType st) const { return size != st; }
    // inline constexpr uint8_t operator+(DisplaySize val) const { return static_cast<uint8_t>(val.size); }
    // inline constexpr uint8_t operator+(SizeType val) const { return static_cast<uint8_t>(size); }
    // constexpr unsigned operator+ (DisplaySize s) const { return s.size; }
    constexpr bool isLarge() const { return size == Large; }

    // inline constexpr unsigned operator+ (Event const val) { return static_cast<unsigned>(val); }
private:
    SizeType size;
};

// end of add your includes here
#ifdef __cplusplus
    extern "C"
    {
#endif

    extern PreferenceManager prefManager;

#ifdef __cplusplus
} // extern "C"
#endif