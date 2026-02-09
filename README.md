All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, .ld, HAL drivers) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — PWM Driver & LED/Motor Control (Lesson 05: PWM)

This repository contains **bare-metal STM32L4 code** demonstrating how to **generate PWM signals** to **dim LEDs or control motor speed** using **direct register access**.  
No HAL is used — only CMSIS device headers and memory-mapped registers.

## Lesson 05: PWM Output
In this lesson, we extend the GPIO driver to generate **PWM signals** with STM32 timers.  
You’ll learn how to configure timers, set up duty cycles, and control output pins for LEDs or motors.

## Key Concepts Covered
- **PWM Fundamentals**: How pulse-width modulation works and how frequency & duty cycle affect output
- **Timer Configuration**: Setting prescaler, auto-reload, and compare registers
- **Duty Cycle Control**: Adjusting PWM to dim LEDs or control motor speed
- **Bare-Metal Timer Use**: Directly accessing TIMx registers without HAL or middleware
- **Alternate Function Pins**: Connecting timer outputs to GPIO pins

## Features
- `PWM_Init()` – Configure a timer for PWM mode
- `PWM_Begin()` – Start the timer and PWM output
- Adjustable **duty cycle** and **PWM frequency**
- Examples showing **LED dimming** and **motor speed control**
- Direct register manipulation of TIM2, CCMR, CCER, ARR, CCR, PSC, and EGR

## What You'll Learn
1. How to configure a GPIO pin for alternate function (timer PWM output)
2. How timers generate PWM signals
3. How to calculate and set **period** and **duty cycle** registers
4. How to dim an LED or drive a motor using PWM

## Board
- STM32 Nucleo L4 series

## Project Structure
- `main.c` – Application code demonstrating PWM on an LED or motor
- `timers.c/.h` – Bare-metal PWM driver functions
- Register-level configuration for TIMx_CR1, TIMx_CCMR1, TIMx_CCER, TIMx_CNT, TIMx_PSC, TIMx_ARR, TIMx_CCRx, and TIMx_EGR

## Disclaimer
This code is for **educational purposes only**.  
It may contain bugs or simplifications and is **not intended for production or safety-critical applications**.
