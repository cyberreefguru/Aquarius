#include "PortManager.h"

PortManager portManager;

PortManager::PortManager() {}

void PortManager::initialize()
{
    Log.traceln("Initializing GPIO...");

    // Set D0 on ESP to be interrupt input
    pinMode(INTR_PIN, INPUT_PULLUP);

    // Initialize I2C bus for GPIO
    if (!gpio.begin_I2C())
    {
        Helper::fatal("Unable to initialize GPIO I2C");
    }

    // Set up port A as output
    for (uint8_t i = 0; i < 8; i++)
    {
        gpio.pinMode(i, OUTPUT);
    }
    gpio.writeGPIOA(0x00);

    // Port B as input with interrupts on LOW
    for (uint8_t i = 8; i < 16; i++)
    {
        gpio.pinMode(i, INPUT_PULLUP);
        gpio.setupInterruptPin(i, CHANGE);
    }

    button[0].initialize(8, ButtonEvent::DOWN);
    button[1].initialize(9, ButtonEvent::RIGHT);
    button[2].initialize(10, ButtonEvent::UP);
    button[3].initialize(11, ButtonEvent::PUSH);
    button[4].initialize(12, ButtonEvent::LEFT);

    // Enable GPIO interrupts
    gpio.setupInterrupts(true, false, CHANGE);

    // Clear any pending interrupts
    gpio.clearInterrupts();

    attachInterrupt(digitalPinToInterrupt(INTR_PIN), std::bind(&PortManager::isr, this), FALLING);

    Log.infoln("Creating debounce task.");
    BaseType_t xReturned = xTaskCreate(
        [](void *pvParameters)
        { portManager.debounceTask(pvParameters); },
        "deounce_task",
        2048,
        NULL,
        tskIDLE_PRIORITY + 2,
        &debounceTaskHandle);
    if (xReturned != pdPASS)
    {
        Helper::fatal("FAILED TO CREATE DEBOUNCE TASK");
    }

    Log.traceln("GPIO Initialization Complete");
}

void IRAM_ATTR PortManager::isr()
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(debounceTaskHandle, &xHigherPriorityTaskWoken);

    // yield processor to other tasks
    portYIELD_FROM_ISR();
}

void PortManager::debounceTask(void *parameter)
{
    Log.infoln("Starting debounce task.");

    uint32_t threadNotification;
    uint32_t notifiedValue;

    uint8_t ticks = 0;
    uint8_t portValue = gpio.readGPIOB();

    while (1)
    {
        threadNotification = xTaskNotifyWait(pdTRUE, ULONG_MAX, &notifiedValue, portMAX_DELAY);
        if (threadNotification == pdPASS)
        {
            uint8_t pin = gpio.getLastInterruptPin();
            uint16_t allPins = gpio.getCapturedInterrupt();
            gpio.clearInterrupts();

            // Log.traceln("Pin: %d, Pins: %X", pin, allPins);

            // Loop through buttons to set state
            for (uint i = 0; i < 5; i++)
            {
                if (button[i].pin == pin)
                {
                    handleButtonAction(&button[i], allPins);
                    break;
                }
            }
        }
    }
}

void PortManager::handleButtonAction(Button *b, uint16_t allPins)
{
    uint32_t now = millis();
    uint16_t state = (((allPins) & (1 << (b->pin))) != 0 ? HIGH : LOW);

    // Log.traceln("Button Action: pin=%d, action=(%d, %s), all=%X, state=%d", b->pin, b->action, ++(b->action), allPins, state);

    if (b->lastState != state)
    {
        // State has changed
        if (now - b->lastTrigger < 20)
        {
            // Too fast; debounce
            Log.traceln("Debounce %d", b->pin);
            b->lastTrigger = now;
            return;
        }
    }
    else
    {
        // No change
        Log.traceln("No state change: %d", b->pin);
        return;
    }

    // Fire event change.
    if (state == LOW)
    {
        // Pressed
        // Log.traceln("PRESSED: %d, %d, %s", b->pin, b->action, ++(b->action));
        if( now - b->lastState < 100 )
        {
            Log.traceln("Press too quickly, ingored");
            b->lastTrigger = now;
        }
        else
        {
            inputEventManager.postEvent(ButtonAction::PRESS, &b->event);
        }
    }
    else
    {
        // Released
        // Log.traceln("RELEASED: %d, %s", b->pin, ++b->action);
        inputEventManager.postEvent(ButtonAction::RELEASE, &b->event);
    }

    b->lastState = state;
    b->lastTrigger = now;
}

uint8_t PortManager::get()
{
    return gpio.readGPIOB();
}

uint8_t PortManager::get(uint8_t pin)
{
    return gpio.digitalRead(pin);
}

void PortManager::set(uint8_t v)
{
    gpio.writeGPIOA(v);
}

void PortManager::set(uint8_t pin, uint8_t value)
{
    gpio.digitalWrite(pin, value);
}

bool PortManager::isLow(uint8_t pin)
{
    return (get(pin) == LOW);
}

bool PortManager::isHigh(uint8_t pin)
{
    return (get(pin) == HIGH);
}