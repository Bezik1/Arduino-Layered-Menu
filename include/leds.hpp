#pragma once

#include "Arduino.h"

#include "pins.hpp"
#include "settings.hpp"

namespace components
{
/**
 * @brief Contains functions driving three channels of the RGB LED with PWM.
 *
 */
namespace leds
{
constexpr int LED_PINS[3] {pins::LED_RED, pins::LED_GREEN, pins::LED_BLUE};

/**
 * @brief Configures all LED pins as outputs. Should be called once inside
 * `setup` function.
 *
 */
inline void begin()
{
    for (auto& pin : LED_PINS)
        pinMode(pin, OUTPUT);
}

/**
 * @brief Applies LED settings to the hardware. When LED power is enabled each
 * channel is driven with its PWM level, otherwise all channels are turned off.
 *
 * @param settings Current user settings.
 */
inline void apply(const app::Settings& settings)
{
    for (int i = 0; i < 3; ++i)
        analogWrite(LED_PINS[i], settings.ledPower ? settings.ledLevel[i] : 0);
}
} // namespace leds
} // namespace components
