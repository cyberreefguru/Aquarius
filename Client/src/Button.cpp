#include "Button.h"

Button::Button(){}

void Button::initialize(uint8_t pin, ButtonEvent event)
{
    this->pin = pin;
    this->event = event;
    lastTrigger = 0;
    lastState = HIGH;
    Log.traceln("pin=%d, action=%d", pin, event);
}


