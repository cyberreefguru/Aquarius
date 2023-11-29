#include "Gpio.h"
#include "FunctionalInterrupt.h"

#define INTR_PIN D0

Gpio::Gpio() {}

void Gpio::initialize()
{

    pinMode(INTR_PIN, INPUT);

    if (!gpio.begin_I2C())
    {
        Log.fatal("Unable to initialize GPIO I2C");
        while (1);
    }

    gpio.setupInterrupts(true, false, LOW);

    for (uint8_t i = 0; i++; i < 16)
    {
        lastTrigger[i] = 0;
        gpio.pinMode(i, INPUT_PULLUP);
        gpio.setupInterruptPin(i, HIGH);

    }

    // attachInterrupt(digitalPinToInterrupt(INTR_PIN), [this](){
    //     this->isr();
    // }, FALLING);

    attachInterrupt(digitalPinToInterrupt(INTR_PIN), std::bind(&Gpio::isr, this), FALLING);

}

void Gpio::isr()
{



}

void IRAM_ATTR Gpio::isr_callback(void *args)
{
    
}

uint16_t Gpio::get()
{
    values = gpio.readGPIOAB();
    return values;
}

uint8_t Gpio::get(uint8_t pin)
{
    return gpio.digitalRead(pin);
}

void Gpio::set(uint16_t v)
{
    values = v;
    gpio.writeGPIOAB(values);
}

void Gpio::set(uint8_t pin, uint8_t value)
{
    gpio.digitalWrite(pin, value);
}

bool Gpio::isLow(uint8_t pin)
{
    return ((values>>pin)&0x01)==0;
}

bool Gpio::isHigh(uint8_t pin)
{
    return ((values>>pin)&0x01)==1;
}