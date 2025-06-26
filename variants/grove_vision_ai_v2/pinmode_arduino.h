#ifndef PINMODE_ARDUINO_H
#define PINMODE_ARDUINO_H

// NOTE: This file is included by Arduino.h AFTER HimaxWE2_SDK.h has been loaded.
// Therefore, the native SDK definitions like HX_DRV_GPIO_PULL_UP are already present.

// Temporarily redefine the standard Arduino enums to avoid clashes
#define INPUT           Arduino_INPUT
#define OUTPUT          Arduino_OUTPUT
#define INPUT_PULLUP    Arduino_INPUT_PULLUP

// Create the final, unified PinMode enum for our Arduino environment
typedef enum {
  INPUT           = 0,
  OUTPUT          = 1,
  INPUT_PULLUP    = 2,
} PinMode;

// Undo the temporary re-definitions
#undef INPUT
#undef OUTPUT
#undef INPUT_PULLUP

#endif // PINMODE_ARDUINO_H