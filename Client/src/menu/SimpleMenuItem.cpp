/*
 * ExitMenuItem.h
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */

#include "SimpleMenuItem.h"

SimpleMenuItem::SimpleMenuItem(const char *title)
{
    this->title = title;
    this->label = title;
}

SimpleMenuItem::SimpleMenuItem(const char *title, const char *label)
{
    this->title = title;
    this->label = label;
}

SimpleMenuItem::~SimpleMenuItem()
{
}

void SimpleMenuItem::onDisplay()
{
    Log.traceln("SimpleMenuItem::onDisplay - BEGIN");
    if (label != nullptr)
    {
        displayManager.clear();
        displayManager.setCursor(0, 0);
        displayManager.setTextColor(WHITE);
        displayManager.println(label);
        displayManager.setTextColor(WHITE);
        displayManager.setRefresh(true);
    }
    else
    {
        Log.errorln("Menu Item has no label!");
    }
    Log.traceln("SimpleMenuItem::onDisplay - END");
}

void SimpleMenuItem::onButtonLeft()
{
    onButtonPush();
}

void SimpleMenuItem::onButtonRight()
{
    onButtonPush();
}
void SimpleMenuItem::onButtonPush()
{
        menuManager.pop();
        menuManager.display();
}