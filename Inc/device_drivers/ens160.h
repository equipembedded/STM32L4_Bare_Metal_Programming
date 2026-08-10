/**
  ******************************************************************************
  * @file    ens160.h
  * @author  Equip Embedded
  * @brief   ENS160 air quality sensor driver definitions.
  * @note    This copyright applies only to this file.
  *
  *          This file contains:
  *           - ENS160 register definitions and configuration macros
  *           - ENS160 I2C device address definitions
  *           - Function prototypes for sensor communication
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

#ifndef DEVICE_DRIVERS_ENS160_H_
#define DEVICE_DRIVERS_ENS160_H_

#include <stdint.h>
#include "device_headers/stm32l432xx.h"

#define ENS160_ADDR            0x53U
#define ENS160_STANDARD_MODE   0x02U
#define ENS160_PART_ID_REG     0x00U

uint16_t ens160_read_part_id(void);
void ens160_write(uint8_t reg, uint8_t data);
uint8_t ens160_read(uint8_t reg);

#endif /* DEVICE_DRIVERS_ENS160_H_ */
