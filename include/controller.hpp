#pragma once

#include "Arduino.h"

#include "navigator.hpp"
#include "settings.hpp"
#include "utils.hpp"

namespace app
{
/**
 * @brief Central state machine of the application. It owns menu position,
 * user settings and currently displayed screen, and translates input events
 * into state changes. Controller does not access hardware directly, so
 * outputs should be refreshed by the caller after each event.
 *
 */
struct Controller
{
    /**
     * @brief Handles rotation of the encoder. In the menu cursor is moved by
     * given number of steps. On the detail screen of red, green or blue item
     * corresponding LED level is changed by `steps * LEVEL_STEP` and limited
     * to the range from 0 to `LEVEL_MAX`.
     *
     * @param steps Number of encoder steps since the last call. Sign determines direction.
     */
    void onRotate(int steps)
    {
        if (screen == Screen::Menu)
        {
            navigator.move(steps);
            return;
        }

        const int channel = utils::colorChannel(navigator.selectedItem().id);
        if (channel >= 0)
            settings.ledLevel[channel] = constrain(settings.ledLevel[channel] + steps * LEVEL_STEP, 0, LEVEL_MAX);
    }

    /**
     * @brief Handles press of the green button. On the detail screen it returns
     * to the menu. On the item with children it enters submenu. On the toggle item
     * like Power, Backlight, Selector or Units it changes its value. On any other
     * item it opens detail screen.
     *
     */
    void onGreen()
    {
        if (screen == Screen::Detail)
        {
            screen = Screen::Menu;
            return;
        }

        if (navigator.enter())
            return;

        switch (navigator.selectedItem().id)
        {
        case menu::MenuItemID::Power:
            settings.ledPower = !settings.ledPower;
            break;
        case menu::MenuItemID::Backlight:
            settings.backlightOn = !settings.backlightOn;
            break;
        case menu::MenuItemID::Selector:
            settings.selector = settings.selector == '>' ? '-' : '>';
            break;
        case menu::MenuItemID::Units:
            settings.fahrenheit = !settings.fahrenheit;
            break;
        default:
            screen = Screen::Detail;
            break;
        }
    }

    /**
     * @brief Handles press of the red button. It leaves detail screen or
     * returns from submenu to the root menu. In the root menu it has no effect.
     *
     */
    void onRed()
    {
        if (screen == Screen::Detail)
            screen = Screen::Menu;
        else
            navigator.back();
    }

    menu::Navigator navigator;
    Settings settings;
    Screen screen {Screen::Menu};
};
} // namespace app
