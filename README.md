# Arduino Layered Menu
Two level LCD menu for Arduino Uno, controlled with rotary encoder and two
buttons. It allows to control RGB LED, change display options and view
temperature in Celsius or Fahrenheit. Project was prepared for IoT classes.

## Specification
Arduino UNO Rev3 pinout and ATmega328P datasheet are located in `specs/arduino`.

## Pinout
| Component         | Pin       |
|-------------------|-----------|
| LED red           | D6 (PWM)  |
| LED green         | D5 (PWM)  |
| LED blue          | D3 (PWM)  |
| Red button        | D2        |
| Green button      | D4        |
| Encoder A         | A2        |
| Encoder B         | A3        |
| LCD I2C (`0x27`)  | A4 / A5   |

## Commands
Board and port are read from `sketch.yaml`. To use different port add `-p <port>` flag.

```bash
# Install tools, AVR core and LCD library
brew install arduino-cli doxygen
arduino-cli core install arduino:avr
arduino-cli lib install "LiquidCrystal I2C"

# List connected boards and their ports
arduino-cli board list

# Build and verify application
arduino-cli compile .

# Build and upload application
arduino-cli compile -u .

# Upload application and verify written memory
arduino-cli upload -t .

# Generate documentation
doxygen
```

## Note
If you are changing the port sometimes there could be situation
when application sending process will crash due to port invalid
setting inside .vscode. To avoid this, just change the port inside
`port` parameter to the one visible in the crash log or Serial Monitor.

## Documentation
Code is documented with Doxygen comments. Configuration is stored in `Doxyfile`
and generated HTML documentation is placed in `docs/html`. To view it open
`docs/html/index.html` in the browser.

## Author
Mateusz Adamowicz
