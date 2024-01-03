/*
 * MenuManager.cpp
 *
 *  Created on: Dec  30, 2023
 *      Author: cyberreefguru
 */
#include "MenuManager.h"

MenuManager menuManager;

SimpleStack<MenuItem *> menus(5); // max 5 levels

NumberInputItem ni = NumberInputItem("Enter Node ID:", 2);
MenuItem *nItems[1] = {&ni};

MenuItem nodeid = MenuItem("> Node ID");
MenuItem targets = MenuItem("> Targets");
MenuItem colors = MenuItem("> Colors");
MenuItem sensor = MenuItem("> Sensor Threshold");
MenuItem servo = MenuItem("> Servo Limits");
ExitMenuItem mexit = ExitMenuItem();
MenuItem *mmItems[6] = {&nodeid, &targets, &colors, &sensor, &servo, &mexit};

MenuManager::MenuManager()
{
}

MenuManager::~MenuManager()
{
    free(mainMenu);
}

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

    mainMenu = new MenuItem();
    mainMenu->initialize("Main Menu", mmItems, sizeof(mmItems) / sizeof(mmItems[0]));
    mainMenu->items[0]->active = true;

    nodeid.initialize("> Node ID", nItems, 1);

    menus.push(mainMenu);
    Log.infoln("menu manager initialization complete");
}

void MenuManager::actionEventHandler(void *args, esp_event_base_t base, int32_t id, void *data)
{
    ActionEvent ae = (ActionEvent)id;

    if (ae == ActionEvent::CONFIGURE)
    {
        // Log.infoln("MM - Setting configure");
        state = 0;
        stateManager.configure = true;
        display();
    }
}

void MenuManager::inputEventHandler(void *args, esp_event_base_t base, int32_t id, void *data)
{
    currentAction = (ButtonAction)id;
    currentEvent = *((ButtonEvent *)data);

    Log.infoln("MenuManager::inputEventHandler: Event: %s, Action: %s", ++currentEvent, ++currentAction);

    if (currentAction == ButtonAction::PRESS)
    {
        if (stateManager.processing == false && stateManager.configure == false)
        {
            // We have a button event, we're not doing anything, and we're not already in memu mode
            actionEventManager.postEvent(ActionEvent::CONFIGURE);
        }
        else if (stateManager.configure == true)
        {
            Log.traceln("Configuration Mode - Passing event to menu system");
            // Get the current menu item
            MenuItem *item = nullptr;
            menus.peek(&item);
            if (item != nullptr)
            {
                item->onEvent(currentEvent);
                display();
            }
        }
        else
        {
            Log.traceln("UNHANDLED CONDITION");
        }
    }
}

void MenuManager::push(MenuItem *item)
{
    if (item != nullptr)
    {
        Log.traceln("Push: %s", item->title);
        menus.push(item);
    }
    else
    {
        Log.errorln("Pushed item is null!");
    }
}

void MenuManager::pop()
{
    if (menus.getSize() == 1)
    {
        displayManager.clear();
        actionEventManager.postEvent(ActionEvent::WAITING);
        stateManager.configure = false;
        return;
    }

    MenuItem *item;
    menus.pop(&item);
    if (&item != nullptr)
    {
        Log.traceln("Pop: %s", item->title);
    }
    else
    {
        Log.errorln("Popped item is null!");
    }
}

void MenuManager::display()
{
    if (stateManager.configure == false)
    {
        Log.traceln("MenuManager::display - not in configuration mode; returning");
        return;
    }
    else
    {
        // Get the current menu item
        MenuItem *item = nullptr;
        menus.peek(&item);
        if (item == nullptr)
        {
            Log.errorln("MenuManager::display - ERROR - no menu item at the top of the list!");
            return;
        }
        else
        {
            displayManager.clear();
            displayManager.setCursor(0, 0);

            // Deactivate this item
            // TODO: Keep it active or reactive it
            item->active = false;

            // item->onActivate(false);
            // Display this item
            item->onDisplay();

            // Display any child items
            if (item->numItems > 0)
            {
                Log.traceln("MenuManager::display - showing %d children: %s", item->numItems, item->title);
                // get active node
                uint8_t active = item->getActiveIndex();
                if (item->items[active]->active == false)
                {
                    // If no node was active, activate it
                    item->items[active]->active = true;
                }

                //Log.traceln("sw=%d", item->windowStart);
                uint8_t start = item->windowStart;
                uint8_t end = start + 5;
                //Log.traceln("MenuManager::display - start=%d, end=%d, diff=%d", start, end);

                if( end > (item->numItems - 1))
                {
                    end = item->numItems - 1;
                }
                //Log.traceln("start=%d, end=%d, diff=%d", start, end);
                // We can display 6 menu items on the screen at one time
                // If number to show is > 6, then create window of 6 items
                // to show.
                for (uint8_t i = start; i <= end; i++)
                {
                    //Log.traceln("MenuManager::display - displaying=%d: %s", i, item->items[i]->title);
                    item->items[i]->onDisplay();
                }
            }
            else
            {
                Log.traceln("No children to show: %s", item->title);
            }
            displayManager.setRefresh(true);
        }
    }
    Log.traceln("MenuManager::display: END");
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
