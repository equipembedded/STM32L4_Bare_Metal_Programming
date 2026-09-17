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

#include <stdio.h>
#include "device_headers/stm32l432xx.h"
#include "device_drivers/clocks.h"
#include "device_drivers/gpio.h"
#include "device_drivers/usart.h"

int main(void)
{
	// Configure the system clock to run at 80 MHz
	rcc_pll80mhz_init();

	// Enable the GPIOA peripheral clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Enable the USART1 peripheral clock
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	// Enable the USART2 peripheral clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;


	// Configure PA9 as USART1 TX.
	GPIO_Init(GPIOA, GPIO_PIN_9, GPIO_MODE_ALTERNATE,
	          GPIO_OTYPE_PUSHPULL, GPIO_OUTPUT_SPEED_HIGH, GPIO_PULL_NONE);

	// Configure PA10 as USART1 RX.
	GPIO_Init(GPIOA, GPIO_PIN_10, GPIO_MODE_ALTERNATE,
	          GPIO_OTYPE_PUSHPULL, GPIO_OUTPUT_SPEED_HIGH, GPIO_PULL_NONE);

	// Configure PA2 as USART2 TX.
	GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_ALTERNATE,
	          GPIO_OTYPE_PUSHPULL, GPIO_OUTPUT_SPEED_HIGH, GPIO_PULL_NONE);

	// Configure PA15 as USART2 RX.
	GPIO_Init(GPIOA, GPIO_PIN_15, GPIO_MODE_ALTERNATE,
	          GPIO_OTYPE_PUSHPULL, GPIO_OUTPUT_SPEED_HIGH, GPIO_PULL_NONE);


	// Select the alternate functions for USART1 pins.
	SelectAltFunction(GPIOA, GPIO_PIN_9, AF7);   // USART1 TX
	SelectAltFunction(GPIOA, GPIO_PIN_10, AF7);  // USART1 RX

	// Select the alternate functions for USART2 pins.
	SelectAltFunction(GPIOA, GPIO_PIN_2, AF7);   // USART2 TX
	SelectAltFunction(GPIOA, GPIO_PIN_15, AF3);  // USART2 RX

	// Initialize USART
	usart_init(USART1, 9600);
	usart_init(USART2, 9600);

	while(1) {
		char c = usart_receive(USART1);
		usart_send(USART2, c);
	}
}
