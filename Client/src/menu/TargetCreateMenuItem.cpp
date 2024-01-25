/**
 * @brief menu item to create a new target
 * @file TargetCreateMenuItem.h
 * @date Jan 23, 2024
 * @author cyberreefguru
 * 
*/
#include "TargetCreateMenuItem.h"
// #include "DisplayManager.h"
// #include "MenuManager.h"

TargetCreateMenuItem::TargetCreateMenuItem(ActionCallback cb)
{
    this->menuTitle = "New Target:";
    this->menuLabel = "> New Target";
    this->menuPrompt = "";
    this->doAction = cb;
}

void TargetCreateMenuItem::initialize()
{
    if( target != nullptr )
    {
        delete(target);
    }
    target = new Target();
    tmi = new TargetMenuItem(target);
}
void TargetCreateMenuItem::onDisplay(bool active)
{
    tmi->onDisplay(active);
}

void TargetCreateMenuItem::onButtonPush()
{

}