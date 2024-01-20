/*
 * TargetManager.cpp
 *
 *  Created on: Jan 17, 2024
 *      Author: cyberreefguru
 */
#include "TargetManager.h"
// #include "PreferenceManager.h"

TargetManager targetManager;

/**
 * @brief Constructor
 * 
 */
TargetManager::TargetManager()
{
}

/**
 * @brief Destructor
 * 
 */
TargetManager::~TargetManager()
{
    for (uint8_t i = 0; i < targets.size(); i++)
    {
        free(targets.get(i));
    }
}

/**
 * @brief Initializles the target manager. 
 * @note Requires preferences to be initalized first.
 * 
 */
void TargetManager::initialize()
{
    Log.traceln("TargetManager::initialize - BEGIN");

    char *targetBuff = prefManager.getTargets();
    if (fromString(targetBuff))
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
 * @brief Adds target to the list
 * @param target 
 */
void TargetManager::add(Target *target)
{
    targets.add(target);
}

/**
 * @brief removes specified target from list
 * @param targetIndex 
 */
void TargetManager::remove(uint8_t targetIndex)
{
    targets.removeAt(targetIndex);
}

/**
 * @brief removes specified target from list
 * @param target 
 */
void TargetManager::remove(Target *target)
{
    targets.remove(target);
}

/**
 * @brief returns the specified target
 * @param index 
 * @return target or nullptr if index is out of bounds
 */
Target* TargetManager::get(uint8_t index)
{
    return targets.get(index);
}

/**
 * @brief returns current size of target list
 * @return size of list
 */
uint8_t TargetManager::size()
{
    return targets.size();
}


/**
 * @brief returns list of targets
 * @return ArrayList of Target pointers
 */
ArrayList<Target*> *TargetManager::getTargets()
{
    return &targets;
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

/**
 * @brief Creates target objects from JSON string
 * @param buff buffer containing JSON string
 * @return true if success, false otherwise
 */
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
    for (uint8_t i = 0; i < numTargets; i++)
    {
        JsonObject t = array[i];
        Target *target = new Target();
        target->sourceNodeId = prefManager.getNodeId();
        target->targetNodeId = t[KEY_TARGET_NODE_ID];
        target->startDelay = t[KEY_TARGET_START_DELAY];
        target->endDelay = t[KEY_TARGET_END_DELAY];
        targets.add(target);

        Log.traceln("TargetManager::fromString - creating target[%d] node ID = %d", i, target->targetNodeId);
    }

    Log.traceln("TargetManager::fromString - END");
    return true;
}
