All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, .ld, HAL drivers) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — DC Motor Driver with PWM (Lesson 06)

This repository contains **bare-metal STM32L4 code** demonstrating how to **control DC motor speed using PWM** with a **DRV8833 motor driver**.  
No HAL is used — only CMSIS device headers and memory-mapped registers.

## Lesson 06: DC Motor Driver
In this lesson, we extend our PWM driver to control a **DC motor** using the **DRV8833 motor driver IC**.  
You'll learn how to interface with motor drivers, calculate appropriate PWM frequencies, and add push-button speed control.

## Key Concepts Covered
- **DC Motor Control**: How PWM regulates motor speed
- **Motor Driver Interfacing**: Connecting DRV8833 to STM32
- **PWM Frequency Selection**: Choosing the right frequency for motors
- **Button Debouncing**: Simple software debouncing technique
- **Bare-Metal Driver Design**: Creating reusable motor control functions
- **Speed Limiting**: Safely capping motor speed between 0-100%

## Features
- `DC_MD_Init(freq_hz)` – Initialize motor driver with specified PWM frequency
- `DC_MD_SetSpeed(duty_percent)` – Set motor speed 0-100%
- Push-button speed control (speed up/slow down)
- Configurable PWM frequency (default 5kHz)
- Direct register manipulation of TIM2 for PWM generation

## Hardware Components
- **STM32 Nucleo-STM32L432**
- **DRV8833 Motor Driver Module**
- **DC Motor (3-6V)**
- **2x Push Buttons** (with internal pull-down resistors)
- **External Power Supply**

## Pin Connections
| STM32 Pin | Component     | Function               |
|-----------|---------------|------------------------|
| PA0       | DRV8833 AIN1  | PWM output (TIM2 CH1)  |
| PB4       | Button 1      | Speed up input         |
| PB5       | Button 2      | Slow down input        |
| -         | DRV8833 AOUT1 | Motor positive terminal|
| -         | DRV8833 AOUT2 | Motor negative terminal|

## What You'll Learn
1. How to read motor driver datasheets
2. How to calculate timer prescaler and auto-reload values for varying frequencies
3. How to interface push buttons with input mode and pull-down resistors
4. How to implement speed control with bounds checking
5. How to structure reusable bare-metal peripheral drivers

## Board
- STM32 Nucleo L4 series

## Disclaimer
This code is for **educational purposes only**.  
It may contain bugs or simplifications and is **not intended for production or safety-critical applications**.
