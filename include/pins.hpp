#pragma once

#include "pins_arduino.h"

/**
 * @brief Contains pin mapping of the Arduino Uno board and LCD parameters.
 *
 */
namespace pins
{
constexpr auto ADC_PIN{A0};
constexpr auto TEMPERATURE_SENSOR{A1};

constexpr auto LED_GREEN {5};
constexpr auto LED_RED {6};
constexpr auto LED_BLUE {3};

constexpr auto RED_BUTTON {2};
constexpr auto GREEN_BUTTON {4};

constexpr auto ENCODER_A {A2};
constexpr auto ENCODER_B {A3};

constexpr auto LCD_ADDR {0x27};
constexpr auto LCD_COLS {16};
constexpr auto LCD_ROWS{2};
} // namespace pins
