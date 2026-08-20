All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, linker script, CMSIS device headers, etc.) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — TIM2 Delay Function

This repository contains **bare-metal STM32L4 code** demonstrating how to create accurate microsecond and millisecond delays using the **TIM2 hardware timer**.

No HAL is used—only CMSIS device headers and memory-mapped peripheral registers.

## Lesson: Building a Delay Function with TIM2

In this lesson, we configure **TIM2** as a free-running 32-bit timer and use it to create accurate delay functions.

The STM32L432KC is running at **80 MHz**. TIM2 uses a prescaler of 79 to produce a **1 MHz counter frequency**, giving us:

**1 timer tick = 1 µs**

The delay function uses the timer counter to measure elapsed time instead of relying on software instruction loops.

## Key Concepts Covered

- Bare-metal timer configuration
- STM32 TIM2 peripheral
- Timer prescaler
- 32-bit timer counter
- Free-running timer
- Microsecond timing
- Millisecond timing
- Unsigned subtraction and timer rollover
- Measuring elapsed time
- Hardware-based delays
- Direct register access

## Features

- TIM2-based delay functionality
- Microsecond delays
- Millisecond delays
- 1 µs timer resolution
- Free-running 32-bit counter
- Timer rollover-safe elapsed-time calculation
- No HAL or third-party libraries

## Hardware Components

- STM32 Nucleo-L432KC
- Logic analyzer or oscilloscope (optional)

## Timer Configuration

| Parameter | Value |
| --------- | ----- |
| System Clock | 80 MHz |
| TIM2 Prescaler | 79 |
| TIM2 Counter Clock | 1 MHz |
| Timer Resolution | 1 µs |
| Counter Size | 32-bit |
| Timer Mode | Up-counter / Free-running |

## What You'll Learn

1. How to enable the TIM2 peripheral clock
2. How a timer prescaler works
3. How to configure TIM2 for a 1 MHz counter
4. How to create a microsecond delay
5. How to create a millisecond delay
6. How to measure elapsed time using a hardware timer
7. How unsigned subtraction handles timer rollover
8. How hardware timers can be used for peripheral timeouts and event timing

## Board

- STM32 Nucleo-L432KC

## Disclaimer

This code is provided for **educational purposes only**.

It demonstrates direct register-level programming of the STM32 microcontroller without using the STM32 HAL. While every effort has been made to keep the code simple and easy to understand, it may contain bugs, omissions, or simplifications.

Always consult the reference manual and datasheet for your specific hardware before using this code in your own projects.

This project is **not intended for production, commercial, or safety-critical applications**.

Equip Embedded assumes no responsibility for hardware damage, data loss, or other issues resulting from the use or misuse of this code.