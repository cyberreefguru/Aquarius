/*
 * InputEventManager.cpp
 *
 *  Created on: Nov 20, 2023
 *      Author: cyberreefguru
 */
#include "InputEventManager.h"

ESP_EVENT_DEFINE_BASE(INPUT_BASE);

InputEventManager inputEventManager;

InputEventManager::InputEventManager() {}

void InputEventManager::initialize()
{
    esp_err_t status;

    Log.infoln("Initializing input event manager");

    inputArgs.queue_size = 10;
    inputArgs.task_name = "input_el"; // Task will be created
    inputArgs.task_priority = uxTaskPriorityGet(NULL);
    inputArgs.task_stack_size = 2048;
    inputArgs.task_core_id = tskNO_AFFINITY;
    if (esp_event_loop_create(&inputArgs, &inputHandler) != ESP_OK)
    {
        Log.fatalln("Unable to create input event loop");
    }
    else
    {
        Log.infoln("Created input event loop");
    }

    status = addEventHandler([](void *arg,
                                esp_event_base_t base,
                                int32_t id,
                                void *data)
                             { inputEventManager.defaultEventHandler(arg, base, id, data); });
    if (status != ESP_OK)
    {
        Log.fatalln("Error adding input event handler");
    }
    else
    {
        Log.infoln("Added event handler!");
    }

    Log.infoln("input event manager initialization complete");
}

esp_err_t InputEventManager::postEvent(ButtonEvent event, ButtonAction *action)
{
    return esp_event_post_to(inputHandler, INPUT_BASE, +event, action, sizeof(ButtonAction), 0);
}

esp_err_t InputEventManager::addEventHandler(esp_event_handler_t eventHandler)
{
    return esp_event_handler_register_with(inputHandler, INPUT_BASE, ESP_EVENT_ANY_ID, eventHandler, nullptr);
}

void InputEventManager::defaultEventHandler(void *args, esp_event_base_t base, int32_t id, void *data)
{
    ButtonEvent be = (ButtonEvent)id;
    ButtonAction *ba = (ButtonAction*)data;
    Log.infoln("IEM - Event: %s, Action: %s", ++be, ++(*ba));
}