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
}

void CommandManager::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    State state = (State)id;
    switch (state)
    {
    case State::RECEIVING:
    case State::PROCESSING:
    case State::SENDING:
        break;
    case State::WAITING:
        break;
    case State::ERROR:
        break;
    default:
        break;
    }
}

void CommandManager::commandTask(void *pvParameters)
{
    Log.infoln("Starting command task.");

    // Wait until command loaded into queue

    // Decode command

    // Execute command

    // Send Ack
}

