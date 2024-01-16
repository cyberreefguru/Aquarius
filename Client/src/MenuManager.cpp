/*
 * MenuManager.cpp
 *
 *  Created on: Dec  30, 2023
 *      Author: cyberreefguru
 */
#include "MenuManager.h"

#include "StateManager.h"
#include "DisplayManager.h"
#include "ActionEventManager.h"
#include "InputEventManager.h"
#include "PreferenceManager.h"

#include "menu/MenuColor.h"

#include "menu/ListMenu.h"
#include "menu/SimpleMenuItem.h"
#include "menu/ExitMenuItem.h"
#include "menu/ActionMenuItem.h"
#include "menu/MultiActionItem.h"
#include "menu/ResetMenuItem.h"
#include "menu/ActionNumberInput.h"
#include "menu/ColorListMenu.h"

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

MenuItem *cis[10] = {&colorInit, &colorConn, &colorConfig, &colorWait,
                         &colorRec, &colorProc, &colorSend,
                         &colorActive, &colorInact, &colorErr};

ListMenu mColorsItem = ListMenu("> Colors", "Colors:", "> ", cis, 10);

ActionNumberInput ni = ActionNumberInput("> ", std::bind(&MenuManager::doNodeId, menuManager), 2);
ActionMenuItem *nis[1] = {&ni};
MultiActionItem mNodeIdItem = MultiActionItem("> Node ID", "Node ID:", nis, 1);

SimpleMenuItem mTargetsItem = SimpleMenuItem("> Targets");

ActionNumberInput si = ActionNumberInput("Sensor > ", std::bind(&MenuManager::doSensor, menuManager), 3);
ActionMenuItem *sis[1] = {&si};
MultiActionItem mSensorItem = MultiActionItem("> Sensor Threshold", "Threshhold:", sis, 1);


ActionNumberInput sbi = ActionNumberInput("Screen > ", std::bind(&MenuManager::doScreenBrightness, menuManager), 3);
ActionNumberInput lbi = ActionNumberInput("LED    > ", std::bind(&MenuManager::doLedBrightness, menuManager), 3);
ActionMenuItem *bis[2] = {&sbi, &lbi};
MultiActionItem mBrightnessItem = MultiActionItem("> Brightness", "Brightness:", bis, 2);

ActionNumberInput mStart = ActionNumberInput("Start> ", std::bind(&MenuManager::doServoStart, menuManager), 3);
ActionNumberInput mStop =  ActionNumberInput("End  > ", std::bind(&MenuManager::doServoEnd, menuManager), 3);
ActionMenuItem *amts[2] = {&mStart, &mStop};
MultiActionItem mServoItem = MultiActionItem("> Servo A Settings", "Servo A Values:", amts, 2);

ActionMenuItem mResetItem = ActionMenuItem("> Factory Reset", "Factory Reset?", "Press to Reset", std::bind(&MenuManager::onResetPush, menuManager));
ActionMenuItem mExitItem = ActionMenuItem("> Exit", "Exit", "> Exit", std::bind(&MenuManager::popAndDisplay, menuManager));

MenuItem *mmItems[] = {
    &mNodeIdItem,
    &mTargetsItem,
    &mColorsItem,
    &mBrightnessItem,
    &mSensorItem,
    &mServoItem,
    &mResetItem,
    &mExitItem,
};
ListMenu mainMenu = ListMenu("> Main Menu", "Main Menu:", "> ", mmItems, 8);

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

    ni.setValue( prefManager.getNodeId() );
    sbi.setValue( prefManager.getScreenBrightness() );
    lbi.setValue( prefManager.getLedBrightness() );
    si.setValue( prefManager.getSensorThreshold() );
    mStart.setValue(prefManager.getServoStart() );
    mStop.setValue(prefManager.getServoStop() );

    mResetItem.setButtonCallback(std::bind(&MenuManager::popAndDisplay, this),
                             std::bind(&MenuManager::popAndDisplay, this),
                             std::bind(&MenuManager::popAndDisplay, this),
                             std::bind(&MenuManager::popAndDisplay, this),
                             std::bind(&MenuManager::onResetPush, this));

    mExitItem.setDisplayCallback(std::bind(&MenuManager::doExit, this, _1));

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
        Log.warningln("MenuManager::pop - top of menu -- can't remove main menu");
        displayManager.clear();
        actionEventManager.postEvent(ActionEvent::WAITING);
        stateManager.configure = false;
        return;
    }

    MenuItem *item;
    menus.pop(&item);
    if (&item != nullptr)
    {
        Log.traceln("MenuManager::pop - %s", item->getMenuTitle());
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

void MenuManager::doNodeId()
{
    Log.traceln("MultiActionItem::doNodeId - setting node ID to %d", ni.getValue());

    prefManager.set(KEY_NODE_ID, ni.getValue());

    Log.traceln("MenuManager::doNodeId - END");
}

void MenuManager::doSensor()
{
    Log.traceln("MenuManager::doSensor - BEGIN");

    pop();
    displayManager.setRefresh(true);

    Log.traceln("MenuManager::doSensor - END");
}

void MenuManager::doScreenBrightness()
{
    Log.traceln("MenuManager::doScreenBrightness - BEGIN");

    pop();
    displayManager.setRefresh(true);

    Log.traceln("MenuManager::doScreenBrightness - END");
}

void MenuManager::doLedBrightness()
{
    Log.traceln("MenuManager::doLedBrightness - BEGIN");

    pop();
    displayManager.setRefresh(true);

    Log.traceln("MenuManager::doLedBrightness - END");
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
    popAndDisplay();
}

void MenuManager::popAndDisplay()
{
    pop();
    display();
    displayManager.setRefresh(true);
}

void MenuManager::doServoStart()
{
    Log.infoln("MenuManager::doServoStart");
}
void MenuManager::doServoEnd()
{
    Log.infoln("MenuManager::doServoEnd");
}
