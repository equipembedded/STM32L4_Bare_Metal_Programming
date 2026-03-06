/**
  ******************************************************************************
  * @file    main.c
  * @author  Equip Embedded
  * @brief   Bare-metal STM32 register example.
  * @note    This copyright applies only to this file.
  *
  *          This file may contain:
  *           - Data structures and address mapping for peripherals
  *           - Register declarations and bit definitions
  *           - Macros to access hardware registers
  *           - Function calls
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

#include "device_drivers/gpio.h"
#include "device_drivers/timers.h"

static void delay_ms(uint32_t ms)
{
    while (ms--)                      // Loop for each millisecond
    {
        for (uint32_t i = 0; i < 1000; i++)  // 1000 iterations per ms
        {
            __asm volatile ("nop");   // Do nothing for 1 cycle
        }
    }
}

int main(void)
{
	// Enable clock for GPIO ports A and B
	// Without this, GPIO registers cannot be accessed
	RCC->AHB2ENR |= 0x03;              // Enable GPIOA and GPIOB clocks

	// Enable clock for TIM2
	// The timer will not run unless its peripheral clock is enabled
	RCC->APB1ENR1 |= 0x01U;            // Enable TIM2 clock


	// Configure PA0 as an alternate-function output
	// This allows the pin to be driven by a peripheral (TIM2) instead of software
	GPIO_Init(GPIOA, GPIO_PIN_0, GPIO_MODE_ALTERNATE,
			GPIO_OTYPE_PUSHPULL, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_NONE);

	// Select Alternate Function 1 on PA0
	// AF1 connects PA0 to TIM2 Channel 1 (PWM output)
	SelectAltFunction(GPIOA, GPIO_PIN_0, AF1);

	// Initialize the BLDC driver with a 20ms period (50Hz)
	BLDC_Motor_Init(20);

	// Gradually increase motor speed from 0% to 100%
	for(uint8_t i = 0; i <= 100; i++) {
	    // Set current motor speed to i%
	    BLDC_SetSpeed(i);
	}

	// Stop the motor by setting speed to 0%
	BLDC_SetSpeed(0);
}
