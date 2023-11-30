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
        (void *)1,
        tskIDLE_PRIORITY,
        &stateTaskHandle);
    if (xReturned != pdPASS)
    {
        Log.errorln("FAILED TO CREATE STATE TASK");
    }
}

void StateManager::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    Event event = (Event)id;
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
        wifi=true;
        rssi = WiFi.RSSI();
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
}

void StateManager::stateTask(void *pvParameters)
{
    Log.infoln("Starting state task.");
    uint32_t time = millis();
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        rssi = WiFi.RSSI();
    }
}
