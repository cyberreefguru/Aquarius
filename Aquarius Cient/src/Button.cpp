#include "Button.h"

Button::Button(){}

void Button::initialize(uint8_t pin)
{
    lastTrigger = 0;
}

bool Button::get()
{
    return value;
}

void Button::set()
{
    uint32_t t = millis();
    if( (t - lastTrigger) > 250 )
    {
        lastTrigger = t;
        value = true;
    }
}

void Button::reset()
{
    value = false;
}



