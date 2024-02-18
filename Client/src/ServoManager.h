/**
 * @brief Manages servos
 * @file ServoManager.h
 * @date Feb 16, 2024
 * @author cyberreefguru
 */
#ifndef ServoManager_H
#define ServoManager_H

#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <Servo.h>

#include "Hardware.h"
#include "ActionEvent.h"

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}

class ServoManager
{
public:
    ServoManager();
    void initialize();

protected:
    QueueHandle_t servoQueueHandle = nullptr;
    TaskHandle_t sensorTaskHandle = NULL;
    void eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data);
    void servoTask(void *pvParameters);
    void setServoPosition(float *position);
    void togglePosition();

    bool move = false;
    float currentPosition = 0.0;
    float savedPosition = 0.0;
    float activePosition = 0.0;
    float deactivePosition = 0.0;
    float newPosition = 0.0;

    double speed = 180.0;
    double ke = 0.0;
    float ye;
    Servo servo = Servo();

};

// end of add your includes here
#ifdef __cplusplus
extern "C"
{
#endif

    extern ServoManager servoManager;

#ifdef __cplusplus
} // extern "C"
#endif

#endif