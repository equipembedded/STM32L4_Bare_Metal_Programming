/**
  ******************************************************************************
  * @file    clocks.c
  * @author  Equip Embedded
  * @brief   Hardware peripheral interface definitions and macros.
  * @note    This copyright applies only to this file.
  *
  *          This file contains:
  *           - RCC and PLL initialization functions.
  *           - System clock configuration routines.
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

#include "device_drivers/clocks.h"

// Configure the system clock to 80 MHz using the PLL.
void rcc_pll80mhz_init(void){

	// Enable the internal high-speed oscillator (HSI16).
	RCC->CR |= RCC_CR_HSION;

	// Wait until HSI is ready.
	while (!(RCC->CR & RCC_CR_HSIRDY));

	// Configure Flash memory for 4 wait states.
	FLASH->ACR &= ~FLASH_ACR_LATENCY;
	FLASH->ACR |= FLASH_ACR_LATENCY_4WS;

	// Disable the PLL before reconfiguring it.
	RCC->CR &= ~RCC_CR_PLLON;

	// Wait until the PLL is fully disabled.
	while (RCC->CR & RCC_CR_PLLRDY);

	// Configure the PLL.
	// Source = HSI16
	// M = 1
	// N = 10
	// R = 2
	// PLL output enabled
	RCC->PLLCFGR =
		RCC_PLLCFGR_PLLSRC_HSI
	|	(0 << RCC_PLLCFGR_PLLM_Pos)
	|	(10 << RCC_PLLCFGR_PLLN_Pos)
	|	(0 << RCC_PLLCFGR_PLLR_Pos)
	|	RCC_PLLCFGR_PLLREN;

	// Enable the PLL.
	RCC->CR |= RCC_CR_PLLON;

	// Wait until the PLL is locked and ready.
	while (!(RCC->CR & RCC_CR_PLLRDY));

	// Select the PLL as the system clock.
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	// Wait until the PLL is being used as the system clock.
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}
