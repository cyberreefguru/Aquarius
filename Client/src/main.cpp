#include <Arduino.h>
#include <ArduinoLog.h>
// #include <WiFi.h>
#include "EventManager.h"
#include "MessageBroker.h"
#include "Event.h"
#include "EventManager.h"
#include "IndicatorManager.h"
#include "CommandManager.h"
#include "PreferenceManager.h"

#include "DisplayManager.h"

// IPAddress server(192, 168, 30, 210);

/**
 * Sets up the hardware and software
 */
void setup()
{
  Serial.begin(115200);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.infoln("Starting Program");

  // Initialize preferences
  prefManager.initialize();

  // Set up event manager
  // This should be set up before other managers
  // so they can post events as required
  eventManager.initialize();

  // Set up state manager - tracks state changes
  stateManager.initialize();

  // Set up and initialize LEDs
  indicatorManager.initialize();

  // Initialize display
  displayManager.initialize();

  // Initialize command manager
  commandManager.initialize();

  // Fire initialization event
  eventManager.postEvent(Event::INITIALIZING);

  // Initialize WIFI and MQTT
  messageBroker.initialize();

  // eventManager.postEvent(Event::WAITING);

  Log.infoln("Initialization complete");
}

void loop()
{
  vTaskDelete(nullptr);
}