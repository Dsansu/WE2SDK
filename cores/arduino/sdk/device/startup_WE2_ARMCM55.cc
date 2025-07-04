/******************************************************************************
 * @file     startup_ARMCM55.c
 * @brief    CMSIS Core Device Startup File for ARMCM55 Device
 * @version  V1.0.0
 * @date     31. March 2020
 ******************************************************************************/
/*
 * Copyright (c) 2020 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#if !defined(HX_TFM)

#if defined (__cplusplus)
extern "C" {
#endif
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#if defined (ARMCM55)
#include "WE2_device.h"
#else
#error device not specified!
#endif
#include "board.h"
#include "WE2_core.h"
#if defined (__cplusplus)
} // extern "C"
#endif
/*----------------------------------------------------------------------------
 External References
 *----------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;
extern uint32_t __STACK_LIMIT;

#if defined (__cplusplus)
//*****************************************************************************
//
// The entry point for the C++ library startup
//
//*****************************************************************************
extern "C" {
extern void __libc_init_array(void);
}
#endif

#if defined (__cplusplus)
extern "C" {
#endif
#if defined (__clang__)
extern __NO_RETURN void __PROGRAM_START(void);
#elif defined (__GNUC__)
extern int main(void);
#endif

/*----------------------------------------------------------------------------
 Internal References
 *----------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler(void);
void Default_Handler(void);

/*----------------------------------------------------------------------------
 Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Exceptions */
void NMI_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__ ((weak));
void MemManage_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SecureFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__ ((weak, alias("Default_Handler")));

void Interrupt0_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt1_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt2_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt3_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt4_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt5_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt6_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt7_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt8_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void Interrupt9_Handler(void) __attribute__ ((weak, alias("Default_Handler")));

#if defined (__cplusplus)
} // extern "C"
#endif

/*----------------------------------------------------------------------------
 Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

extern const VECTOR_TABLE_Type __VECTOR_TABLE[496];
const VECTOR_TABLE_Type __VECTOR_TABLE[496] __VECTOR_TABLE_ATTRIBUTE = {
	(VECTOR_TABLE_Type)(&__INITIAL_SP), /*     Initial Stack Pointer */
	Reset_Handler, /*     Reset Handler */
	NMI_Handler, /* -14 NMI Handler */
	HardFault_Handler, /* -13 Hard Fault Handler */
	MemManage_Handler, /* -12 MPU Fault Handler */
	BusFault_Handler, /* -11 Bus Fault Handler */
	UsageFault_Handler, /* -10 Usage Fault Handler */
	SecureFault_Handler, /*  -9 Secure Fault Handler */
	0, /*     Reserved */
	0, /*     Reserved */
	0, /*     Reserved */
	SVC_Handler, /*  -5 SVCall Handler */
	DebugMon_Handler, /*  -4 Debug Monitor Handler */
	0, /*     Reserved */
	PendSV_Handler, /*  -2 PendSV Handler */
	SysTick_Handler, /*  -1 SysTick Handler */

	/* Interrupts */
	Interrupt0_Handler, /*   0 Interrupt 0 */
	Interrupt1_Handler, /*   1 Interrupt 1 */
	Interrupt2_Handler, /*   2 Interrupt 2 */
	Interrupt3_Handler, /*   3 Interrupt 3 */
	Interrupt4_Handler, /*   4 Interrupt 4 */
	Interrupt5_Handler, /*   5 Interrupt 5 */
	Interrupt6_Handler, /*   6 Interrupt 6 */
	Interrupt7_Handler, /*   7 Interrupt 7 */
	Interrupt8_Handler, /*   8 Interrupt 8 */
	Interrupt9_Handler /*   9 Interrupt 9 */
	/* Interrupts 10 .. 480 are left out */
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

/*----------------------------------------------------------------------------
 Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler(void) {
    __set_MSP((uint32_t)(&__INITIAL_SP));
	__set_MSPLIM((uint32_t) (&__STACK_LIMIT));

	SystemInit(); /* CMSIS System Initialization */

	SCB_DisableICache();
	SCB_DisableDCache();
	SCB_EnableICache();
	SCB_EnableDCache();


    __PROGRAM_START();
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

/*----------------------------------------------------------------------------
 Hard Fault Handler
 *----------------------------------------------------------------------------*/
void HardFault_Handler(void) {
	while (1)
		;
}

/*----------------------------------------------------------------------------
 Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void) {
	while (1)
		;
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic pop
#endif

#endif //#if !defined(HX_TFM)
