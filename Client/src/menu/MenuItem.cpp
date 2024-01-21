/*
 * MenuItem.cpp
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */
#include "MenuManager.h" // TODO: fix this
#include "StateManager.h"
#include "DisplayManager.h"
#include "ActionEventManager.h"
#include "InputEventManager.h"

/**
 * @brief default constructor
 */
MenuItem::MenuItem()
{
}

/**
 * @brief Constructor
 * @param label Menu lable
 * @param title Menu title
 * @param prompt Menu prompt
 */
MenuItem::MenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt)
{
    this->menuTitle = title;
    this->menuLabel = label;
    this->menuPrompt = prompt;
}

/**
 * @brief sets the callback for overriding onDisplay
 * @param cb the callback method
 */
void MenuItem::setDisplayCallback(DisplayCallback cb)
{
    doDisplay = cb;
}

/**
 * @brief sets the callback for overriding onLabelDisplay
 * @param cb the callback method
 */
void MenuItem::setLabelDisplayCallback(DisplayCallback cb)
{
    doLabelDisplay = cb;
}

/**
 * @brief sets the callback for overriding onAction
 * @param cb the callback method
 */
void MenuItem::setActionCallback(ActionCallback cb)
{
    doAction = cb;
}

/**
 * @brief sets the callbacks for overriding button input events
 * @param up overrides ButtonEvent::UP
 * @param down overrides ButtonEvent::DOWN
 * @param left overrides ButtonEvent::LEFT
 * @param right overrides ButtonEvent::RIGHT
 * @param push overrides ButtonEvent::PSUH
 */
void MenuItem::setButtonCallback(ButtonCallback up, ButtonCallback down,
                                       ButtonCallback left, ButtonCallback right,
                                       ButtonCallback push)
{
    doButtonUp = up;
    doButtonDown = down;
    doButtonLeft = left;
    doButtonRight = right;
    doButtonPush = push;
}

/**
 * @brief sets the callbacks for overriding button input events
 * @param cb specified callback function
 */
void MenuItem::setUpCallback(ButtonCallback cb)
{
    doButtonUp = cb;
}

/**
 * @brief sets the callbacks for overriding button input events
 * @param cb specified callback function
 */
void MenuItem::setDownCallback(ButtonCallback cb)
{
    doButtonDown = cb;
}

/**
 * @brief sets the callbacks for overriding button input events
 * @param cb specified callback function
 */
void MenuItem::setLeftCallback(ButtonCallback cb)
{
    doButtonLeft = cb;
}

/**
 * @brief sets the callbacks for overriding button input events
 * @param cb specified callback function
 */
void MenuItem::setRightCallback(ButtonCallback cb)
{
    doButtonRight = cb;
}

/**
 * @brief sets the callbacks for overriding button input events
 * @param cb specified callback function
 */
void MenuItem::setPushCallback(ButtonCallback cb)
{
    doButtonPush = cb;
}

/**
 * @brief displays the menu title and prompt
 * @param active if true, highlights the prompt
 */
void MenuItem::onDisplay(bool active)
{
    Log.traceln("MenuItem::onDisplay - BEGIN");

    if (menuTitle == nullptr || menuPrompt == nullptr)
    {
        Log.errorln("MenuItem::onDisplay - no title or prompt");
        return;
    }

    if (doDisplay != nullptr)
    {
        Log.traceln("MenuItem::onDisplay - using callback; rendering %s", menuLabel);
        doDisplay(active);
    }
    else
    {
        Log.traceln("MenuItem::onDisplay - no callback; rendering %s", menuLabel);

        displayManager.clear();
        displayManager.setCursor(0, 0);
        displayManager.println(menuTitle);
        displayManager.addCursorY(4); // put a little gap beween title and menu item

        if (active)
        {
            displayManager.setTextColor(BLACK, WHITE);
        }
        else
        {
            displayManager.setTextColor(WHITE);
        }
        displayManager.print(menuPrompt);
        displayManager.setTextColor(WHITE);
        displayManager.setRefresh(true);
    }

    Log.traceln("MenuItem::onDisplay - END");
}

/**
 * @brief Displays the menu item's label and nothing else
 * @param active if true, inverts screen color
 */
void MenuItem::onLabelDisplay(bool active)
{
    // Log.traceln("MenuItem::onLabelDisplay - BEGIN");

    if (menuLabel == nullptr)
    {
        Log.errorln("MenuItem::onLabelDisplay - label is null!");
        return;
    }

    if (doLabelDisplay != nullptr)
    {
        Log.traceln("MenuItem::onLabelDisplay - using callback; rendering %s", menuLabel);
        doDisplay(active);
    }
    else
    {
        Log.traceln("MenuItem::onLabelDisplay - no callback; rendering %s", menuLabel);
        if (active)
        {
            displayManager.setTextColor(BLACK, WHITE);
        }
        else
        {
            displayManager.setTextColor(WHITE);
        }
        displayManager.println(menuLabel);
        displayManager.setTextColor(WHITE);
        displayManager.setRefresh(true);
    }

    // Log.traceln("MenuItem::onLabelDisplay - END");
}

/**
 * @brief Handles button presses on a menu item; calls appropriate function. Called by MenuManager
 * @param be the button event
 */
void MenuItem::onEvent(ButtonEvent be)
{
    Log.traceln("MenuItem.onEvent - %s", ++be);
    switch (be)
    {
    case ButtonEvent::UP:
        onButtonUp();
        break;
    case ButtonEvent::DOWN:
        onButtonDown();
        break;
    case ButtonEvent::LEFT:
        onButtonLeft();
        break;
    case ButtonEvent::RIGHT:
        onButtonRight();
        break;
    case ButtonEvent::PUSH:
        onButtonPush();
        break;
    default:
        break;
    }
    Log.traceln("MenuItem.onEvent - END");
}

/**
 * @brief Called when action is required; calls doAction callback if non-null.
 *
 */
void MenuItem::onAction()
{
    if (doAction != nullptr)
    {
        doAction();
    }
}

/**
 * @brief Called when button pressed; calls doButtonUp callback if non-null.
 *
 */
void MenuItem::onButtonUp()
{
    if (doButtonUp != nullptr)
    {
        doButtonUp();
    }
}

/**
 * @brief Called when button pressed; calls doButtonDown callback if non-null.
 *
 */
void MenuItem::onButtonDown()
{
    if (doButtonDown != nullptr)
    {
        doButtonDown();
    }
}

/**
 * @brief Called when button pressed; calls doButtonLeft callback if non-null.
 *
 */
void MenuItem::onButtonLeft()
{
    if (doButtonLeft != nullptr)
    {
        doButtonLeft();
    }
}

/**
 * @brief Called when button pressed; calls doButtonRight callback if non-null.
 *
 */
void MenuItem::onButtonRight()
{
    if (doButtonRight != nullptr)
    {
        doButtonRight();
    }
}

/**
 * @brief Called when button pressed; calls doButtonPush callback if non-null.
 *
 */
void MenuItem::onButtonPush()
{
    if (doButtonPush != nullptr)
    {
        doButtonPush();
    }
}
