/**
 * @brief Controls displaying menu to the screen
 * @file MenuManager.cpp
 * @date Dec  30, 2023
 * @author cyberreefguru
 */
#include "MenuManager.h"

#include "StateManager.h"
#include "DisplayManager.h"
#include "ActionEventManager.h"
#include "InputEventManager.h"
#include "PreferenceManager.h"
#include "TargetManager.h"

#include "menu/MenuColor.h"

#include "menu/ListMenu.h"
#include "menu/ExitMenuItem.h"
#include "menu/MultiActionItem.h"
#include "menu/ActionNumberInput.h"
#include "menu/TargetListMenuItem.h"
#include "menu/ColorListMenu.h"
#include "menu/ResetMenuItem.h"

using namespace std::placeholders;

MenuManager menuManager;

SimpleStack<MenuItem *> menus(5); // max 5 levels

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

ListMenu mColorsItem = ListMenu("> Colors", "Colors:", "> ");

ActionNumberInput iNodeId = ActionNumberInput("> ", std::bind(&MenuManager::doNodeId, menuManager), 2);
MenuItem *nis[1] = {&iNodeId};
MultiActionItem mNodeIdItem = MultiActionItem("> Node ID", "Node ID:", "");

TargetListMenuItem mTargetListItem = TargetListMenuItem("> Targets", "Select Target", "> ");

ActionNumberInput iSensorThres = ActionNumberInput("> ", std::bind(&MenuManager::doSensor, menuManager), 3);
MenuItem *sis[1] = {&iSensorThres};
MultiActionItem mSensorItem = MultiActionItem("> Sensor Threshold", "Sensor Threshold:", "");

ActionNumberInput iScreenBright = ActionNumberInput("Screen > ", std::bind(&MenuManager::doScreenBrightness, menuManager), 3);
ActionNumberInput iLedBright = ActionNumberInput("LED    > ", std::bind(&MenuManager::doLedBrightness, menuManager), 3);
MenuItem *bis[2] = {&iScreenBright, &iLedBright};
MultiActionItem mBrightnessItem = MultiActionItem("> Brightness", "Brightness:", "");

ActionNumberInput iServoStart = ActionNumberInput("Start> ", std::bind(&MenuManager::doServoStart, menuManager), 3);
ActionNumberInput iServoStop = ActionNumberInput("End  > ", std::bind(&MenuManager::doServoStop, menuManager), 3);
MenuItem *amts[2] = {&iServoStart, &iServoStop};
MultiActionItem mServoItem = MultiActionItem("> Servo Settings", "Servo Values:", "");

MenuItem mResetItem = MenuItem("> Factory Reset", "Factory Reset?", "Press to Reset");
MenuItem mExitItem = MenuItem("> Exit", "Exit", "> Exit");

MenuItem *mmItems[] = {
    &mNodeIdItem,
    &mTargetListItem,
    &mColorsItem,
    &mBrightnessItem,
    &mSensorItem,
    &mServoItem,
    &mResetItem,
    &mExitItem,
};
ListMenu mainMenu = ListMenu("> Main Menu", "Main Menu:", "> ");

/**
 * @brief Constructor
 */
MenuManager::MenuManager()
{
}

/**
 * @brief Destructor
 */
MenuManager::~MenuManager()
{
}

/**
 * @brief Initializes the menu manager and menu system
 */
void MenuManager::initialize()
{
    Log.infoln("MenuManager::initialize - BEGIN");

    esp_err_t status;

    // Add event handlers for action events
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

    // Add event handlers for input events
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

    // Initialize menu items
    mNodeIdItem.initialize(nis, 1);
    mSensorItem.initialize(sis, 1);
    mBrightnessItem.initialize(bis, 2);
    mServoItem.initialize(amts, 2);
    mColorsItem.initialize(cis, 10);
    mainMenu.initialize(mmItems, 8);
    mTargetListItem.initialize();

    // Initialize values of input items
    iNodeId.setValue(prefManager.getNodeId());
    iScreenBright.setValue(prefManager.getScreenBrightness());
    iLedBright.setValue(prefManager.getLedBrightness());
    iSensorThres.setValue(prefManager.getSensorThreshold());
    iServoStart.setValue(prefManager.getServoStart());
    iServoStop.setValue(prefManager.getServoStop());

    // Initialize callbacks for reset item
    mResetItem.setActionCallback(std::bind(&MenuManager::doResetPush, this));
    mResetItem.setButtonCallback(std::bind(&MenuManager::popAndDisplay, this),
                                 std::bind(&MenuManager::popAndDisplay, this),
                                 std::bind(&MenuManager::popAndDisplay, this),
                                 std::bind(&MenuManager::popAndDisplay, this),
                                 std::bind(&MenuManager::doResetPush, this));

    // Initialize callback for exit item
    mExitItem.setDisplayCallback(std::bind(&MenuManager::doExit, this, _1));
    mExitItem.setActionCallback(std::bind(&MenuManager::popAndDisplay, this));

    // Push main menu to menu stack
    menus.push(&mainMenu);

    Log.infoln("MenuManager::initialize - END");
}

/**
 * @brief Handles system action events
 * @param args args for event
 * @param base event base
 * @param id the action event
 * @param data not used; null?
 */
void MenuManager::actionEventHandler(void *args, esp_event_base_t base, int32_t id, void *data)
{
    ActionEvent ae = (ActionEvent)id;

    // Received configure event; start displaying the menu system
    if (ae == ActionEvent::CONFIGURE)
    {
        stateManager.configure = true;
        display();
        // // Get the current menu item
        // MenuItem *item = nullptr;
        // menus.peek(&item);
        // if (item != nullptr)
        // {
        //     item->onDisplay(false);
        // }
    }
}

/**
 * @brief Handles button input events, passes them to the menu item for processing
 * @param args args for event
 * @param base event base
 * @param id the current action (press or release)
 * @param data the current event (up, down, etc.)
 */
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
            Log.traceln("MenuManager::inputEventHandler - UNHANDLED CONDITION");
        }
    }
}

/**
 * @brief Returns top of stack without removing it
 * @return the current menu item
 */
MenuItem *MenuManager::peek()
{
    MenuItem *item = nullptr;
    menus.peek(&item);
    return item;
}

/**
 * @brief Pushes menu item onto the stack
 * @param item
 */
void MenuManager::push(MenuItem *item)
{
    if (item != nullptr)
    {
        Log.traceln("MenuManager::push - %s", item->getMenuTitle());
        menus.push(item);
        item->onDisplay(true); // TODO - call display here instead?
    }
    else
    {
        Log.errorln("MenuManager::push - pushed item is null!");
    }
}

/**
 * @brief Removes the top of the menu item stack
 */
void MenuManager::pop()
{
    if (menus.getSize() == 1)
    {
        // We are at the root node, so don't pop
        Log.warningln("MenuManager::pop - top of menu -- can't remove main menu");

        // Exit menu system
        stateManager.configure = false;
        displayManager.clear();
        actionEventManager.postEvent(ActionEvent::WAITING);
        return;
    }

    MenuItem *item;   // Create item temp variable
    menus.pop(&item); // remove item from menu stack
    if (&item != nullptr)
    {
        Log.traceln("MenuManager::pop - %s", item->getMenuLabel());
    }
    else
    {
        Log.errorln("MenuManager::pop - popped item is null!");
    }
}

/**
 * @brief Calls onDisplay of the menu item at the top of the stack
 */
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
            item->onDisplay(true);
        }
    }
    Log.traceln("MenuManager::display: END");
}

void MenuManager::doNodeId()
{
    Log.traceln("MultiActionItem::doNodeId - setting node ID to %d", iNodeId.getValue());

    prefManager.set(KEY_NODE_ID, iNodeId.getValue());

    Log.traceln("MenuManager::doNodeId - END");
}

void MenuManager::doSensor()
{
    Log.traceln("MenuManager::doSensor - BEGIN");

    prefManager.set(KEY_SENSOR_THRESHOLD, iSensorThres.getValue());

    Log.traceln("MenuManager::doSensor - END");
}

void MenuManager::doScreenBrightness()
{
    Log.traceln("MenuManager::doScreenBrightness - BEGIN");

    uint8_t v = iScreenBright.getValue();
    prefManager.set(KEY_BRIGHTNESS_SCREEN, v);
    displayManager.setBrightness(v);

    Log.traceln("MenuManager::doScreenBrightness - END");
}

void MenuManager::doLedBrightness()
{
    Log.traceln("MenuManager::doLedBrightness - BEGIN");

    uint8_t v = iLedBright.getValue();
    prefManager.set(KEY_BRIGHTNESS_LED, v);
    indicatorManager.setBrightness(v);

    Log.traceln("MenuManager::doLedBrightness - END");
}

void MenuManager::doServoStart()
{
    Log.traceln("MenuManager::doServoStart - BEGIN");

    prefManager.set(KEY_SERVO_START, iServoStart.getValue());

    Log.traceln("MenuManager::doServoStart - END");
}
void MenuManager::doServoStop()
{
    Log.traceln("MenuManager::doServoStop - BEGIN");

    prefManager.set(KEY_SERVO_START, iServoStop.getValue());

    Log.traceln("MenuManager::doServoStop - END");
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

void MenuManager::doResetPush()
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
