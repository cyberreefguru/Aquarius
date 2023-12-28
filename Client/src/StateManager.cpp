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
    eventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
                                       { stateManager.eventHandler(arg, base, id, data); });

    Log.infoln("Creating state task.");
    BaseType_t xReturned = xTaskCreate(
        [](void *pvParameters)
        { stateManager.stateTask(pvParameters); },
        "state_task",
        1024,
        NULL,
        tskIDLE_PRIORITY+1,
        &stateTaskHandle);
    if (xReturned != pdPASS)
    {
        Log.errorln("FAILED TO CREATE STATE TASK");
    }
}

void StateManager::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    Event event = (Event)id;
    // Log.infoln("StateManager - Event: %s", Helper::toString(event));
    lastEvent = event;
    switch (event)
    {
    case Event::WAITING:
        processing = false;
        break;
    case Event::PROCESSING:
        processing = true;
        break;
    case Event::ACTIVE:
        active = true;
        break;
    case Event::DEACTIVE:
        active = false;
        break;
    case Event::WIFI_DOWN:
        wifi = false;
        break;
    case Event::WIFI_UP:
        rssi = WiFi.RSSI();
        wifi=true;
        break;
    case Event::MQTT_DOWN:
        mqtt = false;
        break;
    case Event::MQTT_UP:
        mqtt = true;
        break;
    default:
        break;
    }
    // Log.infoln("WIFI: %d, MQTT: %d, RSSI: %d, Processing: %d", wifi, mqtt, rssi, processing);
}

void StateManager::stateTask(void *pvParameters)
{
    Log.infoln("Starting state task.");
    for (;;)
    {
        if( WiFi.status() == WL_CONNECTED )
        {
            rssi = WiFi.RSSI();
            // Log.infoln("WIFI: %d, MQTT: %d, RSSI: %d, Processing: %d", wifi, mqtt, rssi, processing);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
