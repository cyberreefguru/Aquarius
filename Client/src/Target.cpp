/*
 * Target.cpp
 *
 *  Created on: Jan 12, 2023
 *      Author: cyberreefguru
 */

#include "Target.h"

Target::Target()
{
}

uint32_t Target::fromJson(char *buffer)
{
    json.clear();
    return serializeJson(json, buffer, TARGET_MAX_SIZE);
}

const JsonDocument &Target::toJson(char *buff)
{
    Log.infoln("Creating json from buff: %d", buff);
    if (buff != nullptr)
    {
        json.clear();
        Log.infoln("Cleared document, parsing");
        DeserializationError err = deserializeJson(json, buff);
        Log.infoln("Parsed!");
        if (err)
        {
            Log.errorln("Failed to parse input: '%s'", buff);
        }
    }
    else
    {
        Log.errorln("Unable to parse -- buffer is null!");
    }

    return json;
}
