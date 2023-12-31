#include "Button.h"

Button::Button(){}

void Button::initialize(uint8_t pin, ButtonAction action)
{
    this->pin = pin;
    this->action = action;
    lastTrigger = 0;
    lastState = HIGH;
    Log.traceln("pin=%d, action=%d", pin, action);
}


