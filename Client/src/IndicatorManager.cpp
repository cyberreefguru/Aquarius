/*
 * IndicatorManager.cpp
 *
 *  Created on: Nov 20, 2023
 *      Author: cyberreefguru
 */

#include "IndicatorManager.h"

Adafruit_NeoPixel indicators(2, D7, NEO_RGB + NEO_KHZ800);

IndicatorManager indicatorManager;

IndicatorManager::IndicatorManager() {}

/**
 * @brief Initializes the indicator manager
 * 
 */
void IndicatorManager::initialize()
{
    Log.traceln("IndicatorManager::initialize - BEGIN");

    indicators.begin();
    indicators.setBrightness( prefManager.getLedBrightness() );
    setIndicators(prefManager.getConfigureColor(), prefManager.getDeactiveColor());

    actionEventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
                                 { indicatorManager.eventHandler(arg, base, id, data); });

    flashMode = Mode::Solid;
    Log.traceln("IndicatorManager::initialize - Creating flash task.");
    BaseType_t xReturned = xTaskCreate(
        [](void *pvParameters)
        { indicatorManager.flashTask(pvParameters); },
        "flash_task",
        1024,
        NULL,
        tskIDLE_PRIORITY+1,
        &flashTaskHandle);
    if (xReturned != pdPASS)
    {
        Log.errorln("IndicatorManager::initialize - FAILED TO CREATE FLASH TASK");
    }
    Log.traceln("IndicatorManager::initialize - END");
}

/**
 * @brief Responses to action events to change indicators as required.
 * 
 * @param arg 
 * @param base 
 * @param id 
 * @param data 
 */
void IndicatorManager::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    ActionEvent event = (ActionEvent)id;
    switch (event)
    {
    case ActionEvent::INITIALIZING:
        setStatusIndicator(prefManager.getInitializeColor());
        break;
    case ActionEvent::MSG_RECEIVED:
        flashMode = Mode::Flash;
        flashRate = 200;
        setStatusIndicator(prefManager.getReceiveColor());
        break;
    case ActionEvent::WAITING:
        flashMode = Mode::HeartBeat;
        flashRate = 125;
        setStatusIndicator(prefManager.getWaitColor());
        break;
    case ActionEvent::PROCESSING:
        flashMode = Mode::Flash;
        flashRate = 200;
        setStatusIndicator(prefManager.getProcessColor());
        break;
    case ActionEvent::WIFI_DOWN:
        setStatusIndicator(prefManager.getWifiDownColor());
        break;
    case ActionEvent::WIFI_UP:
        setStatusIndicator(prefManager.getWifiUpColor());
        break;
    case ActionEvent::MQTT_DOWN:
        setStatusIndicator(prefManager.getMqttDownColor());
        break;
    case ActionEvent::MQTT_UP:
        setStatusIndicator(prefManager.getMqttUpColor());
        break;
    case ActionEvent::ACTIVE:
        setSystemIndicator(prefManager.getActiveColor());
        break;
    case ActionEvent::DEACTIVE:
        setSystemIndicator(prefManager.getDeactiveColor());
        break;
    case ActionEvent::CONFIGURE:
        flashMode = Mode::Flash;
        flashRate = 200;
        setStatusIndicator(prefManager.getConfigureColor());
        break;
    case ActionEvent::ERROR:
        flashMode = Mode::Flash;
        flashRate = 100;
        setSystemIndicator(prefManager.getErrorColor());
        break;
    default:
        break;
    }
}

/**
 * @brief thread that keeps indicators up to date
 * @param pvParameters 
 */
void IndicatorManager::flashTask(void *pvParameters)
{
    Log.traceln("IndicatorManager::flashTask - starting flash task. Flash mode=%d.", flashMode);

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
            // Log.infoln("Indicator Task Memory: %d", uxTaskGetStackHighWaterMark(NULL));

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

void IndicatorManager::setBrightness(uint8_t b)
{
    indicators.setBrightness( b );
}

void IndicatorManager::clearStatusIndicator(uint32_t color)
{
    indicators.setPixelColor(0, color);
    indicators.show();
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
    indicators.setPixelColor(0, statusColor);
    indicators.setPixelColor(1, stateColor);
    indicators.show();
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
