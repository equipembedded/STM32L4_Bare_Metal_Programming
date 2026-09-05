/**
  ******************************************************************************
  * @file    exti.c
  * @author  Equip Embedded
  * @brief   Hardware peripheral interface definitions and macros.
  * @note    This copyright applies only to this file.
  *
  *          This file may contain:
  *           - EXTI line initialization functions
  *           - EXTI interrupt handler(s) (ISR callbacks)
  *           - GPIO pin state read/write helpers used by EXTI callbacks
  *           - EXTI line configuration macros (trigger edge, port mapping)
  *
  ******************************************************************************
  * MIT License
  *
  * Copyright (c) 2026 Equip Embedded
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in
  * all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  * THE SOFTWARE.
  ******************************************************************************
  */

#include "device_drivers/exti.h"

void exti_init(void) {
	// Select PA1 as the source port for EXTI line 1 (clear EXTI1 bits in SYSCFG_EXTICR1)
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI1;

	// Enable falling-trigger detection on EXTI line 1
	EXTI->FTSR1 |= EXTI_FTSR1_FT1;

	// Clear any pending interrupt flag on EXTI line 1 before enabling
	EXTI->PR1 = EXTI_PR1_PIF1;

	// Unmask (enable) interrupt request on EXTI line 1
	EXTI->IMR1 |= EXTI_IMR1_IM1;

	// Enable EXTI1 interrupt in the NVIC
	NVIC_EnableIRQ(EXTI1_IRQn);

}

void EXTI1_IRQHandler(void) {
	// Check if the pending flag for EXTI line 1 is set
	if (EXTI->PR1 & EXTI_PR1_PIF1) {

		// Clear the pending flag (write 1 to clear)
		EXTI->PR1 = EXTI_PR1_PIF1;

		// Check current output state of pin A1
		if (GPIOA->ODR & GPIO_PIN_1) {
			// If PA1 is high, drive pin PA0 low
			GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_LOW);
		} else {
			// Otherwise (PA1 is low), drive pin PA0 high
			GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_HIGH);
		}
	}
}
