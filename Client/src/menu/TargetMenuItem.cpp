/**
 * @file TargetMenuItem.cpp
 * @brief Menu item that renders a target for editing
 * @date Jan 19, 2024
 * @author cyberreefguru
*/
#include "TargetMenuItem.h"

// #include "DisplayManager.h"
// #include "MenuManager.h"


TargetMenuItem::TargetMenuItem(Target *target)
{
    this->target = target;
    this->menuTitle = "Edit Target:";
    this->menuLabel = "Target ";

}

TargetMenuItem::~TargetMenuItem()
{
}

// void TargetMenuItem::onButtonPush()
// {
//         Log.traceln("Saving %s to value", color->name);
//         // TODO - save color
//         menuManager.pop();
//         menuManager.display();
// }