#pragma once

#include "LiquidCrystal_I2C.h"

#include "navigator.hpp"
#include "pins.hpp"
#include "settings.hpp"
#include "utils.hpp"

namespace app
{
constexpr int VALUE_COLUMN {13};
constexpr float TEMP_IN_C {22.5f};
constexpr float TEMP_OUT_C {-3.5f};

/**
 * @brief View layer of the application. It draws application state on the
 * 16x2 I2C LCD. Every call of `render` clears the screen and draws it again
 * from the passed data, so display does not store any application state.
 *
 */
class Display
{
public:
    /**
     * @brief Construct a new Display object with address and size from `pins` namespace.
     *
     */
    Display() : lcd {pins::LCD_ADDR, pins::LCD_COLS, pins::LCD_ROWS} {}

    /**
     * @brief Initializes LCD controller over I2C. Should be called once inside
     * `setup` function, before any other method.
     *
     */
    void begin()
    {
        lcd.init();
    }

    /**
     * @brief Turns LCD backlight on or off.
     *
     * @param on True to enable backlight.
     */
    void setBacklight(bool on)
    {
        if (on)
            lcd.backlight();
        else
            lcd.noBacklight();
    }

    /**
     * @brief Draws whole screen again, either as menu list or as details
     * of the selected item.
     *
     * @param navigator Current position in the menu.
     * @param settings Current user settings.
     * @param screen Screen to draw.
     */
    void render(const menu::Navigator& navigator, const Settings& settings, Screen screen)
    {
        lcd.clear();

        if (screen == Screen::Detail)
            drawDetail(navigator.selectedItem(), settings);
        else
            drawMenu(navigator, settings);
    }

private:
    /**
     * @brief Returns simulated temperature of the given sensor.
     *
     * @param sensor Sensor identifier, either `SensorIn` or `SensorOut`.
     * @param fahrenheit True to convert result to Fahrenheit.
     * @return float Temperature in the requested unit.
     */
    static float temperature(menu::MenuItemID sensor, bool fahrenheit)
    {
        const float celsius = sensor == menu::MenuItemID::SensorIn ? TEMP_IN_C : TEMP_OUT_C;
        return fahrenheit ? utils::toFahrenheit(celsius) : celsius;
    }

    /**
     * @brief Prints current value of the toggle item at the cursor position.
     * Items without value are ignored.
     *
     * @param id Menu item identifier.
     * @param settings Current user settings.
     */
    void printValue(menu::MenuItemID id, const Settings& settings)
    {
        switch (id)
        {
        case menu::MenuItemID::Power:
            lcd.print(settings.ledPower ? "ON" : "OFF");
            break;
        case menu::MenuItemID::Backlight:
            lcd.print(settings.backlightOn ? "ON" : "OFF");
            break;
        case menu::MenuItemID::Selector:
            lcd.print(settings.selector);
            break;
        case menu::MenuItemID::Units:
            lcd.print(settings.fahrenheit ? 'F' : 'C');
            break;
        default:
            break;
        }
    }

    /**
     * @brief Draws visible page of the current menu level. Each row contains
     * selection marker, item label and item value starting from `VALUE_COLUMN`.
     *
     * @param navigator Current position in the menu.
     * @param settings Current user settings.
     */
    void drawMenu(const menu::Navigator& navigator, const Settings& settings)
    {
        for (int row = 0; row < pins::LCD_ROWS; ++row)
        {
            const int index = navigator.firstVisible() + row;
            if (index >= navigator.parent->childCount)
                break;

            auto& item = navigator.parent->childs[index];

            lcd.setCursor(0, row);
            lcd.print(index == navigator.selected ? settings.selector : ' ');
            lcd.print(item.text);

            lcd.setCursor(VALUE_COLUMN, row);
            printValue(item.id, settings);
        }
    }

    /**
     * @brief Draws detail screen of the leaf menu item. Color items show their
     * PWM level, sensor items show temperature in the selected unit and
     * About item shows author of the project.
     *
     * @param item Selected menu item.
     * @param settings Current user settings.
     */
    void drawDetail(const menu::MenuItem& item, const Settings& settings)
    {
        switch (item.id)
        {
        case menu::MenuItemID::Red:
        case menu::MenuItemID::Green:
        case menu::MenuItemID::Blue:
            lcd.print(item.text);
            lcd.setCursor(0, 1);
            lcd.print(settings.ledLevel[utils::colorChannel(item.id)]);
            break;

        case menu::MenuItemID::SensorIn:
        case menu::MenuItemID::SensorOut:
            lcd.print(item.text);
            lcd.setCursor(0, 1);
            lcd.print(temperature(item.id, settings.fahrenheit), 1);
            lcd.print(utils::DEGREE_CHAR);
            lcd.print(settings.fahrenheit ? 'F' : 'C');
            break;

        case menu::MenuItemID::About:
            lcd.print("Mateusz");
            lcd.setCursor(0, 1);
            lcd.print("Adamowicz");
            break;

        default:
            break;
        }
    }

    LiquidCrystal_I2C lcd;
};
} // namespace app
