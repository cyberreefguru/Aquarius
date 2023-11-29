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

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}

class Gpio
{
public:
    Gpio();
    void initialize();
    uint16_t get();
    uint8_t get(uint8_t pin);
    void set(uint16_t values);
    void set(uint8_t pin, uint8_t value);
    bool isLow(uint8_t pin);
    bool isHigh(uint8_t pin);
    
protected:
    uint8_t pin;
    Adafruit_MCP23X17 gpio;
    uint16_t values;
    uint32_t lastTrigger[16];
    void isr();
private:
    void IRAM_ATTR isr_callback(void* arg);

};