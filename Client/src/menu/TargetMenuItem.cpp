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
    this->menuPrompt = "";
    
    initialize();
}

TargetMenuItem::~TargetMenuItem()
{
    for (uint8_t i = 0; i < items.size(); i++)
    {
        MenuItem *item = items[i];
        items.removeAt(i);
        delete (item);
    }
    items.clear();
}

void TargetMenuItem::initialize()
{
    MultiActionItem::initialize();

    ActionNumberInput *iNodeId = new ActionNumberInput("Target Node > ", std::bind(&TargetMenuItem::doNodeId, this), 2);
    iNodeId->setValue(target->targetNodeId);

    ActionNumberInput *iStartDelay = new ActionNumberInput("Start Delay > ", std::bind(&TargetMenuItem::doStartDelay, this), 3);
    iStartDelay->setValue(target->startDelay);

    ActionNumberInput *iStopDelay = new ActionNumberInput("Stop Delay  > ", std::bind(&TargetMenuItem::doStopDelay, this), 3);
    iStopDelay->setValue(target->endDelay);

    items.add(iNodeId);
    items.add(iStartDelay);
    items.add(iStopDelay);
    
}

void TargetMenuItem::doNodeId()
{
}

void TargetMenuItem::doStartDelay()
{
}

void TargetMenuItem::doStopDelay()
{
}

void TargetMenuItem::doDelete()
{
}

// void TargetMenuItem::onButtonPush()
// {
//         Log.traceln("Saving %s to value", color->name);
//         // TODO - save color
//         menuManager.pop();
//         menuManager.display();
// }