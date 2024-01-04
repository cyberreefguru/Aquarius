/*
 * ExitMenuItem.h
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */

#include "MenuManager.h"

ExitMenuItem::ExitMenuItem()
{
    this->title = "> Exit";
    this->items = nullptr;
    this->numItems = 0;
}

ExitMenuItem::~ExitMenuItem()
{
}

void ExitMenuItem::onDisplay()
{
    if( menuManager.peek() == this )
    {
        menuManager.pop();
    }
    stateManager.configure = false;
    actionEventManager.postEvent(ActionEvent::WAITING);
    Log.traceln("ExitMenuItem::onDisplay - posted wait event");

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