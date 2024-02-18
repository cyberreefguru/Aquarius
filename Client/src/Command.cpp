/**
 * @brief Class encapsulating command information
 * @file ServCommandoManager.cpp
 * @date Nov 26, 2023
 * @author cyberreefguru
 */
#include "Command.h"

Command::Command()
{

    jsonDocument.clear();
    parameters.clear();
}

/**
 * @brief Serializes current command object into a JSON string 
 * @param buffer where json is placed
 * @return number of bytes placed into buffer
 */
uint32_t Command::serialize(char *buffer)
{
    return serializeJson(jsonDocument, buffer, CMD_MAX_SIZE);
}

/**
 * @brief parses buffer into command object
 * @param buff buffer containing json
 */
void Command::parse(char *buff)
{
    Log.traceln("Command::parse - creating json from buff: %s", buff);
    if (buff != nullptr)
    {
        jsonDocument.clear();
        DeserializationError err = deserializeJson(jsonDocument, buff);
        if (err)
        {
            Log.errorln("Command::parse - failed to parse input: '%s'", buff);
        }
        else
        {
            // Check for parameters string
            if (jsonDocument.containsKey(KEY_CMD_PARAMS))
            {
                Log.traceln("Command::parse - parsing parameters");
                const char *params = jsonDocument[KEY_CMD_PARAMS];
                err = deserializeJson(parameters, params);
                if (err)
                {
                    Log.errorln("Command::parse - failed to parse parameters: '%s'", params);
                }
                else
                {
                    Log.traceln("Command::parse - parsed parameters");
                }
            }
            else
            {
                Log.infoln("Command::parse - no parameters to parse");
            }
        }
    }
    else
    {
        Log.errorln("Command::parse - unable to parse -- buffer is null!");
    }
}

CommandType Command::getType()
{
    return (CommandType)jsonDocument[KEY_CMD_TYPE].as<int>();
}

void Command::setType(CommandType t)
{
    jsonDocument[KEY_CMD_TYPE] = (int)t;
}

ActionType Command::getAction()
{
    return (ActionType)jsonDocument[KEY_CMD_ACTION].as<int>();
}

void Command::setAction(ActionType a)
{
    jsonDocument[KEY_CMD_ACTION] = (int)a;
}

uint8_t Command::getSourceId()
{
    return jsonDocument[KEY_CMD_SOURCE_ID];
}

void Command::setSourceId(uint8_t id)
{
    jsonDocument[KEY_CMD_SOURCE_ID] = id;
}

uint8_t Command::getTargetId()
{
    return jsonDocument[KEY_CMD_TARGET_ID];
}

void Command::setTargetId(uint8_t id)
{
    jsonDocument[KEY_CMD_TARGET_ID] = id;
}

uint32_t Command::getTime()
{
    return jsonDocument[KEY_CMD_TIME];
}

void Command::setTime(uint32_t t)
{
    jsonDocument[KEY_CMD_TIME] = t;
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
