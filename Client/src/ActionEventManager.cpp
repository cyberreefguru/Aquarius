/*
 * ActionEventManager.cpp
 *
 *  Created on: Nov 20, 2023
 *      Author: cyberreefguru
 */
#include "ActionEventManager.h"

ESP_EVENT_DEFINE_BASE(ACTION_BASE);

ActionEventManager actionEventManager;

ActionEventManager::ActionEventManager() {}

void ActionEventManager::initialize()
{
    Log.traceln("ActionEventManager::initialize - BEGIN");

    esp_err_t status;

    eventLoopArgs.queue_size = 5;
    eventLoopArgs.task_name = "event_loop"; // Task will be created
    eventLoopArgs.task_priority = uxTaskPriorityGet(NULL);
    eventLoopArgs.task_stack_size = 2048;
    eventLoopArgs.task_core_id = tskNO_AFFINITY;
    if (esp_event_loop_create(&eventLoopArgs, &eventLoopHandler) != ESP_OK)
    {
        Log.fatalln("ActionEventManager::initialize - Unable to create event loop");
    }
    else
    {
        Log.traceln("ActionEventManager::initialize - Created event loop");
    }

    status = addEventHandler([](void *arg,
                                esp_event_base_t base,
                                int32_t id,
                                void *data)
                             { actionEventManager.defaultEventHandler(arg, base, id, data); });
    if (status != ESP_OK)
    {
        Log.fatalln("ActionEventManager::initialize - Error adding event handler");
    }
    else
    {
        Log.traceln("ActionEventManager::initialize - Added event handler!");
    }

    Log.traceln("ActionEventManager::initialize - END");
}

esp_err_t ActionEventManager::postInterruptEvent(ActionEvent event)
{
    return esp_event_post_to(eventLoopHandler, ACTION_BASE, +event, nullptr, 0, 0);
}

esp_err_t ActionEventManager::postEvent(ActionEvent event)
{
    return esp_event_post_to(eventLoopHandler, ACTION_BASE, +event, nullptr, 0, 0);
}

esp_err_t ActionEventManager::postEvent(ActionEvent event, char* payload, uint32_t size)
{
    return esp_event_post_to(eventLoopHandler, ACTION_BASE, +event, payload, size, 0);
}

esp_err_t ActionEventManager::addEventHandler(esp_event_handler_t eventHandler)
{
    return esp_event_handler_register_with(eventLoopHandler, ACTION_BASE, ESP_EVENT_ANY_ID, eventHandler, nullptr);
}

void ActionEventManager::defaultEventHandler(void *args, esp_event_base_t base, int32_t id, void *data)
{
    Log.infoln("ActionEventManager::defaultEventHandler - %s", ++((ActionEvent)id));
}