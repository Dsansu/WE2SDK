#include "variant.h"
#include "hx_drv_scu.h" // System Control Unit for clock setup
#include "hx_drv_timer.h" // For millis() and delay()

// Pin mapping from Arduino Pin Number to Himax GPIO Pin Name
const HX_DRV_GPIO_PIN_E g_pin_map[PINS_COUNT] = {
    AON_GPIO1, // D0 (RX)
    AON_GPIO0, // D1 (TX)
    SGPIO_0,   // D2
    SGPIO_1,   // D3
    SGPIO_2,   // D4 (SDA)
    SGPIO_3,   // D5 (SCL)
    AON_GPIO2, // A0
    AON_GPIO3, // A1
    SGPIO_4,   // A2 - Needs verification if ADC capable
    SGPIO_5,   // A3 - Needs verification if ADC capable
    P_NC,      // 10
    P_NC       // 11
};

// Main Arduino core setup function
void initVariant() {
    // Initialize the System Control Unit and clocks
    // This is a critical step taken from the SDK examples
    hx_drv_scu_init();
    
    // Initialize a hardware timer for millis() and micros()
    // Using Timer 0 as a free-running microsecond timer
    hx_drv_timer_init(TIMER_ID_0, HX_TIMER_CLK_1K);
    hx_drv_timer_start(TIMER_ID_0, 0xFFFFFFFF, TIMER_MODE_PERIODICAL, NULL);
}