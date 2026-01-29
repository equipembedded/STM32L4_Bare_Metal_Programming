All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, .ld, HAL drivers) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — GPIO Driver from Scratch (Lesson 04: Input Capture)

This repository contains **bare-metal STM32L4 code** demonstrating how to **read GPIO inputs and respond to button presses** using **direct register access**.  
No HAL is used — only CMSIS device headers and memory-mapped registers.

## Lesson 04: Input Capture
In this lesson, we expand our GPIO driver to include **input functionality**, reading button states and controlling outputs in response.

## Key Concepts Covered
- **GPIO Input Configuration**: Setting pins as inputs with pull-up/pull-down resistors
- **Button Reading**: Using `GPIO_ReadPin()` to detect button presses
- **Input/Output Interaction**: Making an LED respond to button input
- **Pull Resistors**: Understanding when and why to use pull-up vs. pull-down

## Features
- Complete GPIO driver with `GPIO_Init`, `GPIO_WritePin`, and `GPIO_ReadPin`
- Input capture functionality for button/switch reading
- Pull-up/pull-down resistor configuration
- Clean, readable code progression from raw integers → macros → enums
- No HAL, no middleware — pure bare-metal implementation

## What You'll Learn
1. How to configure a GPIO pin as an input
2. The difference between pull-up and pull-down resistors
3. How to read a button state and control an LED

## Board
- STM32 Nucleo L4 series
- Push button and LED

## Project Structure
- `main.c` - Application code with button-to-LED control
- `gpio.c/.h` - Complete GPIO driver with input/output capabilities
- Register-level configuration for MODER, OTYPER, OSPEEDR, PUPDR, IDR, and BSRR

## Disclaimer
This code is for **educational purposes only**.  
Not intended for production or safety-critical use.
