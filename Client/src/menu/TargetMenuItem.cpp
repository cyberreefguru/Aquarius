/**
 * @file TargetMenuItem.cpp
 * @brief Menu item that renders a target for editing
 * @date Jan 19, 2024
 * @author cyberreefguru
 */
#include "TargetMenuItem.h"
#include "TargetManager.h"
#include "MenuManager.h"
#include "Helper.h"

/**
 * @brief Constructor
 * @param target the target to render
 */
TargetMenuItem::TargetMenuItem(Target *target)
{
    this->target = target;
    this->menuTitle = "Edit Target:";
    this->menuLabel = (const char *)label;
    this->menuPrompt = "";

    initialize();
}

/**
 * @brief destructor
 */
TargetMenuItem::~TargetMenuItem()
{
    targetManager.dumpTargets("tmi1-");

    for (uint8_t i = 0; i < items.size(); i++)
    {
        MenuItem *item = items[i];
        delete (item);
    }
    items.clear();

    for (uint8_t i = 0; i < buttons.size(); i++)
    {
        MenuItem *item = buttons[i];
        delete (item);
    }
    buttons.clear();
    targetManager.dumpTargets("tmi2-");
}

/**
 * @brief returns pointer to the target within this menu item
 * @return target pointer
 */
Target* TargetMenuItem::getTarget()
{
    return target;
}

void TargetMenuItem::initialize()
{
    Log.traceln("TargetMenuItem::initialize - BEGIN");

    if (target == nullptr)
    {
        Helper::fatal("TargetMenuItem::initialize - target is null!");
    }

    MultiButtonItem::initialize();

    // Log.traceln("TargetMenuItem::initialize -  target node id - %d @ %X", target->targetNodeId, target);
    if (label == nullptr)
    {
        Helper::fatal("TargetMenuItem::initialize - label buffer is null!");
    }
    snprintf(label, 21, "> Target %d", target->targetNodeId);

    iNodeId = new ActionNumberInput("Node  > ", std::bind(&TargetMenuItem::doNodeId, this), 2);
    iNodeId->setValue(target->targetNodeId);
    // iNodeId->setLeftCallback(std::bind(&TargetMenuItem::doNumberLeft, this));
    // iNodeId->setRightCallback(std::bind(&TargetMenuItem::doNumberRight, this));
    // iNodeId->setLsb();

    iStartDelay = new ActionNumberInput("Start > ", std::bind(&TargetMenuItem::doStartDelay, this), 6, 2);
    iStartDelay->setValue(target->startDelay);
    // iStartDelay->setLeftCallback(std::bind(&TargetMenuItem::doNumberLeft, this));
    // iStartDelay->setRightCallback(std::bind(&TargetMenuItem::doNumberRight, this));

    iStopDelay = new ActionNumberInput("Stop  > ", std::bind(&TargetMenuItem::doStopDelay, this), 6, 2);
    iStopDelay->setValue(target->stopDelay);
    // iStopDelay->setLeftCallback(std::bind(&TargetMenuItem::doNumberLeft, this));
    // iStopDelay->setRightCallback(std::bind(&TargetMenuItem::doNumberRight, this));

    iOk = new ActionButtonItem("OK");
    iOk->setPushCallback(std::bind(&TargetMenuItem::doOk, this));
    iOk->setLeftCallback(std::bind(&TargetMenuItem::doButtonLeft, this));

    iCancel = new ActionButtonItem("CANCEL");
    iCancel->setPushCallback(std::bind(&TargetMenuItem::doCancel, this));

    iDelete = new ActionButtonItem("DELETE");
    iDelete->setPushCallback(std::bind(&TargetMenuItem::doDelete, this));
    iDelete->setRightCallback(std::bind(&TargetMenuItem::doButtonRight, this));

    items.add(iNodeId);
    items.add(iStartDelay);
    items.add(iStopDelay);
    buttons.add(iOk);
    buttons.add(iCancel);
    buttons.add(iDelete);
    Log.traceln("TargetMenuItem::initialize - END");
}

void TargetMenuItem::doOk()
{
    Log.traceln("TargetMenuItem::doOk - setting values");
    target->targetNodeId = iNodeId->getValue();
    target->startDelay = iStartDelay->getValue();
    target->stopDelay = iStopDelay->getValue();
    snprintf(label, 21, "> Target %d", target->targetNodeId);
    targetManager.save();

    menuManager.popAndDisplay();
}

void TargetMenuItem::doCancel()
{
    Log.traceln("TargetMenuItem::doCancel - canceling");
    menuManager.popAndDisplay();
}

void TargetMenuItem::doDelete()
{
    Log.traceln("TargetMenuItem::doDelete - removing item");

    targetManager.remove(target);
    targetManager.save();
    menuManager.popAndDisplay();
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