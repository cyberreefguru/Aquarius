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
    Event event = (Event)id;
    switch (event)
    {
    case Event::INITIALIZING:
        setStatusIndicator(Color::Orange);
        break;
    case Event::MSG_RECEIVED:
        flashMode = Mode::Flash;
        flashRate = 250;
        setStatusIndicator(Color::Blue);
        break;
    case Event::WAITING:
        flashMode = Mode::HeartBeat;
        flashRate = 150;
        setStatusIndicator(Color::Green);
        break;
    case Event::PROCESSING:
        flashMode = Mode::Flash;
        flashRate = 250;
        setStatusIndicator(Color::Blue);
        break;
    case Event::WIFI_DOWN:
        setStatusIndicator(Color::Magenta);
        break;
    case Event::WIFI_UP:
        setStatusIndicator(Color::Blue);
        break;
    case Event::MQTT_DOWN:
        setStatusIndicator(Color::Purple);
        break;
    case Event::MQTT_UP:
        setStatusIndicator(Color::Blue);
        break;
    case Event::ACTIVE:
        setSystemIndicator(Color::Green);
        break;
    case Event::DEACTIVE:
        setSystemIndicator(Color::Black);
        break;
    case Event::ERROR:
        flashMode = Mode::Flash;
        flashRate = 100;
        setSystemIndicator(Color::Red);
        break;
    default:
        break;
    }
}

void IndicatorManager::flashTask(void *pvParameters)
{
    Log.infoln("Starting flash task. Mode=%d.", flashMode);
    uint8_t hbCounter = 0;
    uint32_t time = millis();

    for (;;)
    {
        uint32_t t = millis();
        if( t > (time + 1000))
        {
            int32_t rssi = WiFi.RSSI();
            stateManager.rssi = rssi;
            time = t;
        }
        if (flashMode == Mode::Solid)
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
