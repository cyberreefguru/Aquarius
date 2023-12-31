/*
 * IndicatorManager.h
 *
 *  Created on: Nov 20, 2023
 *      Author: cyberreefguru
 */

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <Adafruit_NeoPixel.h>

#include "ActionEvent.h"
#include "ActionEventManager.h"
#include "StateManager.h"
#include "Color.h"

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}

enum class Mode
{
    Solid=0,
    HeartBeat,
    Flash
};

class IndicatorManager
{
public:
    IndicatorManager();
    void initialize();

protected:
    void clearStatusIndicator(uint32_t color);
    void setStatusIndicator(uint32_t color);
    void setSystemIndicator(uint32_t color);
    void setIndicators(uint32_t color);
    void setIndicators(uint32_t status, uint32_t state);
    void show();
    void show(uint32_t color);
    void show(uint32_t status, uint32_t state);
    void eventHandler(void *args, esp_event_base_t base, int32_t id, void *data);

    void flashTask( void * pvParameters );
    TaskHandle_t flashTaskHandle = NULL;

    uint32_t statusColor = Color::Black;
    uint32_t stateColor = Color::Black;

    uint8_t flashRate = 150;
    Mode flashMode = Mode::Solid;

private:

};

// end of add your includes here
#ifdef __cplusplus
extern "C"
{
#endif

    extern IndicatorManager indicatorManager;

#ifdef __cplusplus
} // extern "C"
#endif