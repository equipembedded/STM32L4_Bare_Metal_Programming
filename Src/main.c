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

// Delay function for 4MHz clock
//static void delay_ms(uint32_t ms)
//{
//    while (ms--)                      // Loop for each millisecond
//    {
//        for (uint32_t i = 0; i < 1000; i++)  // 1000 iterations per ms
//        {
//            __asm volatile ("nop");   // Do nothing for 1 cycle
//        }
//    }
//}


// Delay function for 80MHz clock
static void delay_ms(uint32_t ms)
{
    while (ms--)
    {
        for (uint32_t i = 0; i < 20000; i++)
        {
            __asm volatile ("nop");
        }
    }
}

#include <stdio.h>
#include "device_headers/stm32l432xx.h"
#include "device_drivers/gpio.h"
#include "device_drivers/i2c.h"
#include "device_drivers/ssd1306.h"
#include "device_drivers/clocks.h"
#include "device_drivers/ens160.h"

int main(void)
{
    // Configure the system clock.
    // The MCU will run at 80 MHz, which affects CPU speed and peripheral clocks.
    rcc_pll80mhz_init();


    // ==========================
    // Initialize Status LEDs
    // ==========================

    // Enable GPIOA peripheral clock because LEDs are connected to GPIOA pins.
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    // Red LED
    GPIO_Init(GPIOA, GPIO_PIN_0, GPIO_MODE_OUTPUT,
            GPIO_OTYPE_PUSHPULL, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_NONE);

    // Yellow LED
    GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_OUTPUT,
            GPIO_OTYPE_PUSHPULL, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_NONE);

    // Green LED
    GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUTPUT,
            GPIO_OTYPE_PUSHPULL, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_NONE);



    // ==========================
    // Initialize I2C1 Peripheral
    // ==========================

    // Enable GPIOB clock because I2C pins are located on GPIOB.
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    // Enable the I2C1 peripheral clock.
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;


    // Configure PB6 as I2C1 SCL.
    // I2C uses open-drain outputs because multiple devices can share the bus.
    GPIO_Init(GPIOB, GPIO_PIN_6, GPIO_MODE_ALTERNATE,
            GPIO_OTYPE_OPENDRAIN, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_NONE);

    // Configure PB7 as I2C1 SDA.
    GPIO_Init(GPIOB, GPIO_PIN_7, GPIO_MODE_ALTERNATE,
            GPIO_OTYPE_OPENDRAIN, GPIO_OUTPUT_SPEED_LOW, GPIO_PULL_NONE);


    // Select alternate function AF4.
    // This connects the GPIO pins to the internal I2C1 peripheral.
    SelectAltFunction(GPIOB, GPIO_PIN_6, AF4); // SCL
    SelectAltFunction(GPIOB, GPIO_PIN_7, AF4); // SDA


    // Configure I2C1 registers.
    // This sets the I2C speed and enables the peripheral.
    i2c_init();



    // ==========================
    // Initialize SSD1306 OLED
    // ==========================

    // Send initialization commands to the OLED controller.
    ssd1306_init();

    // Clear the pixels currently displayed on the OLED.
    ssd1306_clear();

    // Clear the software display buffer stored in MCU RAM.
    ssd1306_clear_buffer();

    // Send the empty buffer to the OLED.
    ssd1306_update();



    // ==========================
    // Initialize ENS160 Sensor
    // ==========================

    // Put ENS160 into standard operating mode.
    // In this mode the sensor continuously measures air quality.
    ens160_write(0x10, ENS160_STANDARD_MODE);

    // Allow time for the sensor to switch modes.
    delay_ms(10);

    // Character array used as a temporary string buffer.
    // sprintf() writes sensor values into this buffer before displaying them on the OLED.
    char buffer[32];


    while(1)
    {
        // ==========================
        // Read ENS160 Measurements
        // ==========================

        // CO2 value is stored in two registers:
        // 0x24 = lower byte
        // 0x25 = upper byte
        uint8_t co2_low  = ens160_read(0x24);
        uint8_t co2_high = ens160_read(0x25);

        // Combine two 8-bit values into one 16-bit value.
        uint16_t co2 = (co2_high << 8) | co2_low;


        // Read Air Quality Index.
        // Values range from 1 (good) to 5 (poor).
        uint8_t aqi = ens160_read(0x21);


        // TVOC value is also stored in two registers:
        // 0x22 = lower byte
        // 0x23 = upper byte
        uint8_t tvoc_low  = ens160_read(0x22);
        uint8_t tvoc_high = ens160_read(0x23);

        // Combine TVOC bytes into a 16-bit value.
        // TVOC is reported in parts per billion (ppb).
        uint16_t tvoc = (tvoc_high << 8) | tvoc_low;



        // ==========================
        // Control LEDs Based on AQI
        // ==========================

        if (aqi >= 4) {

            // Poor air quality - turn on red LED.
            GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_HIGH);
            GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_LOW);
            GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_LOW);

        } else if (aqi == 3) {

            // Moderate air quality - turn on yellow LED.
            GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_LOW);
            GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_HIGH);
            GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_LOW);

        } else {

            // Good air quality - turn on green LED.
            GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_LOW);
            GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_LOW);
            GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_HIGH);
        }



        // ==========================
        // Display Data on OLED
        // ==========================

        sprintf(buffer, "CO2:%u", co2);
        ssd1306_print(0, 0, buffer);

        sprintf(buffer, "AQI:%u", aqi);
        ssd1306_print(0, 16, buffer);

        sprintf(buffer, "TVOC:%u", tvoc);
        ssd1306_print(0, 32, buffer);


        // Transfer the display buffer to the OLED.
        ssd1306_update();

        // Clear buffer before the next screen update.
        ssd1306_clear_buffer();


        // Update readings once per second.
        delay_ms(1000);
    }
}
