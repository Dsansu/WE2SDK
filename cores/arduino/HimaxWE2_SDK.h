#ifndef HIMAXWE2_SDK_H
#define HIMAXWE2_SDK_H

/*
 * This file is the single point of inclusion for the entire Himax SDK.
 * It is based on the actual file structure provided in the we2sdk repository.
 */

// 1. Include the top-level hardware and driver definition files.
// These define the board and the available peripherals.
#include "board.h"                  // Found in .../sdk/board/epii_evb/
#include "WE2_hardware_config.h"    // Found in .../sdk/board/epii_evb/config/
#include "hx_drv_def.h"             // Found in .../sdk/security/inc/

// 2. Include essential drivers needed for the Arduino API implementation
#include "hx_drv_scu.h"             // System Control Unit (Clocks)
#include "hx_drv_gpio.h"            // GPIO (digitalWrite, etc.)
#include "hx_drv_timer.h"           // Timer (millis, delay)
#include "hx_drv_uart.h"            // UART (Serial)
#include "hx_drv_i2c.h"             // I2C (Wire)
#include "hx_drv_spi.h"             // SPI

#endif // HIMAXWE2_SDK_H