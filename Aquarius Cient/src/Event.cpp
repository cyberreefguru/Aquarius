#include "Event.h"

EventType Event::getEventType()
{
    return type;
}

void Event::setEventType(EventType t)
{
    type = t;
}

uint8_t Event::getSourceId()
{
    return sourceId;
}

void Event::setSourceId(uint8_t id)
{
    sourceId = id;
}

String Event::getMessage()
{
    return msg;
}

void Event::setMessage(String msg)
{
    this->msg = msg;
}

uint32_t Event::getEventTime()
{
    return time;
}

void Event::setEventTime(uint32_t time)
{
    this->time = time;
}

