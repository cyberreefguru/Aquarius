/*
 * WifiWrapper.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: tsasala
 */

#include "WifiWrapper.h"

// #define WIFI_SSID "aquarius"
// #define WIFI_PASS "imsecure"
#define WIFI_SSID "IOT_Down"
#define WIFI_PASS "code5541iot"

WifiWrapper::WifiWrapper()
{
}

/**
 * Initializes the WIFI module
 *
 */
WifiStatusCode WifiWrapper::initialize()
{
	uint8_t retry = 0;

	WifiStatusCode status = WifiStatusCode::UNKNOWN;

	Log.noticeln(F("Initializing WIFI..."));

	// If connected, reset connection
	uint8_t ws = WiFi.status();
	Log.noticeln(F("Current Connection Status: "), toStringWifiCode(ws));
	if (ws == WL_CONNECTED)
	{
		Log.warningln(F("Disconnecting current session..."));
		WiFi.disconnect();
	}

	// Connect to specified network
	Log.noticeln(F("Connecting to "), WIFI_SSID);

	// We start by connecting to a WiFi network
	// WiFi.setRetryCount( config->getWifiTries() );

	// NOTE - I changed the routine to implement a callback so it doens't block if callback is defined
	WiFi.begin(WIFI_SSID, WIFI_PASS);

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(retryDelay);
		Log.infoln(".");
		retry++;
		if (retry > retryCount)
		{
			Log.errorln("Unable to connect to wifi");
			status = WifiStatusCode::CONNECTION_FAILED;
			return status;
		}
	}

	status = toWifiStatusCode(WiFi.status());
	if (status == WifiStatusCode::CONNECTED)
	{
		Log.noticeln(F(" Connected: "), WiFi.localIP());
	}
	else
	{
		Log.errorln(F("Failed to connect: "), toStringWifiCode(WiFi.status()));
	}
	return status;
}

/**
 * Returns the WIFI Client
 *
 */
WiFiClient &WifiWrapper::getWifiClient()
{
	return wifi;
}

uint8_t WifiWrapper::connected()
{
	return (WiFi.status() == WL_CONNECTED);
}

void WifiWrapper::work()
{
	// ArduinoOTA.handle();
}

IPAddress WifiWrapper::getIpAddress()
{
	return WiFi.localIP();
}

void WifiWrapper::setRetryCount(uint8_t c)
{
	retryCount = c;
}

uint8_t WifiWrapper::getRetryCount()
{

	return retryCount;
}

void WifiWrapper::setRetryDelay(uint32_t c)
{
	retryDelay = c;
}

uint32_t WifiWrapper::getRetryDelay()
{
	return retryDelay;
}

/**
 * Sets the status update callback function pointer
 */
void WifiWrapper::setConnectionStatusCallback(void (*cb)())
{
	// WiFi.setConnectionStatusCallback(cb);
}

// /**
//  * Sets the status update callback function pointer
//  */
// void WifiWrapper::setAccessPointStatusCallback(void (*cb)())
// {
// 	// WiFi.setAccessPointStatusCallback(cb);
// }

// /**
//  * Sets the status update callback function pointer
//  */
// void WifiWrapper::setScanStatusCallback(void (*cb)())
// {
// 	// WiFi.setScanStatusCallback(cb);
// }

WifiStatusCode WifiWrapper::toWifiStatusCode(uint8_t s)
{
	WifiStatusCode status = WifiStatusCode::UNKNOWN;
	switch (s)
	{
	case WL_IDLE_STATUS:
		status = WifiStatusCode::IDLE;
		break;
	case WL_CONNECTED:
		status = WifiStatusCode::CONNECTED;
		break;
	case WL_DISCONNECTED:
		status = WifiStatusCode::DISCONNECTED;
		break;
	case WL_SCAN_COMPLETED:
		status = WifiStatusCode::SCAN_COMPLETE;
		break;
	case WL_CONNECTION_LOST:
		status = WifiStatusCode::CONNECTION_LOST;
		break;
	case WL_CONNECT_FAILED:
		status = WifiStatusCode::CONNECTION_FAILED;
		break;
	case WL_NO_SSID_AVAIL:
		status = WifiStatusCode::NO_SSID;
		break;
	default:
		break;
	}
	return status;
}

void WifiWrapper::printWiFiStatus()
{
	// print the SSID of the network you're attached to:
	Log.infoln(F("SSID: "), WiFi.SSID());

	// print your WiFi shield's IP address:
	Log.infoln(F("IP Address  : "), WiFi.localIP());
	// print your WiFi shield's gateway:

	Log.infoln(F("IP Gateway  : "), WiFi.gatewayIP());

	// print your WiFi shield's gateway:
	Log.infoln(F("Subnet Mask : "), WiFi.subnetMask());

	// My ip address
	Log.infoln(F("IP Address"), WiFi.localIP());
}

String WifiWrapper::toString(WifiStatusCode c)
{
	String s = "";
	switch (c)
	{
	case WifiStatusCode::IDLE:
		s = String(F("IDLE"));
		break;
	case WifiStatusCode::CONNECTED:
		s = String(F("CONNECTED"));
		break;
	case WifiStatusCode::DISCONNECTED:
		s = String(F("DISCONNECTED"));
		break;
	case WifiStatusCode::SCAN_COMPLETE:
		s = String(F("SCAN COMPLETE"));
		break;
	case WifiStatusCode::AP_LISTENING:
		s = String(F("AP LISTENING"));
		break;
	case WifiStatusCode::AP_CONNECTED:
		s = String(F("AP CONNECTED"));
		break;
	case WifiStatusCode::AP_FAILED:
		s = String(F("AP FAILED"));
		break;
	case WifiStatusCode::CONNECTION_LOST:
		s = String(F("CONNECTION LOST"));
		break;
	case WifiStatusCode::CONNECTION_FAILED:
		s = String(F("CONNECT FAILED"));
		break;
	case WifiStatusCode::NO_SSID:
		s = String(F("NO SSID"));
		break;
	case WifiStatusCode::NO_PASSWORD:
		s = String(F("NO PASSWORD"));
		break;
	case WifiStatusCode::NO_MODULE:
		s = String(F("NO MODULE"));
		break;
	case WifiStatusCode::OTA_AUTH_ERROR:
		s = String(F("OTA AUTHORIZATION ERROR"));
		break;
	case WifiStatusCode::OTA_CONNECTION_ERROR:
		s = String(F("OTA CONNECTION ERROR"));
		break;
	case WifiStatusCode::OTA_RECEIVE_ERROR:
		s = String(F("OTA RECEIVE ERROR"));
		break;
	case WifiStatusCode::OTA_END_ERROR:
		s = String(F("OTA END ERROR"));
		break;
	case WifiStatusCode::UNKNOWN:
		s = String(F("UNKNOWN"));
		break;
	default:
		break;
	}
	return s;
}

String WifiWrapper::toStringWifiCode(uint8_t c)
{
	String s = "";
	switch (c)
	{
	case WL_IDLE_STATUS:
		s = String(F("WL_IDLE_STATUS"));
		break;
	case WL_NO_SSID_AVAIL:
		s = String(F("WL_NO_SSID_AVAIL"));
		break;
	case WL_SCAN_COMPLETED:
		s = String(F("SCAN WL_SCAN_COMPLETED"));
		break;
	case WL_CONNECTED:
		s = String(F("WL_CONNECTED"));
		break;
	case WL_CONNECT_FAILED:
		s = String(F("WL_CONNECT_FAILED"));
		break;
	case WL_CONNECTION_LOST:
		s = String(F("WL_CONNECTION_LOST"));
		break;
	case WL_DISCONNECTED:
		s = String(F("WL_DISCONNECTED"));
		break;
	default:
		break;
	}
	return s;
}
