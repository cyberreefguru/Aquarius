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

    status = actionEventManager.addEventHandler([](void *arg,
                                                   esp_event_base_t base,
                                                   int32_t id,
                                                   void *data)
                                                { menuManager.actionEventHandler(arg, base, id, data); });
    if (status != ESP_OK)
    {
        Log.fatalln("Error adding action event handler");
    }
    else
    {
        Log.infoln("Added action event handler!");
    }

    status = inputEventManager.addEventHandler([](void *arg,
                                                  esp_event_base_t base,
                                                  int32_t id,
                                                  void *data)
                                               { menuManager.inputEventHandler(arg, base, id, data); });
    if (status != ESP_OK)
    {
        Log.fatalln("Error adding input event handler");
    }
    else
    {
        Log.infoln("Added input event handler!");
    }

    Log.infoln("menu manager initialization complete");
}

void MenuManager::actionEventHandler(void *args, esp_event_base_t base, int32_t id, void *data)
{
    ActionEvent ae = (ActionEvent)id;

    if (ae == ActionEvent::CONFIGURE)
    {
        Log.infoln("MM - Setting configure");
        state = 0;
        stateManager.configure = true;
        display();
    }
}

void MenuManager::inputEventHandler(void *args, esp_event_base_t base, int32_t id, void *data)
{
    currentEvent = (ButtonEvent)id;
    currentAction = *((ButtonAction *)data);

    Log.infoln("MM - InputEvent: %s, Action: %s, Mode: %d, State: %d", ++currentEvent, ++currentAction, stateManager.configure, state);

    if (currentEvent == ButtonEvent::PRESS)
    {
        if (stateManager.processing == false && stateManager.configure == false)
        {
            // We have a button event, we're not doing anything, and we're not already in memu mode
            actionEventManager.postEvent(ActionEvent::CONFIGURE);
        }
        else if (stateManager.configure == true)
        {
            if (currentAction == ButtonAction::PUSH)
            {
                if (activeLineNum == 5)
                {
                    state = 0;
                    displayManager.clear();
                    actionEventManager.postEvent(ActionEvent::WAITING);
                    // return;
                }
                else
                {
                display();
                }
            }
            else
            {
            display();

            }

        }
        else
        {
            Log.traceln("UNHANDLED CONDITION");
        }
    }
}

void MenuManager::display()
{
    if (stateManager.configure == false)
    {
        Log.traceln("MenuManager - display returning");
        return;
    }

    Log.traceln("MenuManager.display: state=%d, ln=%d", state, activeLineNum);
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
        // else if (currentAction == ButtonAction::PUSH)
        // {
        //     // Figure out next state
        //     // Perhaps a series of menu item objects makes sense
        //     Log.traceln("Button pushed");
        //     if (activeLineNum == 5)
        //     {
        //         state = 0;
        //         displayManager.setTextColor(WHITE, WHITE);
        //         displayManager.clear();
        //         displayManager.setRefresh(true);
        //         stateManager.configure = false;
        //         actionEventManager.postEvent(ActionEvent::WAITING);
        //         // return;
        //     }
        // }
    }
    if (stateManager.configure == true)
    {
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
