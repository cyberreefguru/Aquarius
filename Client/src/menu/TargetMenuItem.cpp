/**
 * @file TargetMenuItem.cpp
 * @brief Menu item that renders a target for editing
 * @date Jan 19, 2024
 * @author cyberreefguru
 */
#include "TargetMenuItem.h"
#include "TargetManager.h"


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

    iNodeId = new ActionNumberInput("Target Node > ", std::bind(&TargetMenuItem::doNodeId, this), 2);
    iNodeId->setValue(target->targetNodeId);

    iStartDelay = new ActionNumberInput("Start Delay > ", std::bind(&TargetMenuItem::doStartDelay, this), 6, 2);
    iStartDelay->setValue(target->startDelay);

    iStopDelay = new ActionNumberInput("Stop Delay  > ", std::bind(&TargetMenuItem::doStopDelay, this), 6, 2);
    iStopDelay->setValue(target->stopDelay);

    iDelete = new ActionButtonItem("DELETE", std::bind(&TargetMenuItem::doDelete, this));
    iStopDelay->setValue(target->stopDelay);

    items.add(iNodeId);
    items.add(iStartDelay);
    items.add(iStopDelay);
    
}

void TargetMenuItem::onOk()
{
    target->targetNodeId = iNodeId->getValue();
    target->startDelay = iStartDelay->getValue();
    target->stopDelay = iStopDelay->getValue();
    targetManager.save();
    MultiActionItem::onCancel();
}

void TargetMenuItem::doNodeId()
{
    target->targetNodeId = iNodeId->getValue();
}

void TargetMenuItem::doStartDelay()
{
    target->startDelay = iStartDelay->getValue();
}

void TargetMenuItem::doStopDelay()
{
    target->stopDelay = iStopDelay->getValue();
}

void TargetMenuItem::doDelete()
{
    targetManager.remove(target);
    targetManager.save();
}

// void TargetMenuItem::onButtonPush()
// {
//         Log.traceln("Saving %s to value", color->name);
//         // TODO - save color
//         menuManager.pop();
//         menuManager.display();
// }