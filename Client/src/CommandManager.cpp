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

    commandQueueHandle = xQueueCreate(10, sizeof(bool));
    if (commandQueueHandle == NULL)
    {
        Log.fatalln("Failed to create command queue");
        for (;;)
            ;
    }

    Log.infoln("Creating flash task.");
    BaseType_t xReturned = xTaskCreate(
        [](void *pvParameters)
        { commandManager.commandTask(pvParameters); },
        "flash_task",
        1024,
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
        Log.infoln("Message Received");
        if (xQueueSend(commandQueueHandle,
                       (void *)&cmd,
                       (TickType_t)10) != pdPASS)
        {
            /* Failed to post the message, even after 10 ticks. */
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
        if( xQueueReceive( commandQueueHandle,
                         &(cmd),
                         ( TickType_t ) 10 ) == pdPASS )
      {
        Log.infoln("Posting processing");
        eventManager.postEvent(Event::PROCESSING);
        vTaskDelay(5000);
        Log.infoln("Posting waiting");
        eventManager.postEvent(Event::WAITING);

      }
    }
    // Wait until command loaded into queue

    // Decode command

    // Execute command

    // Send Ack
}
