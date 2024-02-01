#include <Arduino.h>
#include <ArduinoLog.h>
#include <Adafruit_MCP23X17.h>

#include "ActionEventManager.h"
#include "MessageBroker.h"
#include "ActionEvent.h"
#include "ActionEventManager.h"
#include "IndicatorManager.h"
#include "CommandManager.h"
#include "PreferenceManager.h"
#include "PortManager.h"
#include "MenuManager.h"
#include "TargetManager.h"
#include "DisplayManager.h"

// IPAddress server(192, 168, 30, 210);

// Adafruit_MCP23X17 gpio;


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

  // Set up action event manager
  // This should be set up before other managers
  // so they can post events as required
  actionEventManager.initialize();

  // Set up input event manager
  // Handles button pushes and other inputs
  inputEventManager.initialize();

  // Initialize display
  displayManager.initialize();

  // Set up state manager - tracks state changes
  stateManager.initialize();

  // Set up and initialize LEDs
  indicatorManager.initialize();

  // Initialize command manager
  commandManager.initialize();

  // Initialize ports
  portManager.initialize();

  // Initialize target manager
  targetManager.initialize();

  // Initialize menu
  menuManager.initialize();

  // Fire initialization event
  actionEventManager.postEvent(ActionEvent::INITIALIZING);

  // Set initial screen
  displayManager.setInitialScreen();

  // Initialize WIFI and MQTT
  messageBroker.initialize();


  // actionEventManager.postEvent(ActionEvent::WAITING);

    // if (!gpio.begin_I2C())
    // {
    //     Log.fatalln("Unable to initialize GPIO I2C");
    //     while (1);
    // }
    // else
    // {
    //   Log.infoln("GPIO initialized!");
    // }
    // for (uint8_t i = 0; i<8; i++)
    // {
    //     Log.infoln("Configuring %i pin", i);
    //     gpio.pinMode(i, OUTPUT);
    // }
    // Log.infoln("GPIO Configured!");

    // // gpio.pinMode(0, OUTPUT);
    // // gpio.pinMode(1, OUTPUT);
    // // gpio.pinMode(7, OUTPUT);
    // gpio.digitalWrite(1,0);
    // gpio.writeGPIOA(0x00);

  Log.infoln("Initialization complete");
}

void loop()
{
    portManager.set(0, HIGH);
    portManager.set(7, LOW);
    // // uint16_t p = portManager.get();
    // // Log.infoln("high: value: %x", p);
    // gpio.digitalWrite(7, HIGH);
    //  gpio.digitalWrite(0, LOW);
   delay(500);
    portManager.set(0, LOW);
    portManager.set(7, HIGH);
    // // p = portManager.get();
    // // Log.infoln("low: value: %x", p);
    // gpio.digitalWrite(7, LOW);
    //  gpio.digitalWrite(0, HIGH);
    delay(500);
    //Log.infoln("port value: %X", portManager.get());

    //vTaskDelete(nullptr);
}

