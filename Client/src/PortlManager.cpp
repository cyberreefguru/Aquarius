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

    button[0].initialize(8);
    button[1].initialize(9);
    button[2].initialize(10);
    button[3].initialize(11);
    button[4].initialize(12);

    // Enable GPIO interrupts
    gpio.setupInterrupts(true, false, CHANGE);

    // Clear any pending interrupts
    gpio.clearInterrupts();

    attachInterrupt(digitalPinToInterrupt(INTR_PIN), std::bind(&PortManager::isr, this), FALLING);

    // eventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
    //                             { portManager.eventHandler(arg, base, id, data); });

    // values = gpio.readGPIOAB();

    // Log.infoln("Creating port debounce queue");
    // debounceQueueHandle = xQueueCreate(10, 1);
    // if (debounceQueueHandle == NULL)
    // {
    //     Helper::fatal("Failed to create debounce queue");
    // }

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
    // process = true;
    // xQueueSend(debounceQueueHandle, &process, portMAX_DELAY);

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

    // Read baseline value
    // values = gpio.readGPIOB();
    // Log.infoln("port value: %X", values);

    while (1)
    {
        // delay(100);
        // uint8_t v = gpio.readGPIOB();
        // // test if some thing has changed
        // if( v != portValue)
        // {
        //     // Log.infoln("v: %X, read: %X", portValue, v);
        //     // Current port value != saved value so something changed
        //     // Increment tick counter
        //     ticks++;
        //     if( ticks > 2 )
        //     {
        //         // Value has been constant for >200ms
        //         // Trap value and signal change
        //         portValue = v;
        //         ticks = 0;
        //         // Log.infoln("Port Changed - v: %X, read: %X", portValue, v);

        //         values = v;
        //         // Fire event
        //         eventManager.postEvent(Event::IO_INTERRUPT);
        //     }
        // }

        // if (xQueueReceive(debounceQueueHandle, &process, portMAX_DELAY) == pdPASS)
        // {
        //     Log.infoln("Processing interrupt");
        //     uint8_t p = gpio.getLastInterruptPin();
        //     uint16_t v = gpio.readGPIOAB();
        //     Log.infoln("Last Interrupt Pin: %d", p);
        //     Log.infoln("port value: %X", v);
        //     // values |= 0x01<<p;
        //     gpio.clearInterrupts();
        //     eventManager.postEvent(Event::IO_INTERRUPT);
        //     process = false;
        //     Log.infoln("Interrupt complete");
        // }

        threadNotification = xTaskNotifyWait(pdTRUE, ULONG_MAX, &notifiedValue, portMAX_DELAY);
        if (threadNotification == pdPASS)
        {
            uint8_t pin = gpio.getLastInterruptPin();
            uint16_t allPins = gpio.getCapturedInterrupt();
            gpio.clearInterrupts();

            Log.infoln("Pin: %d, Pins: %X", pin, allPins);

            // Loop through buttons to set state
            for (uint i = 0; i < 5; i++)
            {
                if (button[i].pin = pin)
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

    Log.infoln("Button Action: pin=%d, all=%X, state=%d", b->pin, allPins, state);

    if (b->lastState != state)
    {
        // State has changed
        if (now - b->lastTrigger < 20)
        {
            // Too fast; debounce
            Log.infoln("Debounce %d", b->pin);
            b->lastTrigger = now;
            return;
        }
    }
    else
    {
        // No change
        Log.infoln("No state change: %d", b->pin);
        return;
    }

    // Fire event change.
    if (state == LOW)
    {
        // Pressed
        Log.infoln("PRESSED: %d", b->pin);
    }
    else
    {
        // Released
        Log.infoln("RELEASED: %d", b->pin);
    }

    b->lastState = state;
    b->lastTrigger = now;
}

void PortManager::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    Event event = (Event)id;
    switch (event)
    {
    case Event::INITIALIZING:
        break;
    case Event::WAITING:
        break;
    case Event::MSG_RECEIVED:
        break;
    case Event::PROCESSING:
        break;
    case Event::ACTIVE:
        break;
    case Event::DEACTIVE:
        break;
    case Event::WIFI_DOWN:
        break;
    case Event::WIFI_UP:
        break;
    case Event::MQTT_DOWN:
        break;
    case Event::MQTT_UP:
        break;
    case Event::NODE_ID_CHANGE:
        break;
    case Event::ERROR:
        break;
    case Event::IO_INTERRUPT:
        // Log.infoln("IO Interrupt: %X", values);
        // values = 0;
        break;
    default:
        break;
    }
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