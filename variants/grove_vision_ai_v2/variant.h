#ifndef _VARIANT_H_
#define _VARIANT_H_

#include "hx_drv_gpio.h" // Include the core SDK header for GPIO definitions

// Number of pins
#define PINS_COUNT           (12)
#define NUM_DIGITAL_PINS     (12)
#define NUM_ANALOG_INPUTS    (4)

// Standard Arduino API definitions
#define PIN_A0 (6)
#define PIN_A1 (7)
#define PIN_A2 (8)
#define PIN_A3 (9)

// LED
#define LED_BUILTIN (13) // Use a non-existent pin for now

// Serial
#define SERIAL_PORT_MONITOR     Serial
#define SERIAL_PORT_HARDWARE    Serial

// Pin declarations
extern const HX_DRV_GPIO_PIN_E g_pin_map[PINS_COUNT];
extern const uint32_t g_pin_mux[PINS_COUNT];

void initVariant();

#endif // _VARIANT_H_