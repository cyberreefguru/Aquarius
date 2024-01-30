/**
 * @brief menu item to create a new target
 * @file TargetCreateMenuItem.h
 * @date Jan 23, 2024
 * @author cyberreefguru
 *
 */
#include "TargetCreateMenuItem.h"

#include "TargetManager.h"

TargetCreateMenuItem::TargetCreateMenuItem()
{
    this->menuTitle = "New Target:";
    this->menuLabel = "> New Target";
    this->menuPrompt = "";

    initialize();
}

TargetCreateMenuItem::~TargetCreateMenuItem()
{
}

void TargetCreateMenuItem::initialize()
{
    Log.traceln("TargetCreateMenuItem::initialize - BEGIN");
    if (target != nullptr)
    {
        Log.traceln("TargetCreateMenuItem::initialize - destroying existing target");
        // Log.traceln("TargetCreateMenuItem::initialize - &target=%X, target=%X", &target, target);
        delete (target);
    }
    // Log.traceln("TargetCreateMenuItem::initialize - creating new target");
    this->target = new Target();
    // Log.traceln("TargetCreateMenuItem::initialize - &target=%X, target=%X", &target, target);

    TargetMenuItem::initialize();
    Log.traceln("TargetCreateMenuItem::initialize - END");
}

void TargetCreateMenuItem::doOk()
{
    Log.traceln("TargetCreateMenuItem::doOk - &target=%X, target=%X", &target, target);
    targetManager.add(target);
    TargetMenuItem::doOk();
}
