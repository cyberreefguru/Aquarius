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
    state = State::INITIALIZING;
    eventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
                                       { stateManager.eventHandler(arg, base, id, data); });
}

void StateManager::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    state = (State)id;
    switch (state)
    {
    case State::ACTIVE:
        indicatorManager.setSystemIndicator(Color::Green);
        break;
    case State::DEACTIVE:
        indicatorManager.setSystemIndicator(Color::Black);
        break;
    case State::WIFI_DOWN:
        wifi = false;
        indicatorManager.setStatusIndicator(Color::Magenta);
        break;
    case State::MQTT_DOWN:
        mqtt = false;
        indicatorManager.setStatusIndicator(Color::Purple);
        break;
    case State::WIFI_UP:
        wifi=true;
        indicatorManager.setStatusIndicator(Color::Blue);
        break;
    case State::MQTT_UP:
        mqtt = true;
        indicatorManager.setStatusIndicator(Color::Blue);
        break;
    case State::RECEIVING:
    case State::PROCESSING:
    case State::SENDING:
        indicatorManager.setStatusIndicator(Color::Blue);
        break;
    case State::INITIALIZING:
        indicatorManager.setStatusIndicator(Color::Orange);
        break;
    case State::WAITING:
        indicatorManager.setStatusIndicator(Color::Green);
        break;
    case State::ERROR:
        indicatorManager.setSystemIndicator(Color::Red);
        break;
    default:
        break;
    }
}

State StateManager::getState()
{
    return state;
}

