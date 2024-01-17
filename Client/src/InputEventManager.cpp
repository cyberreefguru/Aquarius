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
    Log.traceln("InputEventManager::initialize - BEGIN");

    esp_err_t status;

    inputArgs.queue_size = 10;
    inputArgs.task_name = "input_el"; // Task will be created
    inputArgs.task_priority = uxTaskPriorityGet(NULL);
    inputArgs.task_stack_size = 2048;
    inputArgs.task_core_id = tskNO_AFFINITY;
    if (esp_event_loop_create(&inputArgs, &inputHandler) != ESP_OK)
    {
        Helper::fatal("InputEventManager::initialize - Unable to create input event loop");
    }
    else
    {
        Log.traceln("InputEventManager::initialize - Created input event loop");
    }

    status = addEventHandler([](void *arg,
                                esp_event_base_t base,
                                int32_t id,
                                void *data)
                             { inputEventManager.defaultEventHandler(arg, base, id, data); });
    if (status != ESP_OK)
    {
        Helper::fatal("InputEventManager::initialize - Error adding input event handler");
    }
    else
    {
        Log.traceln("InputEventManager::initialize - Added event handler!");
    }

    Log.traceln("InputEventManager::initialize - END");
}

esp_err_t InputEventManager::postEvent(ButtonAction action, ButtonEvent *event)
{
    return esp_event_post_to(inputHandler, INPUT_BASE, +action, event, sizeof(ButtonEvent*), 0);
}

esp_err_t InputEventManager::addEventHandler(esp_event_handler_t eventHandler)
{
    return esp_event_handler_register_with(inputHandler, INPUT_BASE, ESP_EVENT_ANY_ID, eventHandler, nullptr);
}

void InputEventManager::defaultEventHandler(void *args, esp_event_base_t base, int32_t id, void *data)
{
    ButtonAction be = (ButtonAction)id;
    ButtonEvent *ba = (ButtonEvent*)data;
}