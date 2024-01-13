// /*
//  * OptionInputItem.h
//  *
//  *  Created on: Jan 12, 2024
//  *      Author: cyberreefguru
//  */
// #ifndef OptionInputItem_H
// #define OptionInputItem_H

// #include <Arduino.h>
// #include <ArduinoLog.h>

// #include "MenuItem.h"
// #include "ActionMenuItem.h"
// #include "DisplayManager.h"

// class OptionInputItem : public MenuItem
// {
// public:
//     OptionInputItem() {}
//     OptionInputItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt, MenuItem *item);
//     virtual ~OptionInputItem();

//     void initializeValue();
//     void setValue();
    
//     virtual void onEvent(ButtonEvent be) override;

//     virtual void onDisplay() override;
//     // virtual void onButtonUp() override;
//     // virtual void onButtonDown() override;
//     // virtual void onButtonLeft() override;
//     // virtual void onButtonRight() override;
//     // virtual void onButtonPush() override;

// private:
//     ActionMenuItem *ok = nullptr;
//     ActionMenuItem *cancel = nullptr;
//     MenuItem *item;
//     uint8_t highlighted = 0;
//     bool active = false;
// };

// #endif