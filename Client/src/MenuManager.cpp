/*
 * MenuManager.cpp
 *
 *  Created on: Dec  30, 2023
 *      Author: cyberreefguru
 */
#include "MenuManager.h"

MenuManager menuManager;

SimpleStack<MenuItem *> menus(5); // max 5 levels

// ColorMenuItem cmiWhite = ColorMenuItem(&colorWhite);
// ColorMenuItem cmiBlack = ColorMenuItem(&colorBlack);
// ColorMenuItem cmiRed = ColorMenuItem(&colorRed);
// ColorMenuItem cmiGreen = ColorMenuItem(&colorGreen);
// ColorMenuItem cmiBlue = ColorMenuItem(&colorBlue);
// ColorMenuItem cmiMaroon = ColorMenuItem(&colorMaroon);
// ColorMenuItem cmiSalmon = ColorMenuItem(&colorSalmon);
// ColorMenuItem cmiPink = ColorMenuItem(&colorPink);
// ColorMenuItem cmiDeepPink = ColorMenuItem(&colorDeepPink);
// ColorMenuItem cmiMagenta = ColorMenuItem(&colorMagenta);
// ColorMenuItem cmiPurple = ColorMenuItem(&colorPurple);
// ColorMenuItem cmiLtBlue = ColorMenuItem(&colorLightBlue);
// ColorMenuItem cmiNavyBlue = ColorMenuItem(&colorNavyBlue);
// ColorMenuItem cmiLtGreen = ColorMenuItem(&colorLightGreen);
// ColorMenuItem cmiChar = ColorMenuItem(&colorChartreuse);
// ColorMenuItem cmiCyan = ColorMenuItem(&colorCyan);
// ColorMenuItem cmiDkCyan = ColorMenuItem(&colorDarkCyan);
// ColorMenuItem cmiOrange = ColorMenuItem(&colorOrange);
// ;
// ColorMenuItem cmiOrgRed = ColorMenuItem(&colorOrangeRed);
// ColorMenuItem cmiDkOrg = ColorMenuItem(&colorDarkOrange);
// ColorMenuItem cmiYel = ColorMenuItem(&colorYellow);
// ColorMenuItem cmiYelGr = ColorMenuItem(&colorYellowGreen);

// MenuItem *cmiItems[22] = {&cmiWhite, &cmiBlack, &cmiRed,
//                                &cmiGreen, &cmiBlue, &cmiMaroon,
//                                &cmiSalmon, &cmiPink, &cmiDeepPink,
//                                &cmiMagenta, &cmiPurple, &cmiLtBlue,
//                                &cmiNavyBlue, &cmiLtGreen, &cmiChar,
//                                &cmiCyan, &cmiDkCyan, &cmiOrange,
//                                &cmiOrgRed, &cmiDkOrg, &cmiYel,
//                                &cmiYelGr};

// ListMenuItem colorConn = ListMenuItem("Set Connect Color", "> Connect", cmiItems, 22);

ColorListItem colorActive = ColorListItem("Set Active Color", "> Active");
ColorListItem colorInact = ColorListItem("Set Inactive Color", "> Inactive");
ColorListItem colorInit = ColorListItem("Set Initialize Color", "> Initialize");
ColorListItem colorConn = ColorListItem("Set Connect Color", "> Connect");
ColorListItem colorConfig = ColorListItem("Set Configure Color", "> Configure");
ColorListItem colorErr = ColorListItem("Set Error Color", "> Error");
ColorListItem colorRec = ColorListItem("Set Receive Color", "> Receive");
ColorListItem colorProc = ColorListItem("Set Processing Color", "> Processing");
ColorListItem colorSend = ColorListItem("Set Send Color", "> Send");
ColorListItem colorWait = ColorListItem("Set Wait Color", "> Wait");

// SimpleMenuItem colorWait = SimpleMenuItem("> Wait");
// SimpleMenuItem colorRec = SimpleMenuItem("> Receive");
// SimpleMenuItem colorProc = SimpleMenuItem("> Process");
// SimpleMenuItem colorSend = SimpleMenuItem("> Send");
// SimpleMenuItem colorActive = SimpleMenuItem("> Active");
// SimpleMenuItem colorInact = SimpleMenuItem("> Inactive");
// SimpleMenuItem colorErr = SimpleMenuItem("> Error");
MenuItem *cmItems[10] = {&colorInit, &colorConn, &colorConfig, &colorWait,
                        &colorRec, &colorProc, &colorSend,
                        &colorActive, &colorInact, &colorErr};


ListMenuItem selColor = ListMenuItem("Colors", "> Colors", cmItems, 10);

NumberInputItem ni = NumberInputItem("Enter Node ID:", "> Node ID", 0, 2);
SimpleMenuItem nodeid = SimpleMenuItem("> Node ID");
SimpleMenuItem targets = SimpleMenuItem("> Targets");
SimpleMenuItem colors = SimpleMenuItem("> Colors");
SimpleMenuItem sensor = SimpleMenuItem("> Sensor Threshold");
SimpleMenuItem servo = SimpleMenuItem("> Servo Limits");
SimpleMenuItem e1 = SimpleMenuItem("> Extra 1");
SimpleMenuItem e2 = SimpleMenuItem("> Extra 2");
ExitMenuItem mexit = ExitMenuItem();
MenuItem *mmItems[8] = {&ni, &targets, &selColor,
                        &sensor, &servo, &e1, &e2, &mexit};
ListMenuItem mainMenu = ListMenuItem("Main Menu", "> Main Menu", mmItems, 8);

MenuManager::MenuManager()
{
}

MenuManager::~MenuManager()
{
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

    mainMenu.getChildren()[0]->setActive(true);

    menus.push(&mainMenu);
    Log.infoln("menu manager initialization complete");
}

void MenuManager::actionEventHandler(void *args, esp_event_base_t base, int32_t id, void *data)
{
    ActionEvent ae = (ActionEvent)id;

    if (ae == ActionEvent::CONFIGURE)
    {
        stateManager.configure = true;
        // Get the current menu item
        MenuItem *item = nullptr;
        menus.peek(&item);
        if (item != nullptr)
        {
            item->onDisplay();
        }
    }
}

void MenuManager::inputEventHandler(void *args, esp_event_base_t base, int32_t id, void *data)
{
    currentAction = (ButtonAction)id;
    currentEvent = *((ButtonEvent *)data);

    Log.infoln("MenuManager::inputEventHandler - Event: %s, Action: %s", ++currentEvent, ++currentAction);

    if (currentAction == ButtonAction::PRESS)
    {
        if (stateManager.processing == false && stateManager.configure == false)
        {
            // We have a button event, we're not doing anything, and we're not already in memu mode
            actionEventManager.postEvent(ActionEvent::CONFIGURE);
        }
        else if (stateManager.configure == true)
        {
            Log.traceln("MenuManager::inputEventHandler - passing event to menu item");
            // Get the current menu item
            MenuItem *item = nullptr;
            menus.peek(&item);
            if (item != nullptr)
            {
                item->onEvent(currentEvent);
            }
        }
        else
        {
            Log.traceln("UNHANDLED CONDITION");
        }
    }
}

MenuItem *MenuManager::peek()
{
    MenuItem *item = nullptr;
    menus.peek(&item);
    return item;
}

void MenuManager::push(MenuItem *item)
{
    if (item != nullptr)
    {
        Log.traceln("Push: %s", item->getTitle());
        item->setActive(true);
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
        // We are at the root node, so don't pop
        // Exit menu system
        displayManager.clear();
        actionEventManager.postEvent(ActionEvent::WAITING);
        stateManager.configure = false;
        return;
    }

    MenuItem *item;
    menus.pop(&item);
    if (&item != nullptr)
    {
        Log.traceln("Pop: %s", item->getTitle());
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
            item->onDisplay();

            //     // Deactivate this item
            //     // TODO: Keep it active or reactive it
            //     item->active = false;

            //     // item->onActivate(false);
            //     // Display this item
            //     item->onDisplay();

            //     // Display any child items
            //     if (item->numItems > 0)
            //     {
            //         Log.traceln("MenuManager::display - showing %d children: %s", item->numItems, item->label);
            //         // get active node
            //         uint8_t active = item->getActiveIndex();
            //         if (item->items[active]->active == false)
            //         {
            //             // If no node was active, activate it
            //             item->items[active]->active = true;
            //         }

            //         //Log.traceln("sw=%d", item->windowStart);
            //         uint8_t start = item->windowStart;
            //         uint8_t end = start + 5;
            //         //Log.traceln("MenuManager::display - start=%d, end=%d, diff=%d", start, end);

            //         if( end > (item->numItems - 1))
            //         {
            //             end = item->numItems - 1;
            //         }
            //         //Log.traceln("start=%d, end=%d, diff=%d", start, end);
            //         // We can display 6 menu items on the screen at one time
            //         // If number to show is > 6, then create window of 6 items
            //         // to show.
            //         for (uint8_t i = start; i <= end; i++)
            //         {
            //             //Log.traceln("MenuManager::display - displaying=%d: %s", i, item->items[i]->label);
            //             item->items[i]->onDisplay();
            //         }
            //     }
            //     else
            //     {
            //         Log.traceln("No children to show: %s", item->label);
            //     }
            //     displayManager.setRefresh(true);
        }
    }
    Log.traceln("MenuManager::display: END");
}

// void MenuManager::print(uint8_t curLine, const char *m, bool nl)
// {
//     Log.traceln("cl=%d, ln=%d, nl=%d, m=%s", curLine, activeLineNum, nl, m);
//     if (curLine == activeLineNum)
//     {
//         displayManager.setTextColor(BLACK, WHITE);
//     }
//     else
//     {
//         displayManager.setTextColor(WHITE);
//     }
//     displayManager.setCursor(curLine, 0);
//     displayManager.print(m);
// }
