/*
 * MenuManager.cpp
 *
 *  Created on: Dec  30, 2023
 *      Author: cyberreefguru
 */
#include "MenuManager.h"

MenuManager menuManager;

SimpleStack<MenuItem *> menus(5); // max 5 levels

uint32_t vServoStart = 0;
uint32_t vServoEnd = 0;


ColorListMenu colorActive = ColorListMenu("Set Active Color", "> Active");
ColorListMenu colorInact = ColorListMenu("Set Inactive Color", "> Inactive");
ColorListMenu colorInit = ColorListMenu("Set Initialize Color", "> Initialize");
ColorListMenu colorConn = ColorListMenu("Set Connect Color", "> Connect");
ColorListMenu colorConfig = ColorListMenu("Set Configure Color", "> Configure");
ColorListMenu colorErr = ColorListMenu("Set Error Color", "> Error");
ColorListMenu colorRec = ColorListMenu("Set Receive Color", "> Receive");
ColorListMenu colorProc = ColorListMenu("Set Processing Color", "> Processing");
ColorListMenu colorSend = ColorListMenu("Set Send Color", "> Send");
ColorListMenu colorWait = ColorListMenu("Set Wait Color", "> Wait");

MenuItem *cmItems[10] = {&colorInit, &colorConn, &colorConfig, &colorWait,
                        &colorRec, &colorProc, &colorSend,
                        &colorActive, &colorInact, &colorErr};


ListMenu selColor = ListMenu("Colors", "> Colors", cmItems, 10);

NumberInputItem ni = NumberInputItem("Enter Node ID:", "> Node ID");
SimpleMenuItem targets = SimpleMenuItem("> Targets");

NumberInputItem sensor = NumberInputItem("Enter Sensor Threshhold:", "> Sensor Threshold");
// NumberInputItem servoStart = NumberInputItem("Enter Servo Start:", "> Servo Start");
// NumberInputItem servoEnd = NumberInputItem("Enter Servo End:", "> Servo End");
BrightnessInputItem brightness = BrightnessInputItem("Enter Brightness:", "> Brightness");

ExitMenuItem mexit = ExitMenuItem();

NumberInput servoStart = NumberInput("Start> ", &vServoStart, 3);
NumberInput servoEnd = NumberInput("End> ", &vServoEnd, 3);

MenuItem *si[2] = {&servoStart, &servoEnd };

MultiNumberInputItem servoMenu = MultiNumberInputItem("Servo Values:", "> Servo Settings", si, 2);


MenuItem *mmItems[] = {&ni, &targets, &selColor, &brightness,
                        &sensor, &servoMenu, &mexit};
ListMenu mainMenu = ListMenu("Main Menu", "> Main Menu", mmItems, 7);

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

    // mainMenu.getChildren()[0]->setActive(true);

    ni.initialize(&vNodeId, 2);
    // servoStart.initialize(&vServoStart, 3);
    // servoEnd.initialize(&vServoEnd, 3);
    sensor.initialize(&vSensor, 3);

    vBrightness = 255;
    brightness.initialize(&vBrightness, 3);

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
        //item->setActive(true);
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
        }
    }
    Log.traceln("MenuManager::display: END");
}