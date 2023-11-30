#include <Arduino.h>
#include <ArduinoLog.h>
// #include <WiFi.h>
#include "EventManager.h"
#include "MessageBroker.h"
#include "Event.h"
#include "EventManager.h"
#include "IndicatorManager.h"
#include "CommandManager.h"

#include "Display.h"

// IPAddress server(192, 168, 30, 210);

/**
 * Sets up the hardware and software
*/
void setup()
{
  Serial.begin(115200);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.infoln("Starting Program");

  // Set up event manager
  // This should be set up first so other classes
  // can post events as required
  eventManager.initialize();

  // Set up and initialize LEDs
  indicatorManager.initialize();

  // Initialize display
  display.initialize();

  // Set up state manager
  stateManager.initialize();

  // Initialize command manager
  commandManager.initialize();

  // Fire initialization event
  eventManager.postEvent(Event::INITIALIZING);

  
  // Initialize WIFI and MQTT
  messageBroker.initialize();
  
  //eventManager.postEvent(Event::WAITING);

  Log.infoln("Initialization complete");
}

void loop()
{
  vTaskDelete(nullptr);
  // int32_t rssi = WiFi.RSSI();
  // stateManager.rssi = rssi;
  //Log.infoln("Signal Strength %d", stateManager.rssi);
  // eventManager.postEvent(Event::WAITING);
  //vTaskDelay(1000);
  // delay(1000);
}