/**
  ******************************************************************************
  * @file    gpio.h
  * @author  Equip Embedded
  * @brief   Hardware peripheral interface definitions and macros.
  * @note    This copyright applies only to this file.
  *
  *          This file may contain:
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

#ifndef DEVICE_DRIVERS_GPIO_H_
#define DEVICE_DRIVERS_GPIO_H_

// Include the STM32 device-specific register definitions
// This gives access to GPIO_TypeDef and peripheral registers
#include "device_headers/stm32l432xx.h"

// Initialize a GPIO pin with basic configuration options
// port        : GPIO port base address (e.g., GPIOA, GPIOB)
// pin         : Pin number (0–15)
// mode        : Pin mode (input, output, alternate, analog)
// outputType  : Push-pull or open-drain
// outputSpeed : Output speed selection
// pullUpDown  : Pull-up, pull-down, or no pull resistor
void GPIO_Init(GPIO_TypeDef * port,
				uint8_t pin,
				uint8_t mode,
				uint8_t outputType,
				uint8_t outputSpeed,
				uint8_t pullUpDown);

// Write a logic value to a GPIO pin
// port  : GPIO port base address
// pin   : Pin number (0–15)
// value : 1 = set pin HIGH, 0 = set pin LOW
void GPIO_WritePin(GPIO_TypeDef * port,
				uint8_t pin,
				uint8_t value);

#endif /* DEVICE_DRIVERS_GPIO_H_ */
