All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, .ld, HAL drivers) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Blinky (Lesson 01)

This repository contains **bare-metal STM32L4 code** for blinking LEDs on a Nucleo board.  
All programming is done **directly via registers**, without HAL or external libraries.

## Features
- Register-level GPIO control  
- No HAL, no libraries  
- Example for GPIOA and GPIOB pins  

## Code Overview
- Enable GPIO clocks via `RCC_AHB2ENR`  
- Configure pins as output via `GPIOx_MODER`  
- Set/reset pins via `GPIOx_BSRR`  

## Board
- STM32 Nucleo L4 series  

## Disclaimer
This code is for **learning purposes** only. Not production-ready.
