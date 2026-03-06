/**
  ******************************************************************************
  * @file    timers.h
  * @author  Equip Embedded
  * @brief   Hardware peripheral interface definitions and macros.
  * @note    This copyright applies only to this file.
  *
  *          This file may contain:
  *           - Timer and PWM driver function prototypes
  *           - Low-level register definitions and helper macros
  *           - Timer configuration utilities for bare-metal development
  *
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

#include <stdint.h>
#include "device_headers/stm32l432xx.h"

#ifndef DEVICE_DRIVERS_TIMERS_H_
#define DEVICE_DRIVERS_TIMERS_H_

// Defines
#define CLK_4MHZ			4000000U   // Timer clock frequency in Hz (4 MHz)
#define DC_MC_PRESCALER		4U         // Prescaler value for PWM frequency calculation

#define ESC_MIN_US  900
#define ESC_MAX_US  1650
#define ESC_RANGE_US (ESC_MAX_US - ESC_MIN_US)


// Initializes a timer peripheral for PWM operation
// Configures prescaler, auto-reload, compare mode, and preload settings
// Does NOT start the timer
void PWM_Init(TIM_TypeDef * timer);

// Starts PWM signal generation
// Enables the timer counter and begins output on the configured channel
void PWM_Begin(TIM_TypeDef * timer);  // Timer peripheral to start PWM on

// Initializes DC motor driver with specified frequency
void DC_MD_Init(uint16_t freq_hz);    // PWM frequency in Hertz

// Sets motor speed by adjusting PWM duty cycle
void DC_MD_SetSpeed(uint8_t duty_percent);  // Duty cycle 0-100%

// Initialize servo with 20ms period = 50Hz frequency (standard for all hobby servos)
// This sets up the timer to generate continuous PWM signal
void ServoMotor_Init(uint16_t period_ms);

// Convert angle (0-180°) to pulse width and update PWM signal
void SetServoDirection_Degrees(uint16_t period_ms, uint8_t servo_angle);

/*
 * Initializes the BLDC motor ESC PWM interface.
 *
 * period_ms: PWM period in milliseconds (typically 20ms for standard ESC control)
 */
void BLDC_Motor_Init(uint16_t period_ms);

/*
 * Sets BLDC motor speed by adjusting the ESC throttle signal.
 *
 * speed_percent: Motor speed from 0–100%
 */
void BLDC_SetSpeed(uint8_t speed_percent);

#endif /* DEVICE_DRIVERS_TIMERS_H_ */
