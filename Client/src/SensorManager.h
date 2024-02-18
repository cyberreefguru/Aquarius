/**
 * @brief Manages sensors
 * @file SensorManager.h
 * @date Feb 2, 2024
 * @author cyberreefguru
 */
#ifndef SensorManager_H
#define SensorManager_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>

#include "Hardware.h"
#include "ActionEvent.h"
#include "ActionEventManager.h"

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}

#define SENSOR_HYSTERESIS 50

#define MEASURED_VCC       3.318

#define ACS758_SENSITIVITY 40e-3    // 40mV per AMP
#define ACS758_NOISE       10e-3    // 10mV noise
#define ACS758_OFFSET_LIM  35e-3    // +/-35mV Max offset.
#define MAINS_VOLTS_RMS    120      // 240 or 120 Usually.
#define V_PER_LSB          (MEASURED_VCC/4096.0)
#define ACS758_NOISE_LSB   (ACS758_NOISE/V_PER_LSB) // Noise in LSBs

#define MIN_LSB            (ACS758_NOISE_LSB*1.5) // Ignore system noise


/**
 * @brief Describes which information is displayed
 */
enum class SensorState
{
    WAITING=0,
    RISING_EDGE,
    FALLING_EDGE,
} ;
inline constexpr unsigned operator+ (SensorState const val) { return static_cast<unsigned>(val); }
inline const char* operator++(SensorState a)
{
    switch (a)
    {
    case SensorState::WAITING:
        return "WAITING";
        break;
    case SensorState::RISING_EDGE:
        return "RISING_EDGE";
        break;
    case SensorState::FALLING_EDGE:
        return "FALLING_EDGE";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}



class SensorManager
{
public:
    SensorManager();
    void initialize();

protected:
    TaskHandle_t sensorTaskHandle = NULL;
    void eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data);
    void sensorTask(void *pvParameters);
    float getSensorValue();
    
    SensorState state = SensorState::WAITING;

    uint32_t offset = 2048;

    float sensorCurrent = 0.0;
    float voltage = 0.0;
};

// end of add your includes here
#ifdef __cplusplus
extern "C"
{
#endif

    extern SensorManager sensorManager;

#ifdef __cplusplus
} // extern "C"
#endif

#endif