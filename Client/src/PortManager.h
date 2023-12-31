/*
 * Button.h
 *
 *  Created on: Nov 19, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <Adafruit_MCP23X17.h>
#include <FunctionalInterrupt.h>

// #include "ActionEvent.h"
#include "InputEventManager.h"
#include "Button.h"

#define INTR_PIN D0

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
//#include "freertos/portmacro.h"
}

class PortManager
{
public:
    PortManager();
    void initialize();
    uint8_t get();
    uint8_t get(uint8_t pin);
    void set(uint8_t v);
    void set(uint8_t pin, uint8_t value);
    bool isLow(uint8_t pin);
    bool isHigh(uint8_t pin);

protected:
    uint8_t process = false;
    Adafruit_MCP23X17 gpio;
    Button button[5];

    void IRAM_ATTR isr();

    void debounceTask(void *parameter);
    TaskHandle_t debounceTaskHandle = NULL;
    QueueHandle_t debounceQueueHandle = nullptr;

    void handleButtonAction(Button *b, uint16_t allPins);

private:

};


// end of add your includes here
#ifdef __cplusplus
    extern "C"
    {
#endif

    extern PortManager portManager;

#ifdef __cplusplus
} // extern "C"
#endif