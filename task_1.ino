#include "include/button.hpp"
#include "include/controller.hpp"
#include "include/display.hpp"
#include "include/encoder.hpp"
#include "include/leds.hpp"
#include "include/pins.hpp"

components::Button redButton {pins::RED_BUTTON};
components::Button greenButton {pins::GREEN_BUTTON};
components::Encoder encoder {pins::ENCODER_A, pins::ENCODER_B};

app::Controller controller;
app::Display display;

ISR(PCINT1_vect)
{
    encoder.handleInterrupt();
}

void refresh()
{
    components::leds::apply(controller.settings);

    display.setBacklight(controller.settings.backlightOn);
    display.render(controller.navigator, controller.settings, controller.screen);
}

void setup()
{
    display.begin();
    components::leds::begin();

    encoder.begin();
    redButton.begin();
    greenButton.begin();

    refresh();
}

void loop()
{
    auto steps = encoder.read();
    auto green = greenButton.pressed();
    auto red = redButton.pressed();

    if (steps == 0 && !green && !red)
        return;

    if (steps != 0)
        controller.onRotate(steps);

    if (green)
        controller.onGreen();
    if (red)
        controller.onRed();

    refresh();
}
