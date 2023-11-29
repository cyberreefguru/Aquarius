#include "CommandEvent.h"


Command CommandEvent::getType()
{
    return type;
}

void CommandEvent::setType(Command t)
{
    type = t;
}

uint8_t CommandEvent::getSourceId()
{
    return sourceId;
}

void CommandEvent::setSourceId(uint8_t id)
{
    sourceId = id;
}

String CommandEvent::getParameters()
{
    return params;
}

void CommandEvent::setParameters(String msg)
{
    this->params = msg;
}

uint32_t CommandEvent::getEventTime()
{
    return time;
}

void CommandEvent::setEventTime(uint32_t time)
{
    this->time = time;
}

