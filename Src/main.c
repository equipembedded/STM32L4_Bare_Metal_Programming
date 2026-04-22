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


int main(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;           // Enable GPIOA clock

	RCC->APB2ENR |=  RCC_APB2ENR_SPI1EN;           // Enable SPI1 clock

	// CS
	GPIO_Init(GPIOA, GPIO_PIN_4, GPIO_MODE_OUTPUT, // Configure CS pin as output
			GPIO_OTYPE_PUSHPULL, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_UP);

	// CLK
	GPIO_Init(GPIOA, GPIO_PIN_5, GPIO_MODE_ALTERNATE, // Configure SCK as alternate function
			GPIO_OTYPE_PUSHPULL, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_NONE);

	// SDI
	GPIO_Init(GPIOA, GPIO_PIN_6, GPIO_MODE_ALTERNATE, // Configure MISO as alternate function
			GPIO_OTYPE_PUSHPULL, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_NONE);

	// SDO
	GPIO_Init(GPIOA, GPIO_PIN_7, GPIO_MODE_ALTERNATE, // Configure MOSI as alternate function
			GPIO_OTYPE_PUSHPULL, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_NONE);



	// CLK ALT FUNC
	SelectAltFunction(GPIOA, GPIO_PIN_5, AF5);     // Set SCK to AF5 (SPI1)

	// SDI ALT FUNC
	SelectAltFunction(GPIOA, GPIO_PIN_6, AF5);     // Set MISO to AF5 (SPI1)

	// SDO ALT FUNC
	SelectAltFunction(GPIOA, GPIO_PIN_7, AF5);     // Set MOSI to AF5 (SPI1)

	spi_init();                                    // Initialize SPI1 peripheral

	spi_en();                                      // Enable SPI1

	volatile uint8_t x = 0;
	volatile int8_t try = 1;

	while(1) {
	    uint8_t whoami = 0;

	    // CS LOW
	    GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_LOW);   // Assert chip select

	    // Send address: READ_BIT (0x80) | register address 0x00 (WHO_AM_I)
	    spi_tx_8bit(0x80 | 0x00);

	    // Send dummy byte to clock in response, store received WHO_AM_I value
	    whoami = spi_tx_8bit(0x00);

	    // Wait for hardware to finish all SPI activity
	    while(SPI1->SR & SPI_SR_BSY);

	    // CS HIGH
	    GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_HIGH);  // Deassert chip select

	    // Expected WHO_AM_I for ICM-20948 is 0xEA
	    if (whoami != 0xEA) {
	        // Error: wrong device ID - decrement try until zero (infinite loop)
	        while(try > 0) {
	            try--;
	        }
	    } else {
	        // Success: increment counter
	        x++;
	    }
	}

}
