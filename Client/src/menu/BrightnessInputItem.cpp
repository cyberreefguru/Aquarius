/*
 * ExitMenuItem.h
 *
 *  Created on: Dec  31, 2023
 *      Author: cyberreefguru
 */

#include "BrightnessInputItem.h"

BrightnessInputItem::BrightnessInputItem(const char *title, const char *label)
{
    this->title = title;
    this->label = label;
    this->value = value;
    this->items = nullptr;
    this->numItems = 0;
    this->numDigits = 0;
    this->curDigit = 0;
}

void BrightnessInputItem::onButtonPush()
{
        displayManager.setBrightness( getValue() );

        // Save value and pop us off the menu
        menuManager.pop();
        // display the currnet top of the queue
        menuManager.display();
}