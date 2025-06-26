#include "Arduino.h"

int main(void) {
    // Board-specific hardware initialization.
    // This function is defined in variant.cpp
    initVariant();

    // Call the user's setup function.
    setup();

    // Continuously call the user's loop function.
    for (;;) {
        loop();
    }

    return 0;
}