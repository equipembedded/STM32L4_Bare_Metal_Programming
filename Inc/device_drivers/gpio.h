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

#define GPIO_PIN_0   0U
#define GPIO_PIN_1   1U
#define GPIO_PIN_2   2U
#define GPIO_PIN_3   3U
#define GPIO_PIN_4   4U
#define GPIO_PIN_5   5U
#define GPIO_PIN_6   6U
#define GPIO_PIN_7   7U
#define GPIO_PIN_8   8U
#define GPIO_PIN_9   9U
#define GPIO_PIN_10  10U
#define GPIO_PIN_11  11U
#define GPIO_PIN_12  12U
#define GPIO_PIN_13  13U
#define GPIO_PIN_14  14U
#define GPIO_PIN_15  15U

//#define GPIO_MODE_INPUT        0x00U
//#define GPIO_MODE_OUTPUT       0x01U
//#define GPIO_MODE_ALTERNATE    0x02U
//#define GPIO_MODE_ANALOG       0x03U

typedef enum {
	GPIO_MODE_INPUT		= 0U,
	GPIO_MODE_OUTPUT,
	GPIO_MODE_ALTERNATE,
	GPIO_MODE_ANALOG
} GPIO_Mode_t;

//#define GPIO_OTYPE_PUSHPULL   0x00
//#define GPIO_OTYPE_OPENDRAIN  0x01

typedef enum
{
    GPIO_OTYPE_PUSHPULL  = 0U,
    GPIO_OTYPE_OPENDRAIN
} GPIO_OutputType_t;

//#define GPIO_OUTPUT_SPEED_LOW      0x00
//#define GPIO_OUTPUT_SPEED_MEDIUM   0x01
//#define GPIO_OUTPUT_SPEED_HIGH     0x02
//#define GPIO_OUTPUT_SPEED_VERY_HIGH 0x03

typedef enum
{
    GPIO_OUTPUT_SPEED_LOW       = 0U,
    GPIO_OUTPUT_SPEED_MEDIUM,
    GPIO_OUTPUT_SPEED_HIGH,
    GPIO_OUTPUT_SPEED_VERY_HIGH
} GPIO_OutputSpeed_t;


//#define GPIO_PULL_NONE     0x00
//#define GPIO_PULL_UP       0x01
//#define GPIO_PULL_DOWN     0x02

typedef enum
{
    GPIO_PULL_NONE = 0U,
    GPIO_PULL_UP, // HIGH
	GPIO_PULL_DOWN // LOW
} GPIO_Pull_t;

//#define GPIO_HIGH 	1
//#define GPIO_LOW		0

typedef enum
{
    GPIO_LOW  = 0U,
    GPIO_HIGH = 1U
} GPIO_Level_t;

// Initialize a GPIO pin with basic configuration options
// port        : GPIO port base address (e.g., GPIOA, GPIOB)
// pin         : Pin number (0–15)
// mode        : Pin mode (input, output, alternate, analog)
// outputType  : Push-pull or open-drain
// outputSpeed : Output speed selection
// pullUpDown  : Pull-up, pull-down, or no pull resistor
void GPIO_Init(GPIO_TypeDef * port,
				uint8_t pin,
				GPIO_Mode_t mode,
				GPIO_OutputType_t outputType,
				GPIO_OutputSpeed_t outputSpeed,
				GPIO_Pull_t pullUpDown);

// Write a logic value to a GPIO pin
// port  : GPIO port base address
// pin   : Pin number (0–15)
// value : 1 = set pin HIGH, 0 = set pin LOW
void GPIO_WritePin(GPIO_TypeDef * port,
				uint8_t pin,
				GPIO_Level_t value);

// Read the current logic level from a GPIO pin
// port  : GPIO port base address
// pin   : Pin number (0–15)
// returns: GPIO_HIGH (1) or GPIO_LOW (0)
GPIO_Level_t GPIO_ReadPin(GPIO_TypeDef * port, uint8_t pin);

#endif /* DEVICE_DRIVERS_GPIO_H_ */
