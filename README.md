All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, .ld, HAL drivers) remain under STMicroelectronics copyright.

## STM32 Nucleo Bare-Metal Series — GPIO Driver from Scratch (Lesson 03)

This repository contains **bare-metal STM32L4 code** demonstrating how to **write a GPIO driver from scratch** using **direct register access**.  
No HAL is used — only CMSIS device headers and memory-mapped registers.

## Features
- Custom GPIO driver (`GPIO_Init`, `GPIO_WritePin`)
- No HAL, no middleware
- Clean abstraction over GPIO registers
- Readable, scalable bare-metal design
- Progression from raw integers → macros → enums

## Code Overview
- GPIO registers accessed via CMSIS device headers
- Driver split into `.h` / `.c` files
- Macros and enums for clarity and safety
- Easily change ports and pins

## Board
- STM32 Nucleo L4 series

## Disclaimer
This code is for **educational purposes only**.  
Not intended for production or safety-critical use.
