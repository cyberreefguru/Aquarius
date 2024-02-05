/**
 * @brief Manages message broker
 * @file MessageBroker.h
 * @date Nov 15, 2023
 * @author cyberreefguru
 */

#ifndef MessageBroker_H
#define MessageBroker_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <AsyncMqttClient.h>

#include "ActionEventManager.h"
#include "Helper.h"


extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}

// enum class MqttStatusCode
// {
//     IDLE,
//     CONNECTED,
//     DISCONNECTED,
//     UNKNOWN
// };

#define CMD_BUFFER_SIZE 512

// #define WIFI_SSID "aquarius"
// #define WIFI_PASS "imsecure"
#define WIFI_SSID "IOT_Down"
#define WIFI_PASS "code5541iot"

#define MQTT_SERVER IPAddress(192, 168, 30, 210)
// #define MQTT_SERVER			IPAddress(10,10,5,1)
#define MQTT_USER "mqtt_user"
#define MQTT_PASSWORD "mqtt"
#define MQTT_PORT 1883

#define MQTT_CHANNEL_ALL "aquarius/all"
#define MQTT_CHANNEL_CMD "aquarius/cmd"
#define MQTT_CHANNEL_REG "aquarius/reg"
#define MQTT_CHANNEL_RESP "aquarius/resp"

#define STRING_SIZE 32

class MessageBroker
{
public:
    MessageBroker();
    void initialize();
    // void callback(char* topic, byte* payload, unsigned int length);
    uint8_t connect();
    uint8_t disconnect();
    // uint8_t checkConnection();
    uint8_t connected();

    // void work();
    void publish(char *channel);
    void publish(char *channel, char *buffer);
    void publish(char *channel, JsonObject &obj);

    void setRetryCount(uint8_t c);
    uint8_t getRetryCount();
    void setRetryDelay(uint32_t c);
    uint32_t getRetryDelay();
    uint32_t getRetryTimeout() const;
    void setRetryTimeout(uint32_t t);

    void connectToWifi();
    void connectToMqtt();
    // void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info);
    void onMqttConnect(bool sessionPresent);
    void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
    void onMqttSubscribe(uint16_t packetId, uint8_t qos);
    void onMqttUnsubscribe(uint16_t packetId);
    void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
    void onMqttPublish(uint16_t packetId);
    void onWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info);

protected:
    AsyncMqttClient client;
    uint8_t retryCount;
    uint32_t retryDelay;
    uint32_t retryTimeout;

    TimerHandle_t mqttReconnectTimer;
    TimerHandle_t wifiReconnectTimer;


    // static void mqttCallback(TimerHandle_t handler)
    // {
    //     MessageBroker *b = static_cast<MessageBroker*>(pvTimerGetTimerID(handler));
    //     b->connectToMqtt();
    //     // broker.connectToMqtt();
    // }

    // static void wifiCallback(TimerHandle_t handler)
    // {
    //     MessageBroker *b = static_cast<MessageBroker*>(pvTimerGetTimerID(handler));
    //     b->connectToWifi();
    //     //broker.connectToWifi();       
    // }


    // WiFi.onEvent(WiFiEvent);
    // client.onConnect(onMqttConnect);
    // client.onDisconnect(onMqttDisconnect);
    // client.onSubscribe(onMqttSubscribe);
    // client.onUnsubscribe(onMqttUnsubscribe);
    // client.onMessage(onMqttMessage);
    // client.onPublish(onMqttPublish);



};


// end of add your includes here
#ifdef __cplusplus
extern "C"
{
#endif

extern MessageBroker messageBroker;

#ifdef __cplusplus
} // extern "C"
#endif

#endif
