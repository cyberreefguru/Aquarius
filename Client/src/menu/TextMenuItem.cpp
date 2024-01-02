/*
 * MenuItem.h
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */

#include "menu/TextMenuItem.h"

ExitMenuItem::ExitMenuItem()
{
    this->title = "> Exit";
    this->items = nullptr;
    this->numItems = 0;
}

void ExitMenuItem::onEvent(ButtonEvent be)
{
    Log.traceln("ExitMenuItem::onEvent - %s", ++be);
    if( be == ButtonEvent::PUSH )
    {
        stateManager.configure = false;
        actionEventManager.postEvent(ActionEvent::WAITING);
        Log.traceln("ExitMenuItem - posted wait event");

    }
    else
    {
        Log.traceln("ExitMenuItem - calling parent");
        MenuItem::onEvent(be);
    }

}