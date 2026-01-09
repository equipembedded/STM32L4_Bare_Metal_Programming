/**
  ******************************************************************************
  * @file    main.c
  * @author  Equip Embedded
  * @brief   Bare-metal STM32 register example.
  *
  *          This file contains:
  *           - Data structures and address mapping for peripherals
  *           - Register declarations and bit definitions
  *           - Macros to access hardware registers
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

#include <stdint.h>   // Gives us standard integer types (like uint32_t)

// Base address of the clock control block (RCC)
#define RCC_BASE 0x40021000U

// Register that turns hardware blocks (like GPIO) on or off
#define RCC_AHB2ENR (*(volatile uint32_t*)(RCC_BASE + 0x4CU))

// Base addresses for GPIO ports A and B
#define GPIOA_BASE 0x48000000U
#define GPIOB_BASE 0x48000400U

// GPIOA registers
#define GPIOA_MODER (*(volatile uint32_t*)(GPIOA_BASE + 0x00U)) // Controls pin modes
#define GPIOA_BSRR  (*(volatile uint32_t*)(GPIOA_BASE + 0x18U)) // Sets or resets pins

// GPIOB registers
#define GPIOB_MODER (*(volatile uint32_t*)(GPIOB_BASE + 0x00U)) // Controls pin modes
#define GPIOB_BSRR  (*(volatile uint32_t*)(GPIOB_BASE + 0x18U)) // Sets or resets pins

int main(void)
{
	// Turn on the clock for GPIOA and GPIOB
	// If the clock is off, the pins will not work
	RCC_AHB2ENR |= 0x03;

	// First, clear their mode settings
	GPIOA_MODER &= 0xFC000000;

	// Set those pins to "output mode"
	GPIOA_MODER |= 0x01555555;

	// Do the same thing for selected pins on GPIOB
	GPIOB_MODER &= 0xFFFF0030;
	GPIOB_MODER |= 0x00005545;

	// Set GPIOA pins high (turn them ON)
	GPIOA_BSRR |= 0x1FFF;

	// Set GPIOB pins high (turn them ON)
	GPIOB_BSRR |= 0xFB;
}

