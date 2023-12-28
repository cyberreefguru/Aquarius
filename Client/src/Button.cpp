#include "Button.h"

Button::Button(){}

void Button::initialize(uint8_t pin)
{
    this->pin = pin;
    lastTrigger = 0;
    lastState = HIGH;
}

// bool Button::get()
// {
//     return value;
// }

// void Button::set()
// {
//     uint32_t t = millis();
//     if( (t - lastTrigger) > 250 )
//     {
//         lastTrigger = t;
//         value = true;
//     }
// }

// void Button::reset()
// {
//     value = false;
// }



