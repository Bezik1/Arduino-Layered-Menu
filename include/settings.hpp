#pragma once

/**
 * @brief Contains application layer: user settings, input handling
 * and rendering of the application state on the LCD.
 *
 */
namespace app
{
constexpr int LEVEL_MAX {255};
constexpr int LEVEL_STEP {15};

enum class Screen { Menu, Detail };

/**
 * @brief Holds all values, which can be changed by the user through the menu:
 * LED power and PWM levels, LCD backlight, temperature unit and character
 * marking selected menu item.
 *
 */
struct Settings
{
    bool ledPower {false};
    int ledLevel[3] {LEVEL_MAX, LEVEL_MAX, LEVEL_MAX};
    bool backlightOn {true};
    bool fahrenheit {false};
    char selector {'>'};
};
} // namespace app
