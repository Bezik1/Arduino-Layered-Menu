#pragma once

#include "Arduino.h"

/**
 * @brief Contains low level hardware drivers, like buttons, rotary encoder
 * and RGB LED. Components have no knowledge about the menu or application state.
 *
 */
namespace components
{
/**
 * @brief Push button connected between GPIO pin and GND. Pin uses internal
 * pull-up resistor, so idle level is HIGH and press pulls it LOW. Contact
 * bouncing is filtered in software, by accepting new level only after it
 * remained stable for longer than debounce time.
 *
 */
class Button
{
public:
    /**
     * @brief Construct a new Button object bound to the given pin.
     *
     * @param pin Arduino pin number, to which button is connected.
     * @param debounceTime Minimal time in milliseconds the level must stay stable.
     */
    explicit Button(
        int pin,
        unsigned long debounceTime = DEFAULT_DEBOUNCE_TIME
    ) : pin {pin}, debounceTime {debounceTime} {}

    /**
     * @brief Configures pin as an input with internal pull-up resistor enabled.
     * Should be called once inside `setup` function.
     *
     */
    void begin()
    {
        pinMode(pin, INPUT_PULLUP);
    }

    /**
     * @brief Detects debounced press of the button. Returns true exactly once per
     * physical press, at the moment when stable level changes from HIGH to LOW.
     * Holding the button does not generate further events. It should be called
     * in every iteration of the `loop` function.
     *
     * @return bool True if new press has been detected since the last call.
     */
    bool pressed()
    {
        auto reading = digitalRead(pin);
        if (reading != lastReading)
        {
            lastReading = reading;
            changedAt = millis();
        }
        if (reading != currentValue && millis() - changedAt > debounceTime)
        {
            currentValue = reading;
            return currentValue == LOW;
        }
        return false;
    }

private:
    int pin;
    unsigned long debounceTime;
    int currentValue{HIGH};
    int lastReading{HIGH};
    unsigned long changedAt{0};

    static constexpr auto DEFAULT_DEBOUNCE_TIME{30};
};
} // namespace components
