/**
  ******************************************************************************
  * @file    usart.c
  * @author  Equip Embedded
  * @brief   Hardware peripheral interface definitions and macros.
  * @note    This copyright applies only to this file.
  *
  *          This file may contains:
  *           - USART function declarations
  *           - USART configuration definitions
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

#include "device_drivers/usart.h"

void usart2_init(void)
{
    // Set the baud rate to 115200.
    // USART2 is running from an 80 MHz peripheral clock.
    USART2->BRR = 80000000U / 115200U;

    // Enable the transmitter (TE), receiver (RE),
    // and finally enable the USART peripheral (UE).
    USART2->CR1 = USART_CR1_TE |
                  USART_CR1_RE |
                  USART_CR1_UE;
}

void usart2_send(char c)
{
    // Wait until the transmit data register is empty.
    // This means we can send the next character.
    while (!(USART2->ISR & USART_ISR_TXE));

    // Write the character to the transmit data register.
    USART2->TDR = c;
}

void usart2_print(char *str)
{
    // Keep sending characters until we reach
    // the null terminator at the end of the string.
    while (*str != '\0')
    {
        usart2_send(*str);

        // Move to the next character in the string.
        str++;
    }
}

char usart2_receive(void)
{
    // Wait until a new character has been received.
    while (!(USART2->ISR & USART_ISR_RXNE));

    // Read and return the received character.
    return (char)USART2->RDR;
}
