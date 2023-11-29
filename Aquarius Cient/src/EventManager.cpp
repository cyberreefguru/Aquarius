/*
 * EventManager.cpp
 *
 *  Created on: Nov 20, 2023
 *      Author: cyberreefguru
 */
#include "EventManager.h"

ESP_EVENT_DEFINE_BASE(SYSTEM_EVENT);

EventManager eventManager;

EventManager::EventManager() {}

void EventManager::initialize()
{
    esp_err_t status;

    Log.infoln("Initializing event manager");

    eventLoopArgs.queue_size = 5;
    eventLoopArgs.task_name = "system_loop"; // Task will be created
    eventLoopArgs.task_priority = uxTaskPriorityGet(NULL);
    eventLoopArgs.task_stack_size = 2048;
    eventLoopArgs.task_core_id = tskNO_AFFINITY;
    if (esp_event_loop_create(&eventLoopArgs, &eventLoopHandler) != ESP_OK)
    {
        Log.fatal("Unable to create event loop");
    }
    else
    {
        Log.infoln("Created event loop");
    }

    status = addEventHandler([](void *arg,
                                      esp_event_base_t base,
                                      int32_t id,
                                      void *data)
                                   { eventManager.defaultEventHandler(arg, base, id, data); });
    if (status != ESP_OK)
    {
        Log.fatalln("Error adding event handler");
    }
    else
    {
        Log.infoln("Added event handler!");
    }


    Log.infoln("Event manager initialization complete");
}
esp_err_t EventManager::postEvent(State state)
{
    return esp_event_post_to(eventLoopHandler, SYSTEM_EVENT, +state, nullptr, 0, 0);
}

esp_err_t EventManager::postEvent(Command command)
{
    return esp_event_post_to(eventLoopHandler, SYSTEM_EVENT, +command, nullptr, 0, 0);
}

esp_err_t EventManager::postEvent(Event event)
{
    return esp_event_post_to(eventLoopHandler, SYSTEM_EVENT, +event.getEventType(), nullptr, 0, 0);
}

esp_err_t EventManager::addEventHandler(esp_event_handler_t eventHandler)
{
    return esp_event_handler_register_with(eventLoopHandler, SYSTEM_EVENT, ESP_EVENT_ANY_ID, eventHandler, nullptr);
}

void EventManager::defaultEventHandler(void *args, esp_event_base_t base, int32_t id, void *data)
{
    Log.infoln("System Event: %s", Helper::toString((State)id));
}