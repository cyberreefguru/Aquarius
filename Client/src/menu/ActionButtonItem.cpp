/**
 * @brief Renders button with specified text (prompt) or calls doDisplay
 * @note does NOT override doAction or onAction
 * @file ActionButtonItem.cpp
 * @date Jan 12, 2024
 * @author cyberreefguru
 */
#include "ActionButtonItem.h"
#include "DisplayManager.h"

/**
 * @brief Constructor
 * @param prompt text to render within button
 */
ActionButtonItem::ActionButtonItem(menu_prompt_t prompt)
{
    this->menuTitle = prompt;
    this->menuLabel = prompt;
    this->menuPrompt = prompt;
}

/**
 * @brief Constructor
 * @param prompt text to render within button
 * @param cb action to execute
 */
ActionButtonItem::ActionButtonItem(menu_prompt_t prompt, ActionCallback cb)
{
    this->menuTitle = prompt;
    this->menuLabel = prompt;
    this->menuPrompt = prompt;
    this->doAction = cb;
}

/**
 * @brief calls doDisplay if defined or drawButton otherwise
 * @param active if true, highlights button
 */
void ActionButtonItem::onDisplay(bool active)
{
    // Log.traceln("ActionButtonItem::onDisplay - BEGIN");

    if (doDisplay != nullptr)
    {
        Log.traceln("ActionButtonItem::onDisplay - using callback; rendering %s", menuPrompt); 
        doDisplay(active);
        return;
    }
    else
    {
        if (menuPrompt == nullptr)
        {
            Log.errorln("ActionButtonItem::onDisplay - missing prompt!");
            return;
        }

        Log.traceln("ActionButtonItem::onDisplay - no callback; rendering %s", menuPrompt);
        displayManager.drawButton(menuPrompt, active);
    }

    // Log.traceln("ActionButtonItem::onDisplay - END");
}