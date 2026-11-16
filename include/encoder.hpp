#pragma once

#include "Arduino.h"

namespace components
{
/**
 * @brief Incremental rotary encoder with two quadrature outputs A and B.
 * Channel A is monitored with pin change interrupt. On every falling edge
 * of A, level of B determines direction of the rotation. Steps are accumulated
 * inside the interrupt and collected by the main loop with `read` method.
 * Application must define ISR for the port of channel A and call
 * `handleInterrupt` inside of it.
 *
 */
class Encoder
{
public:
    /**
     * @brief Construct a new Encoder object bound to the given pins.
     *
     * @param pinA Pin connected to the channel A, used as interrupt source.
     * @param pinB Pin connected to the channel B, used to detect direction.
     * @param debounceTime Minimal interval in milliseconds between two accepted edges.
     */
    Encoder(
        int pinA,
        int pinB,
        unsigned long debounceTime = DEFAULT_DEBOUNCE_TIME
    ) : pinA {pinA}, pinB {pinB}, debounceTime {debounceTime} {}

    /**
     * @brief Configures both pins as inputs with pull-up resistors and enables
     * pin change interrupt on channel A. Should be called once inside `setup` function.
     *
     */
    void begin()
    {
        pinMode(pinA, INPUT_PULLUP);
        pinMode(pinB, INPUT_PULLUP);
        enablePinChangeInterrupt(pinA);
    }

    /**
     * @brief Returns and clears number of steps accumulated since the previous call.
     * Counter is read and reset with interrupts disabled, so no steps are lost
     * between both operations.
     *
     * @return int Signed number of steps. Sign determines direction of the rotation.
     */
    int read()
    {
        noInterrupts();
        const int value = counter;
        counter = 0;
        interrupts();
        return value;
    }

    /**
     * @brief Processes pin change event. Should be called only from the ISR.
     * Rising edges of channel A and edges arriving within debounce time
     * are ignored.
     *
     */
    void handleInterrupt()
    {
        if (digitalRead(pinA) != LOW)
            return;

        auto now = millis();
        if (now - lastInterruptTime <= debounceTime)
            return;

        lastInterruptTime = now;
        if (digitalRead(pinB) == LOW)
            --counter;
        else
            ++counter;
    }

private:
    /**
     * @brief Enables pin change interrupt for the singular pin. It sets pin bit
     * in PCMSK register, clears pending flag in PCIFR and enables port group in PCICR.
     *
     * @param pin Arduino pin number.
     */
    static void enablePinChangeInterrupt(int pin)
    {
        *digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin));
        PCIFR |= bit(digitalPinToPCICRbit(pin));
        PCICR |= bit(digitalPinToPCICRbit(pin));
    }

    int pinA;
    int pinB;
    unsigned long debounceTime;
    unsigned long lastInterruptTime{0};
    volatile int counter{0};

    static constexpr auto DEFAULT_DEBOUNCE_TIME {10};
};
} // namespace components
