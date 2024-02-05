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
    Log.traceln("StateManager::initialize - creating state task.");
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
        Helper::fatal("StateManager::initialize - FAILED TO CREATE STATE TASK");

    }
}

/**
 * @brief Updates state variables and display periodically
 * @param pvParameters
 */
void StateManager::stateTask(void *pvParameters)
{
    Log.traceln("StateManager::stateTask - starting state task.");

    // Initialize start time
    startTime = millis(); // Capture current time

    // Add event handler
    actionEventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
                                       { stateManager.eventHandler(arg, base, id, data); });

    for (;;)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            rssi = WiFi.RSSI();
        }
        else
        {
            rssi = 0;
        }
        if (displayState == DisplayState::DETAILED || displayState == DisplayState::LARGE)
        {
            displayManager.setRefresh(true); // refresh every 1 second if we're in state mode
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
 * @brief Receives system events and sets appropriate flags for future reference
 * @param arg
 * @param base
 * @param id the event triggering this handler
 * @param data
 */
void StateManager::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    ActionEvent event = (ActionEvent)id;

    switch (event)
    {
    case ActionEvent::INITIALIZING:
        // processing = false;
        // configure = false;
        break;
    case ActionEvent::WAITING:
        processing = false;
        displayState = DisplayState::DETAILED;
        // configure = false;
        break;
    case ActionEvent::MSG_RECEIVED:
        break;
    case ActionEvent::PROCESSING:
        processing = true;
        // configure = false;
        break;
    case ActionEvent::ACTIVE:
        active = true;
        // configure = false;
        break;
    case ActionEvent::DEACTIVE:
        active = false;
        // configure = false;
        break;
    case ActionEvent::WIFI_DOWN:
        wifi = false;
        mqtt = false;
        processing = false;
        break;
    case ActionEvent::WIFI_UP:
        wifi = true;
        break;
    case ActionEvent::MQTT_DOWN:
        mqtt = false;
        processing = false;
        break;
    case ActionEvent::MQTT_UP:
        mqtt = true;
        processing = false;
        break;
    case ActionEvent::CONFIGURE:
        displayState = DisplayState::MENU;
        displayManager.setRefresh(true);
        // configure = true;
        break;
    case ActionEvent::NODE_ID_CHANGE:
        // setNode(true);
        break;
    case ActionEvent::ERROR:
        // setStatusMessage("ERROR", true);
        break;
    default:
        break;
    }
    lastEvent = event;
    if (displayState == DisplayState::DETAILED || displayState == DisplayState::LARGE)
    {
        displayManager.setRefresh(true); // refresh every 1 second if we're in state mode
    }
    // Log.traceln("WIFI: %d, MQTT: %d, RSSI: %d, Processing: %d", wifi, mqtt, rssi, processing);
}

/**
 * @brief displays current state information
 *
 */
void StateManager::display()
{
    switch (displayState)
    {
    case DisplayState::DETAILED:
        displayDetail();
        break;
    case DisplayState::LARGE:
        displayLarge();
        break;
    }
}

/**
 * @brief displays current state information
 *
 */
void StateManager::displayDetail()
{
    displayManager.clear();
    displayManager.setTextColor(WHITE, WHITE);
    setNode();
    setStatusMessage();
    setNetworkStatus();
    setMemory();
    setUpTime(true);
}

/**
 * @brief displays current state information
 *
 */
void StateManager::displayLarge()
{
}

/**
 * @brief prints node id to screen
 * @param refresh
 */
void StateManager::setNode(bool refresh)
{
    displayManager.clearRow(NODE_ROW, NODE_COL, NODE_ROW, 8);
    displayManager.setCursor(NODE_ROW, NODE_COL);
    displayManager.print("ID ");
    displayManager.printf("%3.3d", prefManager.getNodeId());
    displayManager.print(": ");
    displayManager.setRefresh(refresh);
}

/**
 * Sets the status message in display buffer.
 * Optionally refreshes the screen.
 */
void StateManager::setStatusMessage(bool refresh)
{
    displayManager.clearRow(STATUS_ROW, STATUS_COL, STATUS_ROW, 21);
    displayManager.setCursor(STATUS_ROW, STATUS_COL);
    displayManager.print(++stateManager.lastEvent);
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
    if (stateManager.wifi == false)
    {
        displayManager.print("Down");
    }
    else
    {
        displayManager.printf("%d", stateManager.rssi);
    }
    displayManager.setCursor(MQTT_ROW, MQTT_COL);
    displayManager.print("MQTT: ");
    if (stateManager.mqtt == false)
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
    if (stateManager.wifi == false)
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
    uint32_t upTime = millis() - stateManager.startTime;

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