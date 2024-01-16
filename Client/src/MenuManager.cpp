/*
 * MenuManager.cpp
 *
 *  Created on: Dec  30, 2023
 *      Author: cyberreefguru
 */
#include "MenuManager.h"

#include "menu/MenuColor.h"

#include "menu/ListMenu.h"
#include "menu/NumberInputItem.h"
#include "menu/SimpleMenuItem.h"
#include "menu/ExitMenuItem.h"
#include "menu/MultiNumberInputItem.h"
#include "menu/ActionMenuItem.h"
#include "menu/MultiActionItem.h"
#include "menu/ResetMenuItem.h"
#include "menu/ActionNumberInput.h"

using namespace std::placeholders;

MenuManager menuManager;

SimpleStack<MenuItem *> menus(5); // max 5 levels

uint32_t vServoStart = 0;
uint32_t vServoEnd = 180;
uint32_t vNodeId = 0;
uint32_t vSensor = 128;
uint32_t vBrightness = 255;

ColorListMenu colorActive = ColorListMenu("> Active", "Active Color:", "> ", KEY_COLOR_ACTIVE);
ColorListMenu colorInact = ColorListMenu("> Deactive", "Deactive Color:", "> ", KEY_COLOR_DEACTIVE);
ColorListMenu colorInit = ColorListMenu("> Initialize", "Initialize Color:", "> ", KEY_COLOR_INITIALIZE);
ColorListMenu colorConn = ColorListMenu("> Connect", "Connect Color:", "> ", KEY_COLOR_CONNECT);
ColorListMenu colorConfig = ColorListMenu("> Configure", "Configure Color:", "> ", KEY_COLOR_CONFIGURE);
ColorListMenu colorErr = ColorListMenu("> Error", "Error Color:", "> ", KEY_COLOR_ERROR);
ColorListMenu colorRec = ColorListMenu("> Receive", "Receive Color:", "> ", KEY_COLOR_RECEIVE);
ColorListMenu colorProc = ColorListMenu("> Processing", "Processing Color:", "> ", KEY_COLOR_PROCESS);
ColorListMenu colorSend = ColorListMenu("> Send", "Send Color:", "> ", KEY_COLOR_SEND);
ColorListMenu colorWait = ColorListMenu("> Wait", "Wait Color:", "> ", KEY_COLOR_WAIT);

MenuItem *cmItems[10] = {&colorInit, &colorConn, &colorConfig, &colorWait,
                         &colorRec, &colorProc, &colorSend,
                         &colorActive, &colorInact, &colorErr};

ListMenu selColor = ListMenu("> Colors", "Colors:", "> ", cmItems, 10);

NumberInputItem ni = NumberInputItem("> Node ID", "Node ID:", "> ", &vNodeId, 2);
SimpleMenuItem targets = SimpleMenuItem("> Targets");

NumberInputItem sensor = NumberInputItem("> Sensor Threshold", "Sensor Threshhold:", ">", &vSensor, 3);
NumberInputItem brightness = NumberInputItem("> Brightness", "Brightness:", "> ", &vSensor, 3);

// ExitMenuItem mexit = ExitMenuItem();
// NumberInput servoStart = NumberInput("Start> ", "Start: ", "Start> ", &vServoStart, 3);
// NumberInput servoEnd = NumberInput("End> ", "End: ", "End> ", &vServoEnd, 3);
// MenuItem *si[2] = {&servoStart, &servoEnd};
// MultiNumberInputItem servoMenu = MultiNumberInputItem("> Servo Settings", "Servo Values:", si, 2);

ActionMenuItem mReset = ActionMenuItem("> Factory Reset", "Factory Reset?", "Press to Reset", std::bind(&MenuManager::onResetPush, menuManager));
ActionMenuItem mExit = ActionMenuItem("> Exit", "Exit", "> Exit", std::bind(&MenuManager::onResetButton, menuManager));

ActionNumberInput mStart = ActionNumberInput("Start> ", "Start: ", "Start> ", &vServoStart, 3);
ActionNumberInput mEnd = ActionNumberInput("End> ", "End: ", "End> ", &vServoEnd, 3);

// ActionMenuItem mStart = ActionMenuItem("Start> ", "Start: ", "Start> ", std::bind(&MenuManager::onServoStart, menuManager));
// ActionMenuItem mEnd = ActionMenuItem("End> ", "End: ", "End> ", std::bind(&MenuManager::onServoEnd, menuManager));
ActionMenuItem *amts[2] = {&mStart, &mEnd};
MultiActionItem mServo = MultiActionItem("> Servo A Settings", "Servo A Values:", amts, 2);

// ResetMenuItem mreset = ResetMenuItem();

MenuItem *mmItems[] = {
    &ni,
    &targets,
    &selColor,
    &brightness,
    &sensor,
    // &servoMenu,
    &mServo,
    &mReset,
    &mExit,
};
ListMenu mainMenu = ListMenu("> Main Menu", "Main Menu:", "> ", mmItems, 9);

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

    mReset.setButtonCallback(std::bind(&MenuManager::onResetButton, this),
                             std::bind(&MenuManager::onResetButton, this),
                             std::bind(&MenuManager::onResetButton, this),
                             std::bind(&MenuManager::onResetButton, this),
                             std::bind(&MenuManager::onResetPush, this));

    mExit.setDisplayCallback(std::bind(&MenuManager::doExit, this, _1));

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
            item->onDisplay(false);
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
        Log.traceln("MenuManager::push - %s", item->getMenuTitle());
        // item->setActive(true);
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
        Log.traceln("Pop: %s", item->getMenuTitle());
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
            item->onDisplay(false);
        }
    }
    Log.traceln("MenuManager::display: END");
}

void MenuManager::doExit(bool active)
{
    Log.traceln("MenuManager::doExit - BEGIN");
    pop();
    // stateManager.configure = false;
    actionEventManager.postEvent(ActionEvent::WAITING);
    displayManager.setRefresh(true);
    Log.traceln("MenuManager::doExit - END");
}

void MenuManager::onResetPush()
{
    Log.infoln("Reseting to factory settings...");
    prefManager.reset();
    Log.infoln("Reset!");
    onResetButton();
}

void MenuManager::onResetButton()
{
    pop();
    display();
}

void MenuManager::onServoStart()
{
    Log.infoln("MenuManager::onServoStart");
}
void MenuManager::onServoEnd()
{
    Log.infoln("MenuManager::onServoEnd");
}
