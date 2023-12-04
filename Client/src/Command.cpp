#include "Command.h"

Command::Command()
{

    jsonDocument.clear();
    parameters.clear();
};

uint32_t Command::fromJson(char *buffer)
{
    jsonDocument.clear();
    return serializeJson(jsonDocument, buffer, CMD_MAX_SIZE);
}

const JsonDocument &Command::toJson(char *buff)
{
    Log.infoln("Creating json from buff: %d", buff);
    if (buff != nullptr)
    {
        jsonDocument.clear();
        Log.infoln("Cleared document, parsing");
        DeserializationError err = deserializeJson(jsonDocument, buff);
        Log.infoln("Parsed!");
        if (err)
        {
            Log.errorln("Failed to parse input: '%s'", buff);
        }
        else
        {
            Log.infoln("Checking for parameters");
            if (jsonDocument.containsKey(KEY_PARAMS))
            {
                Log.infoln("Parsing parameters");
                const char *params = jsonDocument[KEY_PARAMS];
                err = deserializeJson(parameters, params);
                if (err)
                {
                    Log.errorln("Failed to parse parameters: '%s'", params);
                }
                else
                {
                    Log.infoln("Parsed parameters");
                }
            }
            else
            {
                Log.infoln("No parameters to parse");
            }
        }
    }
    else
    {
        Log.errorln("Unable to parse -- buffer is null!");
    }

    return jsonDocument;
}

CommandType Command::getType()
{
    return (CommandType)jsonDocument[KEY_TYPE].as<int>();
}

void Command::setType(CommandType t)
{
    jsonDocument[KEY_TYPE] = (int)t;
}

ActionType Command::getAction()
{
    return (ActionType)jsonDocument[KEY_ACTION].as<int>();
}

void Command::setAction(ActionType a)
{
    jsonDocument[KEY_ACTION] = (int)a;
}

uint8_t Command::getSourceId()
{
    return jsonDocument[KEY_SOURCE_ID];
}

void Command::setSourceId(uint8_t id)
{
    jsonDocument[KEY_SOURCE_ID] = id;
}

uint8_t Command::getTargetId()
{
    return jsonDocument[KEY_TARGET_ID];
}

void Command::setTargetId(uint8_t id)
{
    jsonDocument[KEY_TARGET_ID] = id;
}

uint32_t Command::getTime()
{
    return jsonDocument[KEY_TIME];
}

void Command::setTime(uint32_t t)
{
    jsonDocument[KEY_TIME] = t;
}

const JsonDocument &Command::getParameters()
{
    return parameters;
}

void Command::setParameters(char *s)
{
    parameters.clear();
    DeserializationError err = deserializeJson(parameters, s);
}
