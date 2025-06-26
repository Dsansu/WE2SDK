#ifndef Arduino_h
#define Arduino_h

// Step 1: Include the entire underlying hardware SDK via our new master header.
// This file is in the same directory, so the IDE will find it immediately.
#include "HimaxWE2_SDK.h"

// Step 2: Now that SDK headers are loaded, include Arduino-specific definitions.
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pinmode_arduino.h" // The conflict-resolution header for PinMode
#include "WCharacter.h"
#include "WString.h"
#include "HardwareSerial.h"
#include "variant.h"       // Board-specific pin names (D0, D1, etc.)

#ifdef __cplusplus
extern "C"{
#endif

// Standard Arduino types
typedef uint8_t byte;
typedef bool boolean;

// Pin Status (can be defined here as it doesn't conflict)
#define LOW   0x0
#define HIGH  0x1
typedef uint8_t PinStatus;

// Standard function prototypes
void digitalWrite(uint32_t pin, PinStatus status);
PinStatus digitalRead(uint32_t pin);
// ... other prototypes ...
unsigned long millis(void);
void delay(unsigned long);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // Arduino_h