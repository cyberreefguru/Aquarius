/*
 * TargetManager.cpp
 *
 *  Created on: Jan 17, 2024
 *      Author: cyberreefguru
 */
#include "TargetManager.h"
//#include "PreferenceManager.h"

TargetManager targetManager;

TargetManager::TargetManager()
{

}

TargetManager::~TargetManager() 
{
    free(targets);
}

void TargetManager::initialize()
{
    Log.traceln("TargetManager::initialize - BEGIN");

    char *targetBuff = prefManager.getTargets();
    if( fromString(targetBuff))
    {
        Log.traceln("TargetManager::initialize - Parsed target json");
    }
    else
    {
        Log.errorln("TargetManager::initialize - failed to parse targets JSON");
    }

    Log.traceln("TargetManager::initialize - END");
}


/**
 * @brief turns targets into a JSON string
 * @return number of bytes in string
 */
uint32_t TargetManager::toString(char *buff, uint32_t size)
{
    Log.traceln("TargetManager::toString - BEGIN");

    // Clear buffer
    memset(buff, 0, size);

    // turn json into string
    uint32_t s = serializeJson(targetJson, buff, size);

    Log.traceln("TargetManager::toString - END");

    return s;
}

bool TargetManager::fromString(char *buff)
{
    Log.traceln("TargetManager::fromString - BEGIN");

    targetJson.clear();
    DeserializationError err = deserializeJson(targetJson, buff);
    if (err)
    {
        Log.errorln("TargetManager::fromString - failed to parse input: '%s'", buff);
        return false;
    }

    JsonArray array = targetJson[KEY_TARGETS];
    uint8_t numTargets = array.size();
    targets = new Target[numTargets];
    for (uint8_t i = 0; i < numTargets; i++)
    {
        JsonObject t = array[i];
        targets[i].sourceNodeId = prefManager.getNodeId();
        targets[i].targetNodeId = t[KEY_TARGET_NODE_ID];
        targets[i].startDelay = t[KEY_TARGET_START_DELAY];
        targets[i].endDelay = t[KEY_TARGET_END_DELAY];
        Log.traceln("TargetManager::fromString - creating target[%d] node ID = %d", i, targets[i].targetNodeId);
    }

    Log.traceln("TargetManager::fromString - END");
    return true;
}
