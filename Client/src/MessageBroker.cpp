/**
 * @brief Manages message broker
 * @file MessageBroker.cpp
 * @date Nov 15, 2023
 * @author cyberreefguru
 */


#include "MessageBroker.h"

MessageBroker messageBroker;

MessageBroker::MessageBroker() {}

void MessageBroker::initialize()
{
    Log.traceln("MessageBroker::initialize - BEGIN");

    // Initialize Wifi
    if (WiFi.isConnected())
    {
        WiFi.disconnect();
    }
    WiFi.mode(WIFI_STA);

    WiFi.onEvent([this](WiFiEvent_t event, WiFiEventInfo_t info)
                 { this->onWifiEvent(event, info); },
                 ARDUINO_EVENT_MAX);

    // Initialize MQTT
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCredentials(MQTT_USER, MQTT_PASSWORD);
    client.setClientId("aquarius_client");
    client.onConnect([this](bool b)
                     { this->onMqttConnect(b); });
    client.onDisconnect([this](AsyncMqttClientDisconnectReason reason)
                     { this->onMqttDisconnect(reason); });
    client.onSubscribe([this](uint16_t packetId, uint8_t qos){this->onMqttSubscribe(packetId, qos);});
    client.onUnsubscribe([this](uint16_t packetId){this->onMqttUnsubscribe(packetId);});
    client.onMessage([this](char *topic, char *payload, AsyncMqttClientMessageProperties properties, 
    size_t len, size_t index, size_t total){this->onMqttMessage(topic, payload, properties,
     len, index, total);});
    client.onPublish([this](uint16_t packetId){this->onMqttPublish(packetId);});

    // Initialize timeout timers
    wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, static_cast<void *>(this), [](TimerHandle_t handler)
                                      { messageBroker.connectToWifi(); });
    mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, static_cast<void *>(this), [](TimerHandle_t handler)
                                      { messageBroker.connectToMqtt(); });

    // Connect to WIFI 
    // If successful, event manager will connect to MQTT.
    connectToWifi();

    Log.traceln("MessageBroker::initialize - END");

}

void MessageBroker::connectToWifi()
{
    Log.infoln("MessageBroker::connectToWifi - Connecting to WIFI...");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
}

void MessageBroker::onWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Log.traceln("MessageBroker::onWifiEvent - [WiFi-event]: %s", Helper::toString(event));
    switch (event)
    {
    case SYSTEM_EVENT_STA_GOT_IP:
        Log.traceln("MessageBroker::onWifiEvent - IP address: ");
        Log.traceln(WiFi.localIP());
        actionEventManager.postEvent(ActionEvent::WIFI_UP);
        connectToMqtt();
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Log.traceln("MessageBroker::onWifiEvent - WiFi lost connection");
        actionEventManager.postEvent(ActionEvent::WIFI_DOWN);
        xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
        xTimerStart(wifiReconnectTimer, 0);
        break;
    case SYSTEM_EVENT_STA_CONNECTED:
        Log.traceln("MessageBroker::onWifiEvent - WiFi connected");
        break;
    }
}


void MessageBroker::connectToMqtt()
{
    Log.traceln("MessageBroker::connectToMqtt - connecting to MQTT....");
    client.connect();
}

void MessageBroker::onMqttConnect(bool sessionPresent)
{
    Log.traceln("MessageBroker::onMqttConnect - BEGIN");
    client.subscribe(MQTT_CHANNEL_ALL, 2);
    client.subscribe(MQTT_CHANNEL_CMD, 2);
    client.subscribe(MQTT_CHANNEL_REG, 2);
    client.subscribe(MQTT_CHANNEL_RESP, 2);

    // Log.trace("Subscribing at QoS 2, packetId: ");
    // Log.traceln("%d", packetIdSub);
    // client.publish("test/lol", 0, true, "test 1");
    // Log.traceln("Publishing at QoS 0");
    // uint16_t packetIdPub1 = client.publish("test/lol", 1, true, "test 2");
    // Log.trace("Publishing at QoS 1, packetId: ");
    // Log.traceln("%d", packetIdPub1);
    // uint16_t packetIdPub2 = client.publish("test/lol", 2, true, "test 3");
    // Log.trace("Publishing at QoS 2, packetId: ");
    // Log.traceln("%d", packetIdPub2);
    actionEventManager.postEvent(ActionEvent::MQTT_UP);

    Log.traceln("MessageBroker::onMqttConnect - END");

}

void MessageBroker::onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
    Log.traceln("MessageBroker::onMqttDisconnect - BEGIN");

    actionEventManager.postEvent(ActionEvent::MQTT_DOWN);
    Log.errorln("Disconnected from MQTT.");
    if (WiFi.isConnected())
    {
        xTimerStart(mqttReconnectTimer, 0);
    }

    Log.traceln("MessageBroker::onMqttDisconnect - END");
}

void MessageBroker::onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
    Log.traceln("MessageBroker::onMqttSubscribe - BEGIN");
    Log.traceln("MessageBroker::onMqttSubscribe - Subscribe acknowledged.");
    Log.trace("MessageBroker::onMqttSubscribe - packetId: ");
    Log.traceln("%d", packetId);
    Log.trace("MessageBroker::onMqttSubscribe - qos: ");
    Log.traceln("%d", qos);
    if( packetId == 4 )
    {
        actionEventManager.postEvent(ActionEvent::WAITING);
    }
    Log.traceln("MessageBroker::onMqttSubscribe - END");
}

void MessageBroker::onMqttUnsubscribe(uint16_t packetId)
{
    Log.traceln("MessageBroker::onMqttUnsubscribe - BEGIN");
    Log.trace("MessageBroker::onMqttUnsubscribe - packetId: ");
    Log.traceln("%d", packetId);
}

void MessageBroker::onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
    Log.traceln("MessageBroker::onMqttMessage - BEGIN");

    char new_payload[len+1];
    new_payload[len] = '\0';
    strncpy(new_payload, payload, len);
    Log.trace("  topic: ");
    Log.traceln("%s", topic);
    Log.trace("  qos: ");
    Log.traceln("%d", properties.qos);
    Log.trace("  dup: ");
    Log.traceln("%d", properties.dup);
    Log.trace("  retain: ");
    Log.traceln("%d", properties.retain);
    Log.trace("  len: ");
    Log.traceln("%d", len);
    Log.trace("  index: ");
    Log.traceln("%d", index);
    Log.trace("  total: ");
    Log.traceln("%d", total);
    Log.traceln(" payload: %s", new_payload);

    actionEventManager.postEvent(ActionEvent::MSG_RECEIVED, new_payload, len+1);

    Log.traceln("MessageBroker::onMqttMessage - END");

}

void MessageBroker::onMqttPublish(uint16_t packetId)
{
    Log.traceln("MessageBroker::onMqttPublish - BEGIN");
    Log.traceln("MessageBroker::onMqttPublish - Publish acknowledged.");
    Log.trace("MessageBroker::onMqttPublish - packetId: ");
    Log.traceln("%d", packetId);
    Log.traceln("MessageBroker::onMqttPublish - END");
}
