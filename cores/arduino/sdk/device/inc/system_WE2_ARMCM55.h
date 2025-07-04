/**************************************************************************//**
 * @file     system_ARMCM55.h
 * @brief    CMSIS Device System Header File for
 *           ARMCM55 Device
 * @version  V1.0.0
 * @date     20. February 2020
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

#ifndef SYSTEM_ARMCM55_H
#define SYSTEM_ARMCM55_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 \brief Exception / Interrupt Handler Function Prototype
 */
typedef void (*VECTOR_TABLE_Type)(void);

/**
 \brief System Clock Frequency (Core Clock)
 */
extern uint32_t SystemCoreClock;

/**
 \brief Setup the microcontroller system.

 Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit(void);

/**
 \brief  Update SystemCoreClock variable.

 Init the SystemCoreClock with current core Clock retrieved from cpu registers.
 */
extern void SystemCoreClockInit();

/**
 \brief  Update SystemCoreClock variable.

 Updates the SystemCoreClock with current core Clock retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate(uint32_t clock);

/**
 \brief  Get Current Tick.

 */
extern void SystemGetTick(uint32_t *systick, uint32_t *loop_cnt);


#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_ARMCM55_H */
