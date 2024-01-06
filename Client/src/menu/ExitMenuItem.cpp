/*
 * ExitMenuItem.h
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */

#include "MenuManager.h"

ExitMenuItem::ExitMenuItem()
{
    this->title = "Exit Menu";
    this->label = "> Exit";
    this->items = nullptr;
    this->numItems = 0;
}

ExitMenuItem::~ExitMenuItem()
{
}

void ExitMenuItem::onDisplay()
{
    Log.traceln("ExitMenuItem::onDisplay - BEGIN");
    if( menuManager.peek() == this )
    {
        menuManager.pop();
    }
    stateManager.configure = false;
    actionEventManager.postEvent(ActionEvent::WAITING);
    Log.traceln("ExitMenuItem::onDisplay - END");
}

void ExitMenuItem::onEvent(ButtonEvent be)
{
    Log.traceln("ExitMenuItem::onEvent - %s", ++be);
    if( be == ButtonEvent::PUSH )
    {
        stateManager.configure = false;
        actionEventManager.postEvent(ActionEvent::WAITING);
        Log.traceln("ExitMenuItem::onEvent - posted wait event");
    }
}