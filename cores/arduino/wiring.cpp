#include "Arduino.h"
#include "hx_drv_timer.h"

void delay(uint32_t ms) {
    if (ms == 0) return;
    uint32_t start = millis();
    while (millis() - start < ms);
}

void delayMicroseconds(uint32_t us) {
    // This is a rough approximation. A more precise implementation would use a dedicated microsecond timer.
    for (volatile uint32_t i = 0; i < us * 100; ++i) {
        __asm__("nop");
    }
}

unsigned long millis() {
    uint32_t tick_count;
    hx_drv_timer_get_count(TIMER_ID_0, HX_TIMER_COUNT_UP, &tick_count);
    return tick_count;
}

unsigned long micros() {
    // The timer is set to 1KHz, so we multiply by 1000 to get microseconds.
    return millis() * 1000;
}