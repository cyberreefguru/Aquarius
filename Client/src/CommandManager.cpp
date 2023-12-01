/*
 * CommandManager.cpp
 *
 *  Created on: Nov 20, 2023
 *      Author: cyberreefguru
 */

#include "CommandManager.h"

CommandManager commandManager;

CommandManager::CommandManager() {}

void CommandManager::initialize()
{
    eventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
                                 { commandManager.eventHandler(arg, base, id, data); });

    Log.infoln("Creating queue");
    commandQueueHandle = xQueueCreate(5, CMD_MAX_SIZE);
    if (commandQueueHandle == NULL)
    {
        Log.fatalln("Failed to create command queue");
        eventManager.postEvent(Event::ERROR);
        while (1)
            ;
    }

    Log.infoln("Creating command task.");
    BaseType_t xReturned = xTaskCreate(
        [](void *pvParameters)
        { commandManager.commandTask(pvParameters); },
        "command_task",
        2048,
        (void *)1,
        tskIDLE_PRIORITY,
        &commandTaskHandle);
    if (xReturned != pdPASS)
    {
        Log.errorln("FAILED TO CREATE COMMAND TASK");
    }
}

void CommandManager::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    Event event = (Event)id;
    // Log.infoln("Command Manager: %s", Helper::toString(event));
    switch (event)
    {
    case Event::MSG_RECEIVED:
        Log.infoln("message: %s", data);
        if (xQueueSend(commandQueueHandle, data, portMAX_DELAY) != pdPASS)
        {
            Log.errorln("Unable to send message to queue!");
        }
        else
        {
            Log.infoln("Sent message to queue!");
        }
        break;
    default:
        break;
    }
}

void CommandManager::commandTask(void *pvParameters)
{
    Log.infoln("Starting command task.");

    while (1)
    {
        if (xQueueReceive(commandQueueHandle, &eventData, portMAX_DELAY) == pdPASS)
        {
            Log.infoln("Command received: %s", eventData);
            eventManager.postEvent(Event::PROCESSING);
            Command c = Command();
            Log.infoln("Created command; parsing");
            c.toJson(eventData);
            Log.infoln("Parsed command");

            CommandType t = c.getType();
            ActionType a = c.getAction();
            Log.infoln("Command Type: %d, '%s'", t, Helper::toString(t));
            Log.infoln("Action Type: %d, '%s'", a, Helper::toString(a));
            switch (t)
            {
            case CommandType::ACTION:
                doAction(c);
                break;
            case CommandType::RESPONSE:
                doResponse(c);
                break;
            case CommandType::LOG:
                doLog(c);
                break;
            }
            vTaskDelay(5000);
            Log.infoln("Posting waiting");
            eventManager.postEvent(Event::WAITING);
        }
        // vTaskDelay(5000);
    }
    // Wait until command loaded into queue

    // Decode command

    // Execute command

    // Send Ack
}

void CommandManager::doAction(Command &c)
{
    ActionType a = c.getAction();
    Log.infoln("Action: %s", Helper::toString(a));
    switch (a)
    {
    case ActionType::ACTIVATE:
        break;
    case ActionType::DEACTIVATE:
        break;
    case ActionType::GET_PARAM:
        break;
    case ActionType::SET_PARAM:
        break;
    case ActionType::GET_STATUS:
        break;
    case ActionType::REGISTER:
        break;
    }
}

void CommandManager::doResponse(Command &c)
{
}

void CommandManager::doLog(Command &c)
{
}

void CommandManager::parse()
{
    StaticJsonDocument<CMD_MAX_SIZE> cmd;
    Log.infoln("message: %s", eventData);
}
