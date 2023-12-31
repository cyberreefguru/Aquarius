/*
 * MenuManager.cpp
 *
 *  Created on: Dec  30, 2023
 *      Author: cyberreefguru
 */
#include "MenuManager.h"

MenuManager menuManager;

MenuManager::MenuManager() {}

void MenuManager::initialize()
{
    esp_err_t status;

    Log.infoln("Initializing menu manager");

    status = inputEventManager.addEventHandler([](void *arg,
                                                  esp_event_base_t base,
                                                  int32_t id,
                                                  void *data)
                                               { menuManager.eventHandler(arg, base, id, data); });
    if (status != ESP_OK)
    {
        Log.fatalln("Error adding event handler");
    }
    else
    {
        Log.infoln("Added input event handler!");
    }

    Log.infoln("menu manager initialization complete");
}

void MenuManager::eventHandler(void *args, esp_event_base_t base, int32_t id, void *data)
{
    currentEvent = (ButtonEvent)id;
    currentAction = *((ButtonAction *)data);

    Log.infoln("MM - Event: %s, Action: %s, Mode: %d, State: %d", ++currentEvent, ++currentAction, stateManager.configure, state);

    if (currentEvent == ButtonEvent::PRESS)
    {
        if (stateManager.processing == false && stateManager.configure == false)
        {
            // We have a button event, we're not doing anything, and we're not already in memu mode
            actionEventManager.postEvent(ActionEvent::CONFIGURE);
            displayMainMenu();
        }
        else if (stateManager.configure == true)
        {
            // We are in configure mode -- process button action
            displayMainMenu();
            // if (state == 0)
            // {
            //     displayMainMenu();
            // }
        }
        else
        {
            Log.traceln("UNHANDLED CONDITION");
        }
    }
}

void MenuManager::displayMainMenu()
{
    Log.traceln("Main Menu: state=%d, ln=%d", state, activeLineNum);
    if (state == 0)
    {
        state = 1; // Enter main menu state
        activeLineNum = 1;
    }
    else
    {
        if (currentAction == ButtonAction::DOWN)
        {
            if (activeLineNum == 5)
            {
                activeLineNum = 1;
            }
            else
            {
                activeLineNum++;
            }
        }
        else if (currentAction == ButtonAction::UP)
        {
            if (activeLineNum == 1)
            {
                activeLineNum = 5;
            }
            else
            {
                activeLineNum--;
            }
        }
        else if (currentAction == ButtonAction::PUSH)
        {
            // Figure out next state
            // Perhaps a series of menu item objects makes sense
            Log.traceln("Button pushed");
            if (activeLineNum == 5)
            {
                state = 0;
                displayManager.setTextColor(WHITE, WHITE);
                displayManager.clear();
                displayManager.setRefresh(true);
                actionEventManager.postEvent(ActionEvent::WAITING);
            }
        }
    }
    displayManager.clear();
    if (changed)
        print(0, "Main Menu*", true);
    else
        print(0, "Main Menu", true);

    print(1, "> Node ID", true);
    print(2, "> Actions", true);
    print(3, "> Settings", true);
    print(4, "> Save", true);
    print(5, "> Exit", false);

    displayManager.setRefresh(true);
}

void MenuManager::print(uint8_t curLine, const char *m, bool nl)
{
    Log.traceln("cl=%d, ln=%d, nl=%d, m=%s", curLine, activeLineNum, nl, m);
    if (curLine == activeLineNum)
    {
        displayManager.setTextColor(BLACK, WHITE);
    }
    else
    {
        displayManager.setTextColor(WHITE);
    }
    displayManager.setCursor(curLine, 0);
    displayManager.print(m);
}
