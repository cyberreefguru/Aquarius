/**
 * @brief Manages sensors
 * @file SensorManager.cpp
 * @date Feb 2, 2024
 * @author cyberreefguru
 */
#include "SensorManager.h"
#include "PreferenceManager.h"

SensorManager sensorManager;

SensorManager::SensorManager() {}

/**
 * @brief initializes the class for use.
 */
void SensorManager::initialize()
{
    // Set D0 on ESP to be interrupt input
    pinMode(CURRENT_SENSOR_PIN, INPUT);
    uint16_t v = analogRead(CURRENT_SENSOR_PIN); // Read to ensure can

    Log.traceln("SensorManager::initialize - creating sensor task.");
    BaseType_t xReturned = xTaskCreate(
        [](void *pvParameters)
        { sensorManager.sensorTask(pvParameters); },
        "sensor_task",
        2048,
        NULL,
        tskIDLE_PRIORITY + 1,
        &sensorTaskHandle);
    if (xReturned != pdPASS)
    {
        Helper::fatal("ServoManager::initialize - FAILED TO CREATE SENSOR TASK");
    }
}

/**
 * @brief Listens for changes in sensors
 * @param pvParameters
 */
void SensorManager::sensorTask(void *pvParameters)
{
    Log.traceln("SensorManager::sensorTask - starting sensor task.");
    state = SensorState::WAITING;
    uint16_t click = 0;
    uint16_t mvPerAmp = 66;
    uint32_t watt = 0;
    double sensorValue = 0.0;
    double vRMS = 0.0;
    double aRMS = 0.0;

    // Add event handler
    actionEventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
                                       { sensorManager.eventHandler(arg, base, id, data); });



    // Sample current value to determine noise floor
    long avg = 0;
    for (int i = 0; i < 100; i++)
    {
        avg += analogRead(CURRENT_SENSOR_PIN);
        vTaskDelay(pdMS_TO_TICKS(2));
    }
    offset = (avg / 100);
    Log.traceln("SensorManager::sensorTask - offset=%d", offset);

    // Start looping thread
    for (;;)
    {
        // Get current value of sensor input
        sensorValue = getSensorValue();
        vRMS = (sensorValue/2.0) * 0.707;
        aRMS = ((vRMS * 1000)/mvPerAmp)-0.3;
        watt = (aRMS*120/1.2);
        //Log.traceln("SensorManager::sensorTask - v=%F, vRMS=%F, aRMS=%F, w=%F", voltage, vRMS, aRMS, watt);

        switch (state)
        {
        case SensorState::WAITING:
            break;
        case SensorState::FALLING_EDGE:
            break;
        case SensorState::RISING_EDGE:
            break;
        }
    }
}

/**
 * @brief Reads sensor input for 1 second and sets the min and max voltage read
 * @return returns the median voltage during the sample period
 */
float SensorManager::getSensorValue()
{
    uint16_t clicks = 0;
    uint16_t minValue = 4095;
    uint16_t maxValue = 0;
    float result = 0;

    while(clicks < 1000 )
    {
        uint16_t v = analogRead(CURRENT_SENSOR_PIN);
        if( v > maxValue )
        {
            maxValue = v;
        }
        if( v < minValue )
        {
            minValue = v;
        }
        clicks++;
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    //Log.traceln("SensorManager::getSensorValue - min=%d, max=%d", minValue, maxValue);
    result = ((maxValue - minValue) * MEASURED_VCC)/4096.0;

    return result;      
}


/**
 * @brief Receives system events and sets appropriate flags for future reference
 * @param arg
 * @param base
 * @param id the event triggering this handler
 * @param data
 */
void SensorManager::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    ActionEvent event = (ActionEvent)id;

    switch (event)
    {
    case ActionEvent::INITIALIZING:
        break;
    case ActionEvent::WAITING:
        break;
    case ActionEvent::MSG_RECEIVED:
        break;
    case ActionEvent::PROCESSING:
        break;
    case ActionEvent::ACTIVE:
        break;
    case ActionEvent::DEACTIVE:
        break;
    case ActionEvent::WIFI_DOWN:
        break;
    case ActionEvent::WIFI_UP:
        break;
    case ActionEvent::MQTT_DOWN:
        break;
    case ActionEvent::MQTT_UP:
        break;
    case ActionEvent::CONFIGURE:
        break;
    case ActionEvent::NODE_ID_CHANGE:
        break;
    case ActionEvent::ERROR:
        break;
    default:
        break;
    }
}
