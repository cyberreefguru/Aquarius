/*
 * ExitMenuItem.h
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */

#include "ExitMenuItem.h"

ExitMenuItem::ExitMenuItem()
{
    this->menuTitle = "Exit Menu";
    this->menuLabel = "> Exit";
    this->menuPrompt = menuLabel;
    this->items = nullptr;
    this->numItems = 0;
}

ExitMenuItem::~ExitMenuItem()
{
}

void ExitMenuItem::onDisplay()
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