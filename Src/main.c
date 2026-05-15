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
#include "device_drivers/spi.h"


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

#include "device_headers/stm32l432xx.h"
#include "device_drivers/gpio.h"
#include "device_drivers/i2c.h"

volatile uint8_t TAR_ADDR = 0x3C;
volatile uint32_t ACK_NUM;
volatile uint32_t NACK_NUM;


int main(void)
{

	// Turn on the clock for GPIOA
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	// Enable I2C clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;

	// I2C1_SCL PIN
	GPIO_Init(GPIOB, GPIO_PIN_6, GPIO_MODE_ALTERNATE,
			GPIO_OTYPE_OPENDRAIN, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_NONE);

	// I2C1_SDA PIN
	GPIO_Init(GPIOB, GPIO_PIN_7, GPIO_MODE_ALTERNATE,
			GPIO_OTYPE_OPENDRAIN, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_NONE);


	// ALT_FUNC SCL
	SelectAltFunction(GPIOB, GPIO_PIN_6, AF4);

	// ALT_FUNC SDA
	SelectAltFunction(GPIOB, GPIO_PIN_7, AF4);


	i2c_init();

	while(1) {
		volatile uint8_t ack = i2c_check_addr(TAR_ADDR);

	    if (ack) { // SSD1306 common 7-bit addr
	    	// ACK received → device is present
	    	ACK_NUM++;
	    } else {
			// no ACK → wiring/address issue
	    	NACK_NUM++;
		}

	    delay_ms(100); // Small delay
	}

}
