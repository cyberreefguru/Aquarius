/*
 * State.cpp
 *
 *  Created on: Nov 20, 2023
 *      Author: cyberreefguru
 */

#include "StateManager.h"

StateManager stateManager;

StateManager::StateManager() {}

void StateManager::initialize()
{
    Log.infoln("Creating state task.");
    BaseType_t xReturned = xTaskCreate(
        [](void *pvParameters)
        { stateManager.stateTask(pvParameters); },
        "state_task",
        2048,
        NULL,
        tskIDLE_PRIORITY + 1,
        &stateTaskHandle);
    if (xReturned != pdPASS)
    {
        Log.errorln("FAILED TO CREATE STATE TASK");
    }
}

void StateManager::stateTask(void *pvParameters)
{
    Log.infoln("Starting state task.");

    startTime = millis(); // Capture current time
    setStateDisplayBase();

    actionEventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
                                       { stateManager.eventHandler(arg, base, id, data); });

    for (;;)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            rssi = WiFi.RSSI();
        }
        if (configure == false)
        {
            setNetworkStatus();
            setUpTime(false);
            setMemory(true);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        // Log.traceln("Status Task Update");
    }
}

void StateManager::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    ActionEvent event = (ActionEvent)id;
    // Log.infoln("StateManager - ActionEvent: %s", ++event);
    switch (event)
    {
    case ActionEvent::INITIALIZING:
        setStatusMessage("Initializing", true);
        break;
    case ActionEvent::WAITING:
        if( lastEvent == ActionEvent::CONFIGURE)
        {
            displayManager.clear();
            setStateDisplayBase();
        }
        setStatusMessage("Waiting", true);
        processing = false;
        configure = false;
        break;
    case ActionEvent::MSG_RECEIVED:
        setStatusMessage("Msg Received", true);
        break;
    case ActionEvent::PROCESSING:
        setStatusMessage("Processing", true);
        processing = true;
        configure = false;
        break;
    case ActionEvent::ACTIVE:
        active = true;
        configure = false;
        break;
    case ActionEvent::DEACTIVE:
        active = false;
        configure = false;
        break;
    case ActionEvent::WIFI_DOWN:
        wifi = false;
        setStatusMessage("WIFI ERROR");
        setNetworkStatus(true);
        break;
    case ActionEvent::WIFI_UP:
        rssi = WiFi.RSSI();
        wifi = true;
        setStatusMessage("WIFI UP");
        setNetworkStatus(true);
        break;
    case ActionEvent::MQTT_DOWN:
        mqtt = false;
        setStatusMessage("MQTT ERROR");
        setNetworkStatus(true);
        break;
    case ActionEvent::MQTT_UP:
        mqtt = true;
        setStatusMessage("MQTT UP");
        setNetworkStatus(true);
        break;
    case ActionEvent::CONFIGURE:
        processing = false;
        configure = true;
    case ActionEvent::NODE_ID_CHANGE:
        setNode(true);
        break;
    case ActionEvent::ERROR:
        setStatusMessage("ERROR", true);
        break;
    default:
        break;
    }
    lastEvent = event;

    // Log.infoln("WIFI: %d, MQTT: %d, RSSI: %d, Processing: %d", wifi, mqtt, rssi, processing);
}

void StateManager::setStateDisplayBase()
{
    Log.traceln("Setting base status display");
    displayManager.clear();
    displayManager.setCursor(0, 0);
    setNode(false);
    setStatusMessage(++ActionEvent::INITIALIZING, false);
    setMemory(false);
    setUpTime(true);
}

void StateManager::setNode(bool refresh)
{
    displayManager.clearRow(NODE_ROW, NODE_COL, NODE_ROW, 8);
    displayManager.setCursor(NODE_ROW, NODE_COL);
    displayManager.print("ID ");
    displayManager.printf("%3.3d", prefManager.getId());
    displayManager.print(": ");
    displayManager.setRefresh(refresh);
}

/**
 * Sets the status message in display buffer.
 * Optionally refreshes the screen.
 */
void StateManager::setStatusMessage(const char *msg, bool refresh)
{
    displayManager.clearRow(STATUS_ROW, STATUS_COL, STATUS_ROW, 21);
    displayManager.setCursor(STATUS_ROW, STATUS_COL);
    displayManager.print(msg);
    displayManager.setRefresh(refresh);
}

/**
 * Sets the network status in the display buffer
 * Optionally refreshes the screen
 */
void StateManager::setNetworkStatus(bool refresh)
{
    displayManager.clearRow(WIFI_ROW);
    if (WIFI_ROW != MQTT_ROW)
    {
        displayManager.clearRow(MQTT_ROW);
    }
    displayManager.setCursor(WIFI_ROW, WIFI_COL);

    displayManager.print("WIFI: ");
    if (wifi == false)
    {
        displayManager.print("Down");
    }
    else
    {
        displayManager.printf("%d", rssi);
    }
    displayManager.setCursor(MQTT_ROW, MQTT_COL);
    displayManager.print("MQTT: ");
    if (mqtt == false)
    {
        displayManager.print("Down");
    }
    else
    {
        displayManager.print("Up");
    }

    displayManager.clearRow(IP_ADDRESS_ROW);
    displayManager.setCursor(IP_ADDRESS_ROW, IP_ADDRESS_COL);
    displayManager.print("IP: ");
    if (wifi == false)
    {
        displayManager.print("0.0.0.0");
    }
    else
    {
        displayManager.print(WiFi.localIP().toString());
    }
    displayManager.setRefresh(refresh);
}

void StateManager::setMemory(bool refresh)
{
    displayManager.clearRow(MEMORY_ROW, MEMORY_COL, MEMORY_ROW, 21);
    displayManager.setCursor(MEMORY_ROW, MEMORY_COL);
    displayManager.print("MEM: ");
    uint32_t m = ESP.getFreeHeap();
    if (m > 10000000)
    {
        displayManager.printf("%d", (m / 1000));
        displayManager.print("K");
    }
    else
    {
        displayManager.printf("%d", m);
    }
    displayManager.setRefresh(refresh);
}

void StateManager::setUpTime(bool refresh)
{
    uint32_t now = millis();
    uint32_t upTime = millis() - startTime;

    uint32_t inSeconds = upTime / 1000;
    uint8_t seconds = inSeconds % 60;
    uint32_t inMins = inSeconds / 60;
    uint8_t mins = inMins % 60;
    uint8_t inHours = inMins / 60;
    uint8_t hours = inHours % 24;
    uint32_t days = inHours / 24;

    char buf[32];
    snprintf(buf, 32, "Uptime:%04dd %02d:%02d:%02d", days, hours, mins, seconds);
    displayManager.clearRow(UPTIME_ROW, UPTIME_COL, UPTIME_ROW, 21);
    displayManager.setCursor(UPTIME_ROW, UPTIME_COL);
    displayManager.print(buf);
    displayManager.setRefresh(refresh);
}