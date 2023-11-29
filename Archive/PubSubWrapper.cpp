/*
 * PubSubWrapper.cpp
 *
 *  Created on: Feb 21, 2016
 *      Author: tsasala
 */

#include "PubSubWrapper.h"

/**
 * Constructor
 */
PubSubWrapper::PubSubWrapper()
{
	cmdBuf = 0;
	retryCount = 10;
	retryDelay = 250;
	retryTimeout = 10*1000;
	callbackConnectionStatus = NULL;
}

/**
 * Initializes the wrapper
 */
uint8_t PubSubWrapper::initialize(WifiWrapper* wifi)
{
	pubsub.setClient( (Client &)wifi->getWifiClient() );

	// Check if we are connected - if so, disconnect
	if( pubsub.connected() )
	{
		Log.warningln(F("Connected already! Disconnecting from queue..."));
		disconnect();
	}

	// Set up mqtt server
	pubsub.setServer( DEFAULT_MQTT_SERVER, DEFAULT_MQTT_PORT);
	pubsub.setCallback(pubsubCallback);

	// Check if we already allocated memory; if so, free it
	if( cmdBuf != 0 )
	{
		free(cmdBuf);
	}

	// Allocate memory
	cmdBuf = (uint8_t *)malloc(CMD_BUFFER_SIZE);
	if( cmdBuf == 0 )
	{
		Log.errorln(F("Unable to allocate buffer memory!"));
		return false;
	}

	return connect();
}

/**
 * Connects to MQTT to server
 *
 */
uint8_t PubSubWrapper::connect()
{
	uint8_t count = 0;
	uint8_t flag = false;

	if( pubsub.connected() )
	{
		Log.infoln(F("Message broker already connected."));
	}
	else
	{
		Log.noticeln(F("Attempting new message broker connection..."));

		// Loop until we're reconnected or "timeout"
		while( count < retryCount )
		{
			if(callbackConnectionStatus)
			{
				callbackConnectionStatus();
			}

			// Attempt to connect
			if (pubsub.connect( DEFAULT_MQTT_CHANNEL_CMD, DEFAULT_MQTT_USER, DEFAULT_MQTT_PASSWORD ) )
			{
				Log.infoln(F("Connected to MQTT Server: "), DEFAULT_MQTT_SERVER );

				// subscribe to channels
				pubsub.subscribe( DEFAULT_MQTT_CHANNEL_ALL );
				pubsub.subscribe( DEFAULT_MQTT_CHANNEL_REG );
				pubsub.subscribe( DEFAULT_MQTT_CHANNEL_RESP );

				// Once connected, publish an announcement...
				Log.noticeln(F("Announcing presence: "), DEFAULT_MQTT_CHANNEL_REG);

				// Tell controller we're listening
				pubsub.publish(DEFAULT_MQTT_CHANNEL_REG, "hi!" );

				flag = true;
				break;
			}
			else
			{
				// Wait before retrying
				// TODO: do I still need this?? Helper::delayYield(retryDelay);
			}
			count += 1;

		} // end while
	}

	if( !flag )
	{
		Log.errorln(F("Unable to bind to broker."));
	}

	return flag;
}

/**
 * Disconnects from MQTT server
 *
 */
uint8_t PubSubWrapper::disconnect()
{
	uint8_t flag = false;

	if( pubsub.connected() )
	{
		Log.noticeln(F("Disconnecting..."));
		pubsub.unsubscribe( DEFAULT_MQTT_CHANNEL_ALL );
		pubsub.unsubscribe( DEFAULT_MQTT_CHANNEL_CMD );
		pubsub.unsubscribe( DEFAULT_MQTT_CHANNEL_REG );
		pubsub.unsubscribe( DEFAULT_MQTT_CHANNEL_RESP );
		pubsub.disconnect();
		Log.infoln(F("Disconnected from message broker."));
		flag = true;

	}
	else
	{
		Log.warningln(F("Cannot disconnect -- not connected!"));
	}

	return flag;
}

uint8_t PubSubWrapper::connected()
{
	return pubsub.connected();
}

/**
 * Checks if we still have a valid connection to the server.
 * If there is no connection, an attempt will be made.
 *
 */
uint8_t PubSubWrapper::checkConnection()
{
	uint8_t flag = pubsub.connected();

	if (!flag)
	{
		flag = connect();
	}

	return flag;
}

/**
 * Calls the loop function to process queue messages
 *
 */
void PubSubWrapper::work()
{
	pubsub.loop();
}


/**
 * Handles all "receive" messages from MQTT
 *
 * Parses the messages and sends to correct handler
 *
 */
void PubSubWrapper::callback(char* topic, byte* payload, unsigned int length)
{
#ifdef __DEBUG
	Log.noticeln3( millis(), F(" - Message arrived ["), topic, F("]") );
		for (uint8_t i = 0; i < length; i++)
	{
		Serial.print((char) payload[i]);
	}
	Serial.println();
#endif

	if( length <= CMD_BUFFER_SIZE )
	{
		// Copy payload to command buffer
		memcpy( (void *)cmdBuf, (void *)payload, length);
		setCommandAvailable(true);
	}
	else
	{
		Log.errorln(F("Command buffer too small"));
	}

}

/**
 * Publishes a message to the specified channel
 *
 */
void PubSubWrapper::publish(char *channel)
{
	pubsub.publish(channel, (char *)cmdBuf);
}

/**
 * Publishes a message to the specified channel
 *
 */
void PubSubWrapper::publish(char *channel, char *buffer)
{
	pubsub.publish(channel, buffer);
}

/**
 * Publishes a message to the specified channel
 *
 */
void PubSubWrapper::publish(char *channel, JsonObject& obj)
{
	//obj.printTo((char *)cmdBuf, CMD_BUFFER_SIZE);
	pubsub.publish( channel, (char *)cmdBuf );
}

/**
 * Returns a pointer to the internal buffer
 *
 */
uint8_t* PubSubWrapper::getBuffer()
{
	return cmdBuf;
}

void PubSubWrapper::setRetryCount(uint8_t c)
{
	retryCount = c;
}

uint8_t PubSubWrapper::getRetryCount()
{
	return retryCount;
}

void PubSubWrapper::setRetryDelay(uint32_t c)
{
	retryDelay = c;
}

uint32_t PubSubWrapper::getRetryDelay()
{
	return retryDelay;
}

void PubSubWrapper::setConnectionStatusCallback(void (*cb)())
{
	this->callbackConnectionStatus = cb;
}

