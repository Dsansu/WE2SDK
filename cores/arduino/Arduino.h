#ifndef Arduino_h
#define Arduino_h

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// This now includes our new, variant-specific PinMode definition.
#include "pinmode_arduino.h" 

// These are the other standard API files we will create.
#include "WCharacter.h"
#include "WString.h"
#include "HardwareSerial.h"

// Bring in board-specific pin names like D0, D1 etc.
#include "variant.h" 

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
// Note: pinMode is NOT prototyped here because its definition is tied
// into the PinMode enum from pinmode_arduino.h
void digitalWrite(uint32_t pin, PinStatus status);
PinStatus digitalRead(uint32_t pin);

int analogRead(uint32_t pin);
void analogWrite(uint32_t pin, int val);

unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned long);
void delayMicroseconds(unsigned int us);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // Arduino_h