/*
 * Menu.cpp
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */
#include "MainMenu.h"

// TextMenuItem nodeid = TextMenuItem("Node ID");
// TextMenuItem targets = TextMenuItem("Targets");
// TextMenuItem colors = TextMenuItem("Colors");
// TextMenuItem sensor = TextMenuItem("Sensor Threshold");
// TextMenuItem servo = TextMenuItem("Servo Limits");
// TextMenuItem mmsave = TextMenuItem("Save");
// TextMenuItem mmexit = TextMenuItem("Exit");

// MenuItem mmItems[] = {nodeid, targets, colors, sensor, servo, mmsave, mmexit};

MainMenu::MainMenu()
{
    // this->items = mmItems;
    // mmsave.setEventCallback(std::bind(&MainMenu::save, this));
    // mmexit.setEventCallback(std::bind(&MainMenu::exit, this));
}

void MainMenu::save()
{
    Log.traceln("Saving changes");
}

void MainMenu::exit()
{
    stateManager.configure = false;
    actionEventManager.postEvent(ActionEvent::WAITING);
}