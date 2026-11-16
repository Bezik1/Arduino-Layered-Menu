#pragma once

#include "menuItem.hpp"

/**
 * @brief Contains helper functions and constants shared across the application.
 *
 */
namespace utils
{
constexpr char DEGREE_CHAR {'\xDF'};

/**
 * @brief Maps color menu item to the index of the LED channel.
 *
 * @param id Menu item identifier.
 * @return int 0 for red, 1 for green, 2 for blue and -1 for any other item.
 */
inline int colorChannel(menu::MenuItemID id)
{
    switch (id)
    {
    case menu::MenuItemID::Red:
        return 0;
    case menu::MenuItemID::Green:
        return 1;
    case menu::MenuItemID::Blue:
        return 2;
    default:
        return -1;
    }
}

/**
 * @brief Converts temperature from Celsius to Fahrenheit.
 *
 * @param celsius Temperature in degrees Celsius.
 * @return float Temperature in degrees Fahrenheit.
 */
inline float toFahrenheit(float celsius)
{
    return celsius * 9.0f / 5.0f + 32.0f;
}
} // namespace utils
