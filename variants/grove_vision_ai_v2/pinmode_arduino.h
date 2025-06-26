#ifndef PINMODE_ARDUINO_H
#define PINMODE_ARDUINO_H

// This file resolves naming conflicts between the Arduino API and the Himax SDK.

// 1. Temporarily rename standard Arduino definitions to avoid clashes.
#define INPUT           Arduino_INPUT
#define OUTPUT          Arduino_OUTPUT
#define INPUT_PULLUP    Arduino_INPUT_PULLUP

// 2. Include the Himax SDK driver that defines its own versions of these terms.
#include "hx_drv_gpio.h"

// 3. Undo the temporary re-definitions.
#undef INPUT
#undef OUTPUT
#undef INPUT_PULLUP

// 4. Create the one, true PinMode enum that our Arduino core will use.
typedef enum {
  INPUT           = 0, // Standard Arduino value
  OUTPUT          = 1, // Standard Arduino value
  INPUT_PULLUP    = 2, // Standard Arduino value
} PinMode;

#endif // PINMODE_ARDUINO_H