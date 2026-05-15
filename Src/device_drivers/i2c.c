/**
  ******************************************************************************
  * @file    i2c.c
  * @author  Equip Embedded
  * @brief   Hardware peripheral interface definitions and macros.
  * @note    This copyright applies only to this file.
  *
  *          This file may contain:
  *           - I2C1 hardware initialization for standard mode operation
  *           - 7-bit slave address ACK detection function
  *           - Basic I2C START and AUTOEND transaction control
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

#include "device_drivers/i2c.h"

void i2c_init(void)
{
    /* Disable I2C */
    I2C1->CR1 &= ~I2C_CR1_PE;

    /* 100kHz timing for 4MHz I2C clock */
    I2C1->TIMINGR = 0x0010061A;

    /* Enable I2C */
    I2C1->CR1 |= I2C_CR1_PE;
}

uint8_t i2c_check_addr(uint8_t addr)
{
    /* Clear STOP and NACK flags */
    I2C1->ICR |= I2C_ICR_STOPCF | I2C_ICR_NACKCF;

    /* Clear CR2 transfer settings */
    I2C1->CR2 = 0;

    /* Set 7-bit slave address */
    I2C1->CR2 |= (addr << 1);

    /* Generate STOP automatically */
    I2C1->CR2 |= I2C_CR2_AUTOEND;

    /* Generate START condition */
    I2C1->CR2 |= I2C_CR2_START;

    /* Wait for STOP or NACK */
    while (!(I2C1->ISR & (I2C_ISR_STOPF | I2C_ISR_NACKF)));

    /* Return ACK status */
    return !(I2C1->ISR & I2C_ISR_NACKF);
}


