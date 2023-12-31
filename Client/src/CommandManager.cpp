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
    actionEventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
                                 { commandManager.eventHandler(arg, base, id, data); });

    Log.infoln("Creating queue");
    commandQueueHandle = xQueueCreate(5, CMD_MAX_SIZE);
    if (commandQueueHandle == NULL)
    {
        Helper::fatal("Failed to create command queue");
    }

    Log.infoln("Creating command task.");
    BaseType_t xReturned = xTaskCreate(
        [](void *pvParameters)
        { commandManager.commandTask(pvParameters); },
        "command_task",
        2048,
        NULL,
        tskIDLE_PRIORITY+1,
        &commandTaskHandle);
    if (xReturned != pdPASS)
    {
        Helper::fatal("FAILED TO CREATE COMMAND TASK");
    }
}

void CommandManager::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    ActionEvent event = (ActionEvent)id;
    // Log.infoln("Command Manager: %s", ++event);
    switch (event)
    {
    case ActionEvent::MSG_RECEIVED:
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
            actionEventManager.postEvent(ActionEvent::PROCESSING);
            Command c = Command();
            c.toJson(eventData);
            Log.traceln("Parsed command");

            CommandType t = c.getType();
            ActionType a = c.getAction();
            Log.infoln("Command Type: %d, '%s'", t, ++t);
            Log.infoln("Action Type: %d, '%s'", a, ++a);
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
            Log.traceln("Post waiting");
            actionEventManager.postEvent(ActionEvent::WAITING);
            Log.infoln("Command Task Memory: %d", uxTaskGetStackHighWaterMark(NULL));
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
    Log.infoln("Action: %s", ++a);
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
