/**
  ******************************************************************************
  * @file    ssd1306.h
  * @author  Equip Embedded
  * @brief   Hardware peripheral interface definitions and macros.
  * @note    This copyright applies only to this file.
  *
  *          This file may contain:
  *           - SSD1306 OLED driver macros
  *           - SSD1306 function declarations
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

#ifndef DEVICE_DRIVERS_SSD1306_H_
#define DEVICE_DRIVERS_SSD1306_H_


#include <stdint.h>
#include "device_headers/stm32l432xx.h"

#define SSD1306_ADDR 0x3C
#define SSD1306_CMD  0x00
#define SSD1306_DATA 0x40

void i2c_write(uint8_t addr, uint8_t control_byte, uint8_t data);
void ssd1306_cmd(uint8_t cmd);
void ssd1306_data(uint8_t data);
void ssd1306_init(void);


#endif /* DEVICE_DRIVERS_SSD1306_H_ */
