/**
 * @file ActionMenuItem.cpp
 * @brief Provides the shell for a menu item that can easily be controlled through call backs. 
 *        No need to create a new class to override functions.
 * @date Dec  31, 2023
 * @author cyberreefguru
*/
#include "ActionMenuItem.h"
#include "DisplayManager.h"
#include "MenuColor.h"

/**
 * @brief Menu item with callbacks to easily override functions.
 * @param label Rendered when item is in a list
 * @param title Rendered as screen title when onDisplay is called
 * @param prompt Rendered when the user needs to input a value
 */
ActionMenuItem::ActionMenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt)
{
    this->menuTitle = title;
    this->menuLabel = label;
    this->menuPrompt = prompt;
}

/**
 * @brief Menu item with callbacks to easily override functions.
 * @param label Rendered when item is in a list
 * @param title Rendered as screen title when onDisplay is called
 * @param prompt Rendered when the user needs to input a value
 * @param cb called when onAction is called
 */
ActionMenuItem::ActionMenuItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt, ActionCallback cb)
{
    this->menuTitle = title;
    this->menuLabel = label;
    this->menuPrompt = prompt;
    this->doAction = cb;
}

/**
 * @brief sets the callback for overriding onDisplay
 * @param cb the callback method
 */
void ActionMenuItem::setDisplayCallback(DisplayCallback cb)
{
    doDisplay = cb;
}

/**
 * @brief sets the callback for overriding onAction
 * @param cb the callback method
 */
void ActionMenuItem::setActionCallback(ActionCallback cb)
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
void ActionMenuItem::setButtonCallback(ButtonCallback up, ButtonCallback down,
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
 * @brief Default display routine; if callback is null, renders title and then prompt
 * @param active Inverts prompt if true;
 */
void ActionMenuItem::onDisplay(bool active)
{
    Log.traceln("ActionMenuItem::onDisplay - BEGIN");

    if (doDisplay != nullptr)
    {
        Log.traceln("ActionMenuItem::onDisplay - using callback");
        doDisplay(active);
        return;
    }

    if (menuTitle == nullptr || menuLabel == nullptr || menuPrompt == nullptr)
    {
        Log.errorln("Item missing labels!");
        return;
    }

    Log.traceln("ActionMenuItem::onDisplay - no callback; rendering %s", menuLabel);

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

    Log.traceln("ActionMenuItem::onDisplay - END");
}

/**
 * @brief Called when action is required; calls doAction callback if non-null.
 * 
 */
void ActionMenuItem::onAction()
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
void ActionMenuItem::onButtonUp()
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
void ActionMenuItem::onButtonDown()
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
void ActionMenuItem::onButtonLeft()
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
void ActionMenuItem::onButtonRight()
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
void ActionMenuItem::onButtonPush()
{
    if (doButtonPush != nullptr)
    {
        doButtonPush();
    }
}