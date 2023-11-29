/*
 * WifiWrapper.h
 *
 *  Created on: Feb 22, 2016
 *      Author: tsasala
 */

#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ArduinoLog.h>

enum class WifiStatusCode
{
    IDLE,
    CONNECTED,
    DISCONNECTED,
    SCAN_COMPLETE,
    AP_LISTENING,
    AP_CONNECTED,
    AP_FAILED,
    NO_MODULE,
    CONNECTION_FAILED,
    CONNECTION_LOST,
    NO_SSID,
    NO_PASSWORD,
    OTA_AUTH_ERROR,
    OTA_CONNECTION_ERROR,
    OTA_RECEIVE_ERROR,
    OTA_END_ERROR,
    NO_CONFIG,
    UNKNOWN
};


class WifiWrapper
{
public:
    /** Constructor */
    WifiWrapper();

    /** Initializes the class */
    WifiStatusCode initialize();

    /** Gets the WIFI client (necessary for MQTT) */
    WiFiClient &getWifiClient();

    /** Returns true if connected, false otherwise */
    uint8_t connected();

    /** Returns our IP Address */
    IPAddress getIpAddress();

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
     * Sets the time duration to wait until restarting the connection process again
     */
    void setRetryTimeout(uint32_t c);

    /**
     * Gets the time duration before restarting the connection process
     */
    uint32_t getRetryDelay();

    /**
     * Sets the status update callback function pointer
     */
    void setConnectionStatusCallback(void (*cb)());

    // /**
    //  * Sets the status update callback function pointer
    //  */
    // void setAccessPointStatusCallback(void (*cb)());

    // /**
    //  * Sets the status update callback function pointer
    //  */
    // void setScanStatusCallback(void (*cb)());

    /**
     * Function that performs any necessary network work during "break" times
     *
     */
    void work();

    WifiStatusCode toWifiStatusCode(uint8_t s);
    String toString(WifiStatusCode c);
    String toStringWifiCode(uint8_t c);

    static void printWiFiStatus();

protected:
    WiFiClient wifi;
    uint32_t retryDelay = 500;
    uint32_t retryTimeout = 10*1000;
    uint8_t retryCount = 10;
    
    // Configuration* config;
    // WifiStatusCode configureWifi();
};

// end of add your includes here
#ifdef __cplusplus
extern "C"
{
#endif

    extern void wifiStatusCallback();

#ifdef __cplusplus
} // extern "C"
#endif
