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

    // Set full column address range
    ssd1306_cmd(0x21);
    ssd1306_cmd(0);
    ssd1306_cmd(127);

    // Set full page address range
    ssd1306_cmd(0x22);
    ssd1306_cmd(0);
    ssd1306_cmd(7);

    // Clear entire display GDDRAM
    for (uint16_t i = 0; i < 1024; i++)
    {
        i2c_write(0x3C, 0x40, 0x00);
    }

    // Select drawing window: right half of display
    ssd1306_cmd(0x21);
    ssd1306_cmd(63);
    ssd1306_cmd(127);

    // Select drawing window: lower display pages
    ssd1306_cmd(0x22);
    ssd1306_cmd(4);
    ssd1306_cmd(7);

    // Write raw bitmap data for letter A
    ssd1306_data(0x80);
    ssd1306_data(0x60);
    ssd1306_data(0x18);
    ssd1306_data(0x16);
    ssd1306_data(0x11);
    ssd1306_data(0x16);
    ssd1306_data(0x18);
    ssd1306_data(0x20);
    ssd1306_data(0xC0);
}
