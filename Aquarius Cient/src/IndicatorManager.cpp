/*
 * IndicatorManager.cpp
 *
 *  Created on: Nov 20, 2023
 *      Author: cyberreefguru
 */

#include "IndicatorManager.h"

Adafruit_NeoPixel pixels(2, D7, NEO_RGB + NEO_KHZ800);

IndicatorManager indicatorManager;

IndicatorManager::IndicatorManager() {}

void IndicatorManager::initialize()
{
    pixels.begin();
    pixels.setBrightness(25);
    // setIndicators(Color::Red);
    // delay(250);
    // setIndicators(Color::Green);
    // delay(250);
    // setIndicators(Color::Blue);
    // delay(250);
    setIndicators(Color::Orange, Color::Black);

    eventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
                                 { indicatorManager.eventHandler(arg, base, id, data); });

    flashMode = Mode::Solid;
    Log.infoln("Creating flash task.");
    BaseType_t xReturned = xTaskCreate(
        [](void *pvParameters)
        { indicatorManager.flashTask(pvParameters); },
        "flash_task",
        1024,
        (void *)1,
        tskIDLE_PRIORITY,
        &flashTaskHandle);
    if (xReturned != pdPASS)
    {
        Log.errorln("FAILED TO CREATE FLASH TASK");
    }
}

void IndicatorManager::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    State state = (State)id;
    switch (state)
    {
    case State::RECEIVING:
    case State::PROCESSING:
    case State::SENDING:
        flashMode = Mode::Flash;
        flashRate = 250;
        break;
    case State::WAITING:
        flashMode = Mode::HeartBeat;
        flashRate = 150;
        break;
    case State::ERROR:
        flashMode = Mode::Flash;
        flashRate = 100;
        break;
    default:
        break;
    }
}

void IndicatorManager::flashTask(void *pvParameters)
{
    Log.infoln("Starting flash task. Mode=%d.", flashMode);
    uint8_t hbCounter = 0;
    for (;;)
    {
        if(flashMode == Mode::Solid)
        {
            show();
            vTaskDelay(pdMS_TO_TICKS(flashRate));
        }
        if (flashMode == Mode::HeartBeat)
        {
            hbCounter++;
            switch (hbCounter)
            {
            case 1:
                show();
                break;
            case 3:
                clearStatusIndicator(Color::Black);
                break;
            case 5:
                show();
                break;
            case 7:
                clearStatusIndicator(Color::Black);
                break;
            case 14:
                hbCounter = 0;
                break;
            }
            vTaskDelay(pdMS_TO_TICKS(flashRate));
        }
        else if (flashMode == Mode::Flash)
        {
            show();
            vTaskDelay(pdMS_TO_TICKS(flashRate));
            clearStatusIndicator(Color::Black);
            vTaskDelay(pdMS_TO_TICKS(flashRate));
        }
    }
}

void IndicatorManager::clearStatusIndicator(uint32_t color)
{
    pixels.setPixelColor(0, color);
    pixels.show();
}

void IndicatorManager::setStatusIndicator(uint32_t color)
{
    statusColor = color;
}

void IndicatorManager::setSystemIndicator(uint32_t color)
{
    stateColor = color;
}

void IndicatorManager::setIndicators(uint32_t status, uint32_t state)
{
    statusColor = status;
    stateColor = state;
}

void IndicatorManager::setIndicators(uint32_t color)
{
    statusColor = color;
    stateColor = color;
}
void IndicatorManager::show()
{
    pixels.setPixelColor(0, statusColor);
    pixels.setPixelColor(1, stateColor);
    pixels.show();
}

void IndicatorManager::show(uint32_t status, uint32_t state)
{
    statusColor = status;
    stateColor = state;
    show();
}

void IndicatorManager::show(uint32_t color)
{
    statusColor = color;
    stateColor = color;
    show();
}
