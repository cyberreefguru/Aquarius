/*
 * PreferenceManager.h
 *
 *  Created on: Nov 17, 2023
 *      Author: cyberreefguru
 */
#pragma once

#include <ArduinoLog.h>
#include <Preferences.h>
#include "menu/MenuColor.h"

#define NAMESPACE "aquarius"

#define KEY_VERSION "version"
#define KEY_CONFIGURED "configured"

#define KEY_NODE_ID "id"
// #define KEY_DELAY "delay"

#define KEY_HOST_NAME "wifi.hostname"
#define KEY_WIFI_SSID "wifi.ssid"
#define KEY_WIFI_PASSWORD "wifi.password"
#define KEY_WIFI_RETRIES "wifi.retries"
#define KEY_WIFI_DELAY "wifi.delay"
#define KEY_WIFI_TIMEOUT "wifi.timeout"

#define KEY_MQTT_SERVER "mqtt.server"
#define KEY_MQTT_PORT "mqtt.port"
#define KEY_MQTT_USER "mqtt.user"
#define KEY_MQTT_PASSWORD "mqtt.pass"
#define KEY_MQTT_RETRIES "mqtt.retries"
#define KEY_MQTT_DELAY "mqtt.delay"
#define KEY_MQTT_TIMEOUT "mqtt.timeout"

#define KEY_COLOR_INITIALIZE "c.init"
#define KEY_COLOR_CONFIGURE "c.config"
#define KEY_COLOR_CONNECT "c.connect"
#define KEY_COLOR_RECEIVE "c.receive"
#define KEY_COLOR_PROCESS "c.process"
#define KEY_COLOR_SEND "c.send"
#define KEY_COLOR_WAIT "c.wait"

#define KEY_COLOR_ERROR "c.error"
#define KEY_COLOR_WIFI_DOWN "c.w.down"
#define KEY_COLOR_WIFI_UP "c.w.up"
#define KEY_COLOR_MQTT_DOWN "c.m.down"
#define KEY_COLOR_MQTT_UP "c.m.up"

#define KEY_COLOR_ACTIVE "color.active"
#define KEY_COLOR_DEACTIVE "color.deactive"

#define KEY_SERVO_START "s.start"
#define KEY_SERVO_STOP "s.stop"

#define KEY_SENSOR_THRESHOLD "s.t"

#define KEY_TARGETS "ts"
#define KEY_TARGET "t"
#define KEY_TARGET_NODE_ID  "t.nid"
#define KEY_TARGET_START_DELAY  "t.sd"
#define KEY_TARGET_END_DELAY  "t.ed"

#define KEY_DISPLAY_SIZE "d.s"

#define KEY_BRIGHTNESS_SCREEN "b.s"
#define KEY_BRIGHTNESS_LED "b.i"


#define DEFAULT_NODE_ID 1
#define DEFAULT_DELAY 500

#define DEFAULT_HOST_NAME "aquarius"
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

#define DEFAULT_COLOR_INITIALIZE (uint32_t)colorOrange.value
#define DEFAULT_COLOR_CONFIGURE (uint32_t)colorCyan.value
#define DEFAULT_COLOR_SEND (uint32_t)colorBlue.value
#define DEFAULT_COLOR_PROCESS (uint32_t)colorBlue.value
#define DEFAULT_COLOR_RECEIVE (uint32_t)colorBlue.value
#define DEFAULT_COLOR_CONNECT (uint32_t)colorBlue.value
#define DEFAULT_COLOR_WAIT (uint32_t)colorGreen.value

#define DEFAULT_COLOR_WIFI_DOWN (uint32_t)colorMagenta.value
#define DEFAULT_COLOR_WIFI_UP (uint32_t)colorBlue.value
#define DEFAULT_COLOR_MQTT_DOWN (uint32_t)colorPurple.value
#define DEFAULT_COLOR_MQTT_UP (uint32_t)colorBlue.value
#define DEFAULT_COLOR_ERROR (uint32_t)colorRed.value

#define DEFAULT_COLOR_ACTIVE (uint32_t)colorGreen.value
#define DEFAULT_COLOR_DEACTIVE (uint32_t)colorBlack.value

#define DEFAULT_SERVO_START 0
#define DEFAULT_SERVO_STOP 180

#define DEFAULT_SENSOR_THRESHOLD 128

#define DEFAULT_DISPLAY_SIZE DisplaySize::Regular

#define DEFAULT_BRIGHTNESS_SCREEN 255
#define DEFAULT_LED_BRIGHTNESS 25
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
    uint32_t getConfigureColor();
    uint32_t getDeactiveColor();
    uint32_t getActiveColor();
    uint32_t getSendColor();
    uint32_t getProcessColor();
    uint32_t getReceiveColor();
    uint32_t getWaitColor();
    uint32_t getConnectColor();
    uint32_t getErrorColor();
    uint32_t getWifiDownColor();
    uint32_t getWifiUpColor();
    uint32_t getMqttDownColor();
    uint32_t getMqttUpColor();

    uint8_t getServoStart();
    uint8_t getServoStop();

    uint8_t getSensorThreshold();

    uint8_t getDisplaySize();

    void set(char const *key, uint8_t v);
    void set(char const *key, uint16_t v);
    void set(char const *key, uint32_t v);
    void set(char const *key, char *v, uint8_t len);
    void set(char const *key, MenuColor color);

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

    // inline constexpr unsigned operator+ (ActionEvent const val) { return static_cast<unsigned>(val); }
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