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
    for (uint8_t i = 0; i < targetList.size(); i++)
    {
        free(targetList.get(i));
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

    char *buf = prefManager.getTargetsBuffer();
    // Log.traceln("TargetManager::initialize - target buf: %s", buf);
    if (fromString(buf) > 0)
    {
        Log.traceln("TargetManager::initialize - Parsed target json - %s", buf);
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
    targetList.add(target);
}

/**
 * @brief removes specified target from list
 * @param targetIndex
 */
void TargetManager::remove(uint8_t targetIndex)
{
    targetList.removeAt(targetIndex);
}

/**
 * @brief removes specified target from list
 * @param target
 */
void TargetManager::remove(Target *target)
{
    targetList.remove(target);
}

/**
 * @brief returns the specified target
 * @param index
 * @return target or nullptr if index is out of bounds
 */
Target *TargetManager::get(uint8_t index)
{
    return targetList.get(index);
}

/**
 * @brief returns current size of target list
 * @return size of list
 */
uint8_t TargetManager::size()
{
    return targetList.size();
}

/**
 * @brief returns list of targets
 * @return ArrayList of Target pointers
 */
ArrayList<Target*> *TargetManager::getTargetList()
{
    return &targetList;
}

void TargetManager::save()
{
    //  {"ts":[{"nid":2,"sd":0,"ed":0}]}

    uint8_t size = targetList.size();
    targetJson.clear();

    // create an empty array
    JsonArray array = targetJson.createNestedArray(KEY_TARGETS);
    for (uint8_t i = 0; i < size; i++)
    {
        Target *target = targetList.get(i);
        JsonObject t = array.createNestedObject();
        t[KEY_TARGET_NODE_ID] = target->targetNodeId;
        t[KEY_TARGET_START_DELAY] = target->startDelay;
        t[KEY_TARGET_END_DELAY] = target->stopDelay;
    }

    char *buf = prefManager.getTargetsBuffer();
    uint32_t s = toString(buf, TARGET_BUFF_SIZE);
    if( s > 0 )
    {
        Log.traceln("TargetManager::save - saving targets(%d) - %s", s, buf);
        prefManager.set(KEY_TARGETS, buf, s);
    }
    else
    {
        Log.errorln("TargetManager::save - failed to serialize!");
    }
}

/**
 * @brief turns targets into a JSON string
 * @return number of bytes in string
 */
uint32_t TargetManager::toString(char *buff, uint32_t size)
{
    // Log.traceln("TargetManager::toString - BEGIN");

    // Clear buffer
    memset(buff, 0, size);

    // turn json into string
    uint32_t s = serializeJson(targetJson, buff, size);

    Log.traceln("TargetManager::toString - target buf: %s", buff);

    // Log.traceln("TargetManager::toString - END");

    return s;
}

/**
 * @brief Creates target objects from JSON string
 * @param buff buffer containing JSON string
 * @return true if success, false otherwise
 */
bool TargetManager::fromString(char *buff)
{
    // Log.traceln("TargetManager::fromString - BEGIN");

    targetJson.clear();
    DeserializationError err = deserializeJson(targetJson, (const char*)buff);
    if (err)
    {
        Log.errorln("TargetManager::fromString - failed to parse input: '%s'", buff);
        // todo - reset targets??
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
        target->stopDelay = t[KEY_TARGET_END_DELAY];
        targetList.add(target);

        Log.traceln("TargetManager::fromString - target[%d] node ID = %d", i, target->targetNodeId);
    }
    // Log.traceln("TargetManager::fromString - END");
    return true;
}
