/**
 * @brief Handles incoming and outgong commands
 * @file CommandManager.cpp
 * @date Nov 20, 2023
 * @author cyberreefguru
 */
#include "CommandManager.h"
#include <ArduinoJson.h>
#include "ActionEvent.h"
#include "ActionEventManager.h"

CommandManager commandManager;

CommandManager::CommandManager() {}

/**
 * @brief initializes the manager
 */
void CommandManager::initialize()
{
    Log.traceln("CommandManager::initialize - BEGIN");

    actionEventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
                                       { commandManager.eventHandler(arg, base, id, data); });

    commandQueueHandle = xQueueCreate(5, CMD_MAX_SIZE);
    if (commandQueueHandle == NULL)
    {
        Helper::fatal("CommandManager::initialize - failed to create command queue");
    }
    else
    {
        Log.traceln("CommandManager::initialize - Queue created! Creating command task...");
    }

    BaseType_t xReturned = xTaskCreate(
        [](void *pvParameters)
        { commandManager.commandTask(pvParameters); },
        "command_task",
        2048,
        NULL,
        tskIDLE_PRIORITY + 1,
        &commandTaskHandle);
    if (xReturned != pdPASS)
    {
        Helper::fatal("CommandManager::initialize - FAILED TO CREATE COMMAND TASK");
    }
    Log.traceln("CommandManager::initialize - END");
}

/**
 * @brief Handles message events
 * @param arg
 * @param base
 * @param id
 * @param data
 */
void CommandManager::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    ActionEvent event = (ActionEvent)id;
    //Log.infoln("CommandManager::eventHandler - %s", ++event);

    switch (event)
    {
    case ActionEvent::MSG_RECEIVED:
        if (data == nullptr)
        {
            Log.errorln("CommandManager::eventHandler - data pointer is null!");
        }
        else
        {
            Log.traceln("CommandManager::eventHandler - message: '%s'", data);
            if (xQueueSend(commandQueueHandle, data, portMAX_DELAY) != pdPASS)
            {
                Log.errorln("CommandManager::eventHandler - unable to send message to queue!");
            }
            else
            {
                Log.traceln("CommandManager::eventHandler - sent message to queue!");
            }
        }
        break;
    case ActionEvent::COMMAND_COMPLETE:
        actionEventManager.postEvent(ActionEvent::WAITING);
        break;
    case ActionEvent::RESPONSE_COMPLETE:
        actionEventManager.postEvent(ActionEvent::WAITING);
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
            Log.traceln("CommandManager::commandTask - command received: '%s'", eventData);
            //actionEventManager.postEvent(ActionEvent::MSG_RECEIVED);
            Command c = Command();
            c.parse(eventData);
            Log.traceln("Parsed command");

            CommandType t = c.getType();
            ActionType a = c.getAction();
            Log.infoln("CommandManager::commandTask - Command: %d, '%s', Action: %d, '%s'", t, ++t, a, ++a);
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
            // vTaskDelay(5000);
            // Log.traceln("CommandManager::commandTask - post waiting");
            // actionEventManager.postEvent(ActionEvent::WAITING);
            Log.infoln("CommandManager::commandTask - Command Task Memory: %d", uxTaskGetStackHighWaterMark(NULL));
        }
        // vTaskDelay(5000);
    }
    // Wait until command loaded into queue

    // Decode command

    // Execute command

    // Send Ack
}
/**
 * @brief Performs the action directed by the command
 * @param c the command
 * @note does NOT send command complete or waiting event
 */
void CommandManager::doAction(Command &c)
{
    ActionType a = c.getAction();
    Log.infoln("CommandManager::doAction - action: '%s'", ++a);
    switch (a)
    {
    case ActionType::ACTIVATE:
        actionEventManager.postEvent(ActionEvent::ACTIVE);
        break;
    case ActionType::DEACTIVATE:
        actionEventManager.postEvent(ActionEvent::DEACTIVE);
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
    actionEventManager.postEvent(ActionEvent::RESPONSE_COMPLETE);
}

void CommandManager::doLog(Command &c)
{
    actionEventManager.postEvent(ActionEvent::WAITING);
}

void CommandManager::parse()
{
    StaticJsonDocument<CMD_MAX_SIZE> cmd;
    Log.infoln("message: %s", eventData);
}
