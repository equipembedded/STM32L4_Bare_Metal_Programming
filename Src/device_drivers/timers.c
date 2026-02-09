/**
  ******************************************************************************
  * @file    timers.c
  * @author  Equip Embedded
  * @brief   Hardware peripheral interface definitions and macros.
  * @note    This copyright applies only to this file.
  *
  *          This file may contain:
  *           - Bare-metal timer and PWM driver implementations
  *           - Timer initialization and control functions
  *           - Register-level configuration for STM32 timers
  *           - Educational examples for PWM generation
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

#include "device_drivers/timers.h"

void PWM_Init(TIM_TypeDef * timer) {

	// Enable Auto-Reload Preload (ARPE)
	// Allows ARR updates to take effect on an update event instead of immediately
	timer->CR1 |= 0x80U;

	// Configure Channel 1 for PWM mode 1 and enable preload
	// OC1M = 110 (PWM mode 1), OC1PE = 1 (preload enable)
	timer->CCMR1 |= 0x68U;

	// Enable Capture/Compare Channel 1 output
	// This connects the timer output to the GPIO pin
	timer->CCER |= 0x01U;

	// Clear the counter to start counting from zero
	timer->CNT |= 0U;

	// Set prescaler
	// Divides the timer clock to slow down the counter
	timer->PSC = 40U - 1U;

	// Set auto-reload value (PWM period)
	// Timer resets when CNT reaches ARR
	timer->ARR = 1000U - 1U;

	// Set compare value (PWM duty cycle)
	// Determines how long the output stays high
	timer->CCR1 = 100U - 1U;

	// Generate an update event
	// Forces PSC, ARR, and CCR values to load into active registers
	timer->EGR |= 0x01U;
}

void PWM_Begin(TIM_TypeDef * timer) {

	// Enable the timer counter
	// PWM output starts running
	timer->CR1 |= 0x01;
}

