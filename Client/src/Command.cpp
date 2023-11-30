#include "Command.h"


CommandType Command::getType()
{
    return type;
}

void Command::setType(CommandType t)
{
    type = t;
}

ActionType Command::getAction()
{
    return action;
}

void Command::setAction(ActionType a)
{
    action = a;
}

uint8_t Command::getSourceId()
{
    return sourceId;
}

void Command::setSourceId(uint8_t id)
{
    sourceId = id;
}

uint8_t Command::getTargetId()
{
    return sourceId;
}

void Command::setTargetId(uint8_t id)
{
    sourceId = id;
}


String Command::getParameters()
{
    return parameters;
}

void Command::setParameters(String s)
{
    this->parameters = s;
}

uint32_t Command::getTime()
{
    return time;
}

void Command::setTime(uint32_t time)
{
    this->time = time;
}

