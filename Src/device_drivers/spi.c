/**
  ******************************************************************************
  * @file    spi.c
  * @author  Equip Embedded
  * @brief   Hardware peripheral interface definitions and macros.
  * @note    This copyright applies only to this file.
  *
  *          This file contains:
  *           - SPI1 hardware initialization for master mode
  *           - 8-bit blocking tx/rx function
  *           - SPI peripheral enable control
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


#include "device_drivers/spi.h"

void spi_init() {                                   // Configure SPI as master with software slave management
	SPI1->CR1 &= ~SPI_CR1_SPE;

	SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_2 | SPI_CR1_BR_0 | SPI_CR1_SSM | SPI_CR1_SSI;

	SPI1->CR2 |= SPI_CR2_FRXTH;
}

void spi_en() {                                     // Enable SPI peripheral
	SPI1->CR1 |= SPI_CR1_SPE;
}

// Transmits 8 bits over SPI, returns received 8 bits
uint8_t spi_tx_8bit(uint8_t data) {
    // Wait for TX buffer empty (can accept new data)
    while(!(SPI1->SR & SPI_SR_TXE));
    // Write byte to data register (triggers transmission)
    *((volatile uint8_t *)&SPI1->DR) = data;
    // Wait for RX buffer non-empty (data received)
    while(!(SPI1->SR & SPI_SR_RXNE));
    // Read and return received byte
    return *(volatile uint8_t*)&SPI1->DR;
}
