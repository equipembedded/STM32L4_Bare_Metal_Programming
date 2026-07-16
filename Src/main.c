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
#include "device_drivers/ssd1306.h"

volatile uint8_t TAR_ADDR = 0x3C;
volatile uint32_t ACK_NUM;
volatile uint32_t NACK_NUM;


int main(void)
{
    // Enable GPIOB peripheral clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    // Enable I2C1 peripheral clock
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;

    // Configure PB6 as I2C1 SCL
    GPIO_Init(GPIOB, GPIO_PIN_6, GPIO_MODE_ALTERNATE,
            GPIO_OTYPE_OPENDRAIN, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_NONE);

    // Configure PB7 as I2C1 SDA
    GPIO_Init(GPIOB, GPIO_PIN_7, GPIO_MODE_ALTERNATE,
            GPIO_OTYPE_OPENDRAIN, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_NONE);

    // Select alternate function AF4 for SCL
    SelectAltFunction(GPIOB, GPIO_PIN_6, AF4);

    // Select alternate function AF4 for SDA
    SelectAltFunction(GPIOB, GPIO_PIN_7, AF4);

    // Initialize STM32 I2C peripheral
    i2c_init();

    // Initialize SSD1306 display
    ssd1306_init();

    // Clear the SSD1306 display.
    ssd1306_clear();

    // Clear the local display buffer.
    ssd1306_clear_buffer();

    // Send the cleared buffer to the display.
    ssd1306_update();

    // Draw two individual pixels.
    ssd1306_draw_pixel(32, 16);
    ssd1306_draw_pixel(90, 16);

    // Draw a diagonal line across the display.
	ssd1306_draw_line(0, 0, 127, 63);

    // Draw a rectangle.
	ssd1306_draw_rect(16, 5, 100, 50);

    // Draw a circle in the center of the display.
	ssd1306_draw_circle(64, 32, 20);

    // Print text and numbers.
	ssd1306_print(26, 24, "EQUIP");
	ssd1306_print(62, 24, "EMBEDDED");
	ssd1306_print(0, 63-8, "123");

    // Update the display with all drawings.
    ssd1306_update();

}
