// /*
//  * OptionInputItem.cpp
//  *
//  *  Created on: Jan 12, 2024
//  *      Author: cyberreefguru
//  */
// #include "OptionInputItem.h"

// OptionInputItem::OptionInputItem(menu_label_t label, menu_title_t title, menu_prompt_t prompt, MenuItem *item)
// {
//     this->menuLabel = label;
//     this->menuTitle = title;
//     this->menuPrompt = prompt;
//     this->item = item;

//     // menu_label_t label, menu_title_t title, menu_prompt_t prompt, MenuItem *item
//     // ok = new ActionMenuItem("OK", "", "OK", this->item);
//     // cancel = new ActionMenuItem("CANCEL", "", "CANCEL", this->item);
//     ok->active = false;
//     cancel->active = false;

//     highlighted = 0;
// }

// OptionInputItem::~OptionInputItem()
// {
//     free(ok);
//     free(cancel);
// }

// void OptionInputItem::onDisplay()
// {
//     Log.traceln("OptionInputItem::onDisplay - BEGIN");

//     displayManager.print(menuPrompt);
//     item->onDisplay();
//     displayManager.println();
//     ok->onDisplay();
//     cancel->onDisplay();
//     Log.traceln("OptionInputItem::onDisplay - END");
// }

// void OptionInputItem::onEvent(ButtonEvent be)
// {
//     Log.traceln("OptionInputItem.onEvent - BEGIN");
//     MenuItem *i = nullptr;
//     switch (highlighted)
//     {
//     case 0:
//         i = item;
//         break;
//     case 1:
//         i = ok;
//         break;
//     case 2:
//         i = cancel;
//         break;
//     }

//     switch (be)
//     {
//     case ButtonEvent::UP:
//         if( highlighted == 0 )
//         {
//             highlighted = 2;
//         }
//         else if(highlighted = 1 )
//         {
//             highlighted = 0;
//         }
//         else if(highlighted == 2)
//         {
//             highlighted = 0;
//         }
//         break;
//     case ButtonEvent::DOWN:
//         if( highlighted == 0 )
//         {
//             highlighted = 1;
//         }
//         else if(highlighted = 1 )
//         {
//             highlighted = 0;
//         }
//         else if(highlighted == 2)
//         {
//             highlighted = 0;
//         }
//         break;
//     case ButtonEvent::LEFT:
//         if( highlighted == 0 )
//         {
//             highlighted = 1;
//         }
//         else if(highlighted = 1 )
//         {
//             highlighted = 2;
//         }
//         else if(highlighted == 2)
//         {
//             highlighted = 0;
//         }
//         break;
//     case ButtonEvent::RIGHT:
//         if( highlighted == 0 )
//         {
//             highlighted = 2;
//         }
//         else if(highlighted = 1 )
//         {
//             highlighted = 0;
//         }
//         else if(highlighted == 2)
//         {
//             highlighted = 1;
//         }
//         break;
//     case ButtonEvent::PUSH:
//         if( highlighted == 0 )
//         {
//             item->onButtonPush();
//         }
//         else if(highlighted = 1 )
//         {
//             highlighted = 0;
//         }
//         else if(highlighted == 2)
//         {
//             cancel->active = false;
            
//             highlighted = 0;
//         }
//         break;
//     default:
//         break;
//     }
//     Log.traceln("OptionInputItem.onEvent - END");
// }

// // void OptionInputItem::onButtonPush()
// // {
// //     item->onButtonPush();
// // }
