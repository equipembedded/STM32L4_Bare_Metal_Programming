/**
  ******************************************************************************
  * @file    gpio.c
  * @author  Equip Embedded
  * @brief   Hardware peripheral interface definitions and macros.
  * @note    This copyright applies only to this file.
  *
  *          This file may contain:
  *           - GPIO initialization and control functions
  *           - Register-level configuration logic
  *           - Helper functions for GPIO operations
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

void GPIO_Init(GPIO_TypeDef * port,
		uint8_t pin,
		uint8_t mode,
		uint8_t outputType,
		uint8_t outputSpeed,
		uint8_t pullUpDown){

	// -------- GPIO MODE CONFIGURATION --------
	// Each pin uses 2 bits in MODER
	// Clear the 2 bits for the selected pin
	port->MODER &= ~(0x3UL << (pin * 2U));

	// Set the mode for the selected pin (e.g., input, output, alternate)
	port->MODER |= ((uint32_t)(mode << (pin * 2U)));

	// -------- OUTPUT TYPE CONFIGURATION --------
	// Each pin uses 1 bit in OTYPER
	// Clear the bit for the selected pin
	port->OTYPER &= ~(0x1UL << pin);

	// Set output type (push-pull or open-drain)
	port->OTYPER |= ((uint32_t)(outputType << pin));

	// -------- OUTPUT SPEED CONFIGURATION --------
	// Each pin uses 2 bits in OSPEEDR
	// Clear the 2 bits for the selected pin
	port->OSPEEDR &= ~(0x3UL << (pin * 2));

	// Set output speed (low, medium, high, very high)
	port->OSPEEDR |= ((uint32_t)(outputSpeed << (pin * 2U)));

	// -------- PULL-UP / PULL-DOWN CONFIGURATION --------
	// Each pin uses 2 bits in PUPDR
	// Clear the 2 bits for the selected pin
	port->PUPDR &= ~(0x3UL << (pin * 2));

	// Set pull-up, pull-down, or no pull resistor
	port->PUPDR |= ((uint32_t)(pullUpDown << (pin * 2U)));
}

void GPIO_WritePin(GPIO_TypeDef * port,
				uint8_t pin,
				uint8_t value) {

	// Check whether we want to set the pin HIGH or LOW
	if (value == 1U) {
		// Write to the lower 16 bits of BSRR to set the pin HIGH
		// This operation is atomic (no read-modify-write)
		port->BSRR |= (1UL << pin);
	} else {
		// Write to the upper 16 bits of BSRR to reset the pin LOW
		// (pin number + 16 targets the reset bits)
		port->BSRR |= (1UL << (pin + 16));
	}
}


