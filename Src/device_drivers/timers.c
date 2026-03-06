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

void DC_MD_Init( uint16_t freq_hz) {
	// Enable Auto-Reload Preload (ARPE)
	// Allows ARR updates to take effect on an update event instead of immediately
	TIM2->CR1 |= 0x80U;

	// Configure Channel 1 for PWM mode 1 and enable preload
	// OC1M = 110 (PWM mode 1), OC1PE = 1 (preload enable)
	TIM2->CCMR1 |= 0x68U;

	// Enable Capture/Compare Channel 1 output
	// This connects the timer output to the GPIO pin
	TIM2->CCER |= 0x01U;

	// Clear the counter to start counting from zero
	TIM2->CNT |= 0U;

	// Set prescaler
	// Divides the timer clock to slow down the counter
	TIM2->PSC = DC_MC_PRESCALER - 1U;

	// Set auto-reload value (PWM period)
	// Timer resets when CNT reaches ARR
	TIM2->ARR = CLK_4MHZ / (DC_MC_PRESCALER * freq_hz) - 1;

	// Set compare value (PWM duty cycle)
	// Determines how long the output stays high
	TIM2->CCR1 = 0U;

	// Generate an update event
	// Forces PSC, ARR, and CCR values to load into active registers
	TIM2->EGR |= 0x01U;

	TIM2->CR1 |= 0x01;  // Enable timer counter (CEN bit)
}

void DC_MD_SetSpeed(uint8_t duty_percent) {
    volatile uint32_t arr_value = TIM2->ARR;  // Read current auto-reload value

    TIM2->CCR1 = (arr_value + 1) * duty_percent / 100;  // Calculate and set compare value for duty cycle
}


void ServoMotor_Init(uint16_t period_ms) {
	// Enable auto-reload preload (updates ARR on next cycle)
	TIM2->CR1 |= 0x80U;

	// PWM mode 1, enable preload
	TIM2->CCMR1 |= 0x68U;

	// Enable channel 1 output
	TIM2->CCER |= 0x01U;

	// Reset counter
	TIM2->CNT |= 0U;

	// Set prescaler (clock divider)
	TIM2->PSC = DC_MC_PRESCALER - 1U;

	// Calculate and set period (20ms for 50Hz)
    TIM2->ARR = (CLK_4MHZ * period_ms) / (DC_MC_PRESCALER * 1000) - 1;

	// Start with 0% duty cycle
	TIM2->CCR1 = 0U;

	// Load new values into active registers
	TIM2->EGR |= 0x01U;

	// Start the timer
	TIM2->CR1 |= 0x01;
}

void SetServoDirection_Degrees(uint16_t period_ms, uint8_t servo_angle){
	uint32_t arr = TIM2->ARR;  // Get current period value

	// Clamp angle to valid range (0-180°)
	if (servo_angle > 180) servo_angle = 180;

	// Convert angle to pulse width (500-2500µs)
	uint32_t pulse_us = 500 + ((uint32_t)servo_angle * 2000) / 180;

	// Convert pulse width to compare value and update duty cycle
	TIM2->CCR1 = (pulse_us * (arr + 1)) / (period_ms * 1000);
}


/*
 * Initializes PWM output used to control the BLDC ESC.
 * The ESC expects a servo-style PWM signal  (~50Hz).
 *
 * period_ms: PWM period in milliseconds (typically 20ms for ESCs)
 */
void BLDC_Motor_Init(uint16_t period_ms) {

	// Enable auto-reload preload so ARR updates safely on next cycle
	TIM2->CR1 |= 0x80U;

	// Configure Channel 1 for PWM Mode 1 and enable CCR preload
	TIM2->CCMR1 |= 0x68U;

	// Enable output on Channel 1
	TIM2->CCER |= 0x01U;

	// Reset timer counter
	TIM2->CNT = 0U;

	// Configure prescaler (divides timer clock)
	TIM2->PSC = DC_MC_PRESCALER - 1U;

	// Set PWM period (e.g., 20ms → 50Hz signal for ESC)
    TIM2->ARR = (CLK_4MHZ * period_ms) / (DC_MC_PRESCALER * 1000) - 1;

	// Initialize with minimum throttle pulse (~0% speed)
	TIM2->CCR1 = ((TIM2->ARR + 1) * 45) / 1000;

	// Force update event to load registers immediately
	TIM2->EGR |= 0x01U;

	// Start the timer
	TIM2->CR1 |= 0x01;
}


/*
 * Sets BLDC motor speed by adjusting ESC throttle pulse width.
 *
 * speed_percent: throttle value from 0–100%
 */
void BLDC_SetSpeed(uint8_t speed_percent) {

	// Clamp input to valid range
	if (speed_percent > 100) speed_percent = 100;

	uint32_t arr = TIM2->ARR;

	// Convert throttle percentage to ESC pulse width (µs)
    uint32_t pulse_us = ESC_MIN_US + ((ESC_RANGE_US * speed_percent) / 100);

    // Convert pulse width to timer ticks and update duty cycle
    TIM2->CCR1 = (pulse_us * (arr + 1)) / 20000;

}
