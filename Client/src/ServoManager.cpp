/**
 * @brief Manages servos
 * @file ServoManager.cpp
 * @date Feb 2, 2024
 * @author cyberreefguru
 */
#include "ServoManager.h"
#include "PreferenceManager.h"
#include "ActionEventManager.h"
#include "IndicatorManager.h"

ServoManager servoManager;

ServoManager::ServoManager() {}

/**
 * @brief initializes the class for use.
 */
void ServoManager::initialize()
{
    // Attach servo
    servo.attach(SERVO_PIN);

    // Add event handler
    actionEventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
                                       { servoManager.eventHandler(arg, base, id, data); });

    // Create movement queue
    servoQueueHandle = xQueueCreate(5, sizeof(float));
    if (servoQueueHandle == NULL)
    {
        Helper::fatal("ServoManager::initialize - failed to create command queue");
    }
    else
    {
        Log.traceln("ServoManager::initialize - Queue created! Creating servo task...");
    }

    // Create servo task
    BaseType_t xReturned = xTaskCreate(
        [](void *pvParameters)
        { servoManager.servoTask(pvParameters); },
        "servo_task",
        2048,
        NULL,
        tskIDLE_PRIORITY + 1,
        &sensorTaskHandle);
    if (xReturned != pdPASS)
    {
        Helper::fatal("ServoManager::initialize - FAILED TO CREATE SERVO TASK");
    }
}

/**
 * @brief Listens for changes in sensors
 * @param pvParameters
 */
void ServoManager::servoTask(void *pvParameters)
{
    Log.traceln("ServoManager::servoTask - starting servo task.");

    // Read current position and limits
    activePosition = prefManager.getServoActivePosition();
    deactivePosition = prefManager.getServoDeactivePosition();
    savedPosition = prefManager.getServoPosition();

    ye = servo.write(SERVO_PIN, savedPosition, speed, ke);
    currentPosition = servo.read(SERVO_PIN);
    
    Log.infoln("ServoManager::servoTask - act=%F, deact=%F, saved=%F cur=%F, ye=%F",
            activePosition, deactivePosition, savedPosition, currentPosition, ye);

    // Start looping thread
    for (;;)
    {
        // wait until new position is received
        if (xQueueReceive(servoQueueHandle, &newPosition, portMAX_DELAY) == pdPASS)
        {
            actionEventManager.postEvent(ActionEvent::PROCESSING);
            currentPosition = servo.read(SERVO_PIN);
            Log.infoln("ServoManager::servoTask - curr pos=%F, new pos=%F", currentPosition, newPosition);

            if (currentPosition == newPosition)
            {
                Log.warningln("ServoManager::servoTask - servo at new position already");
            }
            else
            {
                move = true;
                while (move)
                {
                    ye = servo.write(SERVO_PIN, newPosition, speed, ke);
                    // Log.infoln("ServoManager::servoTask - ye=%F", ye);
                    if (newPosition > currentPosition)
                    {
                        if (ye >= 1.0)
                        {
                            move = false;
                        }
                    }
                    else if (newPosition < currentPosition)
                    {
                        if (ye <= 0.0)
                        {
                            move = false;
                        }
                    }
                    vTaskDelay(pdMS_TO_TICKS(3));
                }
                Log.infoln("ServoManager::servoTask - reached servo limit: %F", newPosition);
                currentPosition = newPosition;
                prefManager.set(KEY_SERVO_POSITION, newPosition);
                savedPosition = newPosition;
            }
            actionEventManager.postEvent(ActionEvent::COMMAND_COMPLETE);
        }
    }
}

/**
 * @brief Receives system events and sets appropriate flags for future reference
 * @param arg
 * @param base
 * @param id the event triggering this handler
 * @param data
 */
void ServoManager::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    ActionEvent event = (ActionEvent)id;
    //Log.traceln("ServoManager::eventHandler - %s", ++event);
    switch (event)
    {
    case ActionEvent::INITIALIZING:
        break;
    case ActionEvent::WAITING:
        // togglePosition();
        // if (currentPosition != savedPosition)
        // {
        //     Log.infoln("ServoManager::eventHandler - moving servo to saved position");
        //     setServoPosition(&savedPosition);
        // }
        break;
    case ActionEvent::MSG_RECEIVED:
        break;
    case ActionEvent::PROCESSING:
        break;
    case ActionEvent::ACTIVE:
        setServoPosition(&activePosition);
        break;
    case ActionEvent::DEACTIVE:
        setServoPosition(&deactivePosition);
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
        // togglePosition();
        break;
    case ActionEvent::NODE_ID_CHANGE:
        break;
    case ActionEvent::ERROR:
        break;
    default:
        break;
    }
}

void ServoManager::setServoPosition(float *pos)
{
    currentPosition = servo.read(SERVO_PIN);
    Log.infoln("ServoManager::setServoPosition - curr pos=%F, new pos=%F", currentPosition, *pos);
    if (*pos == currentPosition)
    {
        Log.errorln("ServoManager::setServoPosition - servo is already at specified position");
        return;
    }

    if (xQueueSend(servoQueueHandle, pos, portMAX_DELAY) != pdPASS)
    {
        Log.errorln("ServoManager::setServoPosition - unable to send message to queue!");
    }
    else
    {
        Log.infoln("ServoManager::setServoPosition - sent message to queue!");
    }
}

void ServoManager::togglePosition()
{
    if (currentPosition == activePosition)
    {
        setServoPosition(&deactivePosition);
    }
    else if (currentPosition == deactivePosition)
    {
        setServoPosition(&activePosition);
    }
    else
    {
        Log.errorln("ServoManager::togglePosition - servo not in open or closed position - %F",currentPosition);
        setServoPosition(&activePosition);
    }
}
