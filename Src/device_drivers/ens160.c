/**
  ******************************************************************************
  * @file    ens160.c
  * @author  Equip Embedded
  * @brief   ENS160 air quality sensor driver implementation.
  * @note    This copyright applies only to this file.
  *
  *          This file contains:
  *           - ENS160 sensor initialization and configuration functions
  *           - I2C register read and write operations
  *           - Functions for reading sensor data such as AQI, TVOC, and CO2
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



#include "device_drivers/ens160.h"

uint16_t ens160_read_part_id(void)
{
    uint8_t addr = ENS160_ADDR;
    uint8_t id[2];

    /*
     * ENS160 register read sequence:
     *
     * 1. Master sends register address (WRITE)
     * 2. Master sends repeated START
     * 3. Master reads data bytes (READ)
     */

    /* Clear previous I2C status flags */
    I2C1->ICR = I2C_ICR_STOPCF | I2C_ICR_NACKCF;

    /* Reset transfer configuration */
    I2C1->CR2 = 0;


    /*
     * Step 1: Tell ENS160 which register we want to read
     *
     * Master -> Slave:
     * START
     * Address + WRITE
     * Register address
     */

    /* Set ENS160 slave address */
    I2C1->CR2 |= (addr << 1);

    /* We are sending one byte: register address */
    I2C1->CR2 |= (1 << I2C_CR2_NBYTES_Pos);

    /* Generate START condition */
    I2C1->CR2 |= I2C_CR2_START;


    /* Wait until STM32 is ready to transmit */
    while (!(I2C1->ISR & I2C_ISR_TXIS));

    /* Send PART_ID register address (0x00) */
    I2C1->TXDR = ENS160_PART_ID_REG;


    /*
     * Wait until the register address transmission is complete.
     *
     * We do not wait for STOP because we need a
     * repeated START for the read operation.
     */
    while (!(I2C1->ISR & I2C_ISR_TC));


    /*
     * Step 2: Read two bytes from ENS160
     *
     * Master -> Slave:
     * START
     * Address + READ
     *
     * Slave -> Master:
     * Data byte 0
     * Data byte 1
     */


    /* Reset transfer configuration */
    I2C1->CR2 = 0;

    /* Set ENS160 address */
    I2C1->CR2 |= (addr << 1);

    /* Select READ direction */
    I2C1->CR2 |= I2C_CR2_RD_WRN;

    /* We expect two bytes from the sensor */
    I2C1->CR2 |= (2 << I2C_CR2_NBYTES_Pos);

    /* Automatically generate STOP after receiving data */
    I2C1->CR2 |= I2C_CR2_AUTOEND;

    /* Generate repeated START */
    I2C1->CR2 |= I2C_CR2_START;


    /* Wait for first received byte */
    while (!(I2C1->ISR & I2C_ISR_RXNE));
    id[0] = (uint8_t)I2C1->RXDR;


    /* Wait for second received byte */
    while (!(I2C1->ISR & I2C_ISR_RXNE));
    id[1] = (uint8_t)I2C1->RXDR;


    /* Wait until the complete transaction finishes */
    while (!(I2C1->ISR & I2C_ISR_STOPF));


    /*
     * ENS160 sends data LSB first:
     *
     * ID low byte  -> id[0]
     * ID high byte -> id[1]
     */
    return (id[1] << 8) | id[0];
}



void ens160_write(uint8_t reg, uint8_t data)
{
    uint8_t addr = ENS160_ADDR;


    /*
     * ENS160 register write sequence:
     *
     * Master -> Slave:
     * START
     * Address + WRITE
     * Register address
     * Data
     * STOP
     */


    /* Clear previous I2C flags */
    I2C1->ICR = I2C_ICR_STOPCF | I2C_ICR_NACKCF;

    /* Reset transfer configuration */
    I2C1->CR2 = 0;


    /* Set slave address */
    I2C1->CR2 |= (addr << 1);

    /* Two bytes:
     * 1 byte register address
     * 1 byte data
     */
    I2C1->CR2 |= (2 << I2C_CR2_NBYTES_Pos);

    /* Generate STOP automatically */
    I2C1->CR2 |= I2C_CR2_AUTOEND;

    /* Start transmission */
    I2C1->CR2 |= I2C_CR2_START;


    /* Send register address */
    while (!(I2C1->ISR & I2C_ISR_TXIS));
    I2C1->TXDR = reg;


    /* Send register value */
    while (!(I2C1->ISR & I2C_ISR_TXIS));
    I2C1->TXDR = data;


    /* Wait until STOP is generated */
    while (!(I2C1->ISR & I2C_ISR_STOPF));
}



uint8_t ens160_read(uint8_t reg)
{
    uint8_t data;
    uint8_t addr = ENS160_ADDR;


    /*
     * Register read:
     *
     * 1. Write register address
     * 2. Repeated START
     * 3. Read data byte
     */


    /* Clear previous flags */
    I2C1->ICR = I2C_ICR_STOPCF | I2C_ICR_NACKCF;


    /*
     * Step 1:
     * Send register address to ENS160
     */

    I2C1->CR2 = 0;

    /* Slave address + WRITE */
    I2C1->CR2 |= (addr << 1);

    /* One byte: register address */
    I2C1->CR2 |= (1 << I2C_CR2_NBYTES_Pos);

    /* START condition */
    I2C1->CR2 |= I2C_CR2_START;


    while (!(I2C1->ISR & I2C_ISR_TXIS));
    I2C1->TXDR = reg;


    /*
     * Wait for register address transmission to complete.
     * Keep the bus active because we need a repeated START.
     */
    while (!(I2C1->ISR & I2C_ISR_TC));


    /*
     * Step 2:
     * Read one byte from ENS160
     */

    I2C1->CR2 = 0;

    /* Slave address */
    I2C1->CR2 |= (addr << 1);

    /* Select READ direction */
    I2C1->CR2 |= I2C_CR2_RD_WRN;

    /* Receive one byte */
    I2C1->CR2 |= (1 << I2C_CR2_NBYTES_Pos);

    /* Generate STOP automatically */
    I2C1->CR2 |= I2C_CR2_AUTOEND;

    /* Repeated START */
    I2C1->CR2 |= I2C_CR2_START;


    /* Wait until sensor sends data */
    while (!(I2C1->ISR & I2C_ISR_RXNE));

    /* Read received byte */
    data = (uint8_t)I2C1->RXDR;


    /* Wait until transaction is complete */
    while (!(I2C1->ISR & I2C_ISR_STOPF));


    return data;
}

