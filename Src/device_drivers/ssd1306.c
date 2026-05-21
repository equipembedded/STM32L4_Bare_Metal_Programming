/**
  ******************************************************************************
  * @file    ssd1306.c
  * @author  Equip Embedded
  * @brief   Hardware peripheral interface definitions and macros.
  * @note    This copyright applies only to this file.
  *
  *          This file may contain:
  *           - SSD1306 OLED display driver functions
  *           - I2C communication routines
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


#include "device_drivers/ssd1306.h"

void i2c_write(uint8_t addr, uint8_t control_byte, uint8_t data) {

    /* Clear STOP and NACK flags */
    I2C1->ICR |= I2C_ICR_STOPCF | I2C_ICR_NACKCF;

    /* Reset CR2 configuration */
    I2C1->CR2 = 0;

    /* Set slave address */
    I2C1->CR2 |= (addr << 1);

    /* Configure transfer size for 2 bytes */
    I2C1->CR2 |= (2 << I2C_CR2_NBYTES_Pos);

    /* Automatically generate STOP condition */
    I2C1->CR2 |= I2C_CR2_AUTOEND;

    /* Start I2C transfer */
    I2C1->CR2 |= I2C_CR2_START;

    /* Wait until TX register empty and ready for the next byte */
    while (!(I2C1->ISR & I2C_ISR_TXIS));
    I2C1->TXDR = control_byte;

    /* Wait until TX register empty before sending data */
    while (!(I2C1->ISR & I2C_ISR_TXIS));
    I2C1->TXDR = data;

    /* Wait until STOP condition detected */
    while (!(I2C1->ISR & I2C_ISR_STOPF));
}

void ssd1306_cmd(uint8_t cmd) {

    /* Send command byte to SSD1306 */
	i2c_write(SSD1306_ADDR, SSD1306_CMD, cmd);
}

void ssd1306_init() {

    /* Turn display off during configuration */
	ssd1306_cmd(0xAE);

    /* Set memory addressing mode */
    ssd1306_cmd(0x20);

    /* Use horizontal addressing mode */
    ssd1306_cmd(0x00);

    /* Remap display columns */
    ssd1306_cmd(0xA1);

    /* Set COM output scan direction */
    ssd1306_cmd(0xC8);

    /* Set display contrast */
    ssd1306_cmd(0x81);

    /* Set contrast value */
    ssd1306_cmd(0x7F);

    /* Set normal (non-inverted) display mode */
    ssd1306_cmd(0xA6);

    /* Set multiplex ratio */
    ssd1306_cmd(0xA8);

    /* Configure multiplex value for 64 rows */
    ssd1306_cmd(0x3F);

    /* Set display offset */
    ssd1306_cmd(0xD3);

    /* No display offset */
    ssd1306_cmd(0x00);

    /* Set display clock divide ratio */
    ssd1306_cmd(0xD5);

    /* Set recommended clock setting */
    ssd1306_cmd(0x80);

    /* Enable charge pump regulator */
    ssd1306_cmd(0x8D);

    /* Use internal charge pump */
    ssd1306_cmd(0x14);

    /* Turn display on */
    ssd1306_cmd(0xAF);
}
