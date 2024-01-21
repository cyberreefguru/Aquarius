/*
 * ExitMenuItem.h
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */

#include "ExitMenuItem.h"
#include "MenuManager.h"
// #include "DisplayManager.h"
#include "StateManager.h"
#include "ActionEventManager.h"

ExitMenuItem::ExitMenuItem()
{
    this->menuTitle = "Exit Menu";
    this->menuLabel = "> Exit";
    this->menuPrompt = menuLabel;
}

ExitMenuItem::~ExitMenuItem()
{
}

void ExitMenuItem::onDisplay(bool active)
{
    onButtonPush();
    // Log.traceln("ExitMenuItem::onDisplay - BEGIN");
    // stateManager.configure = false;
    // actionEventManager.postEvent(ActionEvent::WAITING);
    // Log.traceln("ExitMenuItem::onDisplay - END");
}

void ExitMenuItem::onButtonRight()
{
    onButtonPush();
}

void ExitMenuItem::onButtonPush()
{
    if( menuManager.peek() == this )
    {
        menuManager.pop();
    }
    stateManager.configure = false;
    actionEventManager.postEvent(ActionEvent::WAITING);
    Log.traceln("ExitMenuItem - posted wait event");
}