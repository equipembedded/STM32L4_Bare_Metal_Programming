All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, .ld, HAL drivers) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — Servo Motor Driver with PWM (Lesson 07)

This repository contains **bare-metal STM32L4 code** demonstrating how to **control a servo motor** using **precise PWM timing**.  
No HAL is used — only CMSIS device headers and memory-mapped registers.

## Lesson 07: Servo Motor Driver
In this lesson, we build a **servo motor driver from scratch** to control position using PWM.  
You'll learn how to generate the exact 50Hz signal required by standard hobby servos and map angles to pulse widths.

## Key Concepts Covered
- **Servo Motor Control**: How pulse width determines angular position (0° to 180°)
- **50Hz PWM Generation**: Creating the exact timing servos require (20ms period)
- **Pulse Width Calculation**: Converting angles to pulse widths
- **Datasheet Reading**: Understanding SG90 timing requirements
- **Bare-Metal Driver Design**: Creating reusable servo control functions
- **Angle Clamping**: Safely limiting input to 0-180° range

## Features
- `ServoMotor_Init(period_ms)` – Initialize timer for servo control (20ms = 50Hz)
- `SetServoDirection_Degrees(period_ms, servo_angle)` – Set servo position 0-180°
- Automatic angle-to-pulse-width conversion
- Direct register manipulation of TIM2 for PWM generation

## Hardware Components
- **STM32 Nucleo-STM32L432**
- **SG90 Micro Servo Motor** (or similar hobby servo)

## Pin Connections
| STM32 Pin | Component     | Function                    |
|-----------|---------------|-----------------------------|
| PA0       | Servo Signal  | PWM output (TIM2 CH1)       |
| 5V        | Servo VCC     | Power (external supply)     |
| GND       | Servo GND     | Common ground               |

## What You'll Learn
1. How to read servo motor datasheets
2. How to calculate timer prescaler and auto-reload values for 50Hz frequency
3. How to convert angle (0-180°) to pulse width (500-2500µs)
4. How to map pulse width to timer compare values
5. How to structure reusable bare-metal peripheral drivers
6. The relationship between period, pulse width, and servo position

## Board
- STM32 Nucleo L4 series

## Disclaimer
This code is for **educational purposes only**.  
It may contain bugs or simplifications and is **not intended for production or safety-critical applications**.
