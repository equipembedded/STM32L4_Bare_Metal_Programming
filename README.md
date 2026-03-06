All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, .ld, HAL drivers) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — BLDC Motor Driver with PWM (Lesson 08)

This repository contains **bare-metal STM32L4 code** demonstrating how to **control a brushless DC (BLDC) motor** using **precise PWM signals**.  
No HAL is used — only CMSIS device headers and memory-mapped registers.

## Lesson 08: BLDC Motor Driver
In this lesson, we build a **BLDC motor driver from scratch** to control motor speed using PWM signals to an ESC (Electronic Speed Controller).  
You'll learn how to generate the correct pulse width for throttle control and map percentage speed to pulse widths.

## Key Concepts Covered
- **BLDC Motor Control**: Using ESCs to control brushless motors  
- **PWM Generation**: Creating precise timing signals to set motor speed  
- **Pulse Width Calculation**: Converting speed percentage (0-100%) to PWM pulse widths  
- **Timer Registers**: Directly configuring STM32 timers for PWM without HAL  
- **Bare-Metal Driver Design**: Creating reusable functions for motor initialization and speed control  
- **Speed Clamping**: Safely limiting input to 0-100% range

## Features
- `BLDC_Motor_Init(period_ms)` – Initialize timer for ESC control (e.g., 20ms = 50Hz)  
- `BLDC_SetSpeed(speed_percent)` – Set motor speed 0-100%  
- Automatic mapping of speed percentage to pulse width  
- Direct register manipulation of TIM2 for PWM generation  
- Ready-to-use, reusable bare-metal driver functions

## Hardware Components
- **STM32 Nucleo-STM32L432**  
- **BLDC Motor + ESC** (or similar)  
- **Servo Tester** (optional, for calibration)  
- **Lithium Battery** (for motor power)

## Pin Connections
| STM32 Pin | Component | Function                        |
|-----------|-----------|---------------------------------|
| PA0       | ESC Signal| PWM output (TIM2 CH1)           |
| GND       | ESC GND   | Common ground                   |
| VCC       | ESC VCC   | Motor power (from battery/ESC)  |

## What You'll Learn
1. How to read ESC timing requirements  
2. How to calculate timer prescaler and auto-reload for a given period  
3. How to convert speed percentage (0-100%) to pulse width (µs)  
4. How to map pulse width to timer compare register (CCR) values  
5. How to structure reusable bare-metal peripheral drivers  
6. The relationship between period, pulse width, and motor speed

## Board
- STM32 Nucleo L4 series

## Disclaimer
This code is for **educational purposes only**.  
BLDC motors and lithium batteries can be **dangerous if misused**.  
Use proper safety precautions, protective equipment, and proceed at your own risk. 
The code may contain bugs or simplifications and is **not intended for production or safety-critical applications**.
