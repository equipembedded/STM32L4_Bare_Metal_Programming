/**
  ******************************************************************************
  * @file    utilities.c
  * @author  Equip Embedded
  * @brief   Hardware peripheral interface definitions and macros.
  * @note    This copyright applies only to this file.
  *
  * This file contains:
  *      - TIM2-based delay function implementations
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

#include "utilities.h"

void delay_init() {
    // Enable the TIM2 peripheral clock
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

    // Set timer to 1 MHz: 80 MHz / (79 + 1) = 1 MHz
    TIM2->PSC = 79;

    // Set maximum 32-bit counter value for free-running operation
    TIM2->ARR = 0xFFFFFFFF;

    // Start counter at 0
    TIM2->CNT = 0;

    // Apply the prescaler configuration
    TIM2->EGR = TIM_EGR_UG;

    // Enable the timer counter
    TIM2->CR1 = TIM_CR1_CEN;
}

void delay_us(uint32_t us) {
    // Capture the starting timer value
    uint32_t t1 = TIM2->CNT;

    // Wait until the requested number of ticks has elapsed
    while ((uint32_t)(TIM2->CNT - t1) < us);
}

void delay_ms(uint32_t ms) {
    // Convert milliseconds to microseconds
    delay_us(ms * 1000);
}
