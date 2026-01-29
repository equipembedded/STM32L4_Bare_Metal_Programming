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

int main(void)
{
	// Enable clock for GPIO Ports A and B (required for register access)
	RCC->AHB2ENR |= 0x03;

	// Configure PA3 as output (will control an LED or other device)
	GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUTPUT,
			GPIO_OTYPE_PUSHPULL, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_NONE);

	// Configure PA4 as input with pull-down resistor (for reading a button/switch)
	GPIO_Init(GPIOA, GPIO_PIN_4, GPIO_MODE_INPUT,
			GPIO_OTYPE_PUSHPULL, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_DOWN);

	while(1) {
		// Read the state of PA4 (button/switch)
		volatile GPIO_Level_t port_A_pin_4 = GPIO_ReadPin(GPIOA, GPIO_PIN_4);

		// If PA4 is HIGH, turn PA3 ON. If PA4 is LOW, turn PA3 OFF
		if (port_A_pin_4 == GPIO_HIGH) {
			GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_HIGH);
		} else {
			GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_LOW);
		}
	}
}

