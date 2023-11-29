/*
 * PubSubWrapper.h
 *
 *  Created on: Feb 21, 2016
 *      Author: tsasala
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
//#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "PubSubWrapper.h"
#include "WifiWrapper.h"

enum class MqttStatusCode {IDLE, CONNECTED, DISCONNECTED, UNKNOWN };

#define CMD_BUFFER_SIZE		512

#define DEFAULT_MQTT_SERVER			"192.168.30.210"
// #define DEFAULT_MQTT_SERVER			"10.10.5.1"
#define DEFAULT_MQTT_USER			"mqtt_user"
#define DEFAULT_MQTT_PASSWORD		"mqtt"
#define DEFAULT_MQTT_PORT			1883

#define DEFAULT_MQTT_CHANNEL_ALL	"aquarius/all"
#define DEFAULT_MQTT_CHANNEL_CMD	"aquarius/cmd"
#define DEFAULT_MQTT_CHANNEL_REG	"aquarius/reg"
#define DEFAULT_MQTT_CHANNEL_RESP	"aquarius/resp"

#define STRING_SIZE					32

class PubSubWrapper
{
public:
	PubSubWrapper();
	uint8_t initialize(WifiWrapper* wifi);
	void callback(char* topic, byte* payload, unsigned int length);

	uint8_t connect();
	uint8_t disconnect();
	uint8_t checkConnection();
	uint8_t connected();

	void work();
	void publish(char *channel);
	void publish( char *channel, char* buffer);
	void publish( char *channel, JsonObject& obj);
	uint8_t *getBuffer();

	// const uint8_t* getServer() const;
	// void setServer(uint8_t *b);

	// uint16_t getPort() const;
	// void setPort(uint16_t port);

	// const uint8_t* getUser() const;
	// void setUser(uint8_t *b);

	// const uint8_t* getPassword() const;
	// void setPassword(uint8_t *b);

	uint8_t getRetries() const;
	void setRetries(uint8_t t);

	uint32_t getRetryDelay() const;
	void setRetryDelay(uint32_t d);

	uint32_t getRetryTimeout() const;
	void setRetryTimeout(uint32_t t);

	const uint8_t* getAllChannel() const;
	void setAllChannel(uint8_t *b);

	const uint8_t* getRegistrationChannel() const;
	void setRegistrationChannel(uint8_t *b);

	const uint8_t* getResponseChannel() const;
	void setResponseChannel(uint8_t *b);

	const uint8_t* getCommandChannel() const;
	void setCommandChannel(uint8_t *b);


    /**
     * Sets the number of times to try during a connection attempt
     */
    void setRetryCount(uint8_t c);

    /**
     * Gets the number of times to try during a connection attempt
     */
    uint8_t getRetryCount();

    /**
     * Sets the time duration to wait until checking for a retry
     */
    void setRetryDelay(uint32_t c);

    /**
     * Sets the time duration to wait until checking for a retry
     */
    uint32_t getRetryDelay();

    /**
     * Sets the status update callback function pointer
     */
	void setConnectionStatusCallback(void (*cb)());


protected:
	PubSubClient pubsub;
	uint8_t* cmdBuf;
	uint8_t retryCount;
    uint32_t retryDelay;
    uint32_t retryTimeout;

 	// uint8_t mqttServer[STRING_SIZE];
	// uint16_t mqttPort;
	// uint8_t mqttUser[STRING_SIZE];
	// uint8_t mqttPassword[STRING_SIZE];
	// uint8_t mqttTries;

	uint8_t allChannel[STRING_SIZE];
	uint8_t regChannel[STRING_SIZE];
	uint8_t cmdChannel[STRING_SIZE];
	uint8_t respChannel[STRING_SIZE];

	void (*callbackConnectionStatus)();

};


//end of add your includes here
#ifdef __cplusplus
extern "C"
{
#endif

extern boolean isCommandAvailable();
extern void setCommandAvailable(boolean b);
extern boolean commandDelay(uint32_t time);

extern void pubsubCallback(char* topic, byte* payload, unsigned int length);

#ifdef __cplusplus
} // extern "C"
#endif

