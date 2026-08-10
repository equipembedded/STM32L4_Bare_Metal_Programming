All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, linker script, CMSIS device headers, etc.) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — ENS160 Air Quality Sensor (I²C)

This repository contains **bare-metal STM32L4 code** demonstrating how to interface the **ENS160 Air Quality Sensor** using direct register access.

No HAL is used—only CMSIS device headers and memory-mapped peripheral registers.

## Lesson: Reading the ENS160 Air Quality Sensor

In this lesson, we communicate with the **ENS160** over the **I²C bus** using bare-metal programming. We write our own I²C driver to read and write sensor registers without relying on vendor libraries.

The project displays **Air Quality Index (AQI)**, **estimated CO₂ (eCO₂)**, and **Total Volatile Organic Compounds (TVOC)** on an SSD1306 OLED display. Three LEDs provide an immediate visual indication of the current air quality.

## Key Concepts Covered

- Bare-metal I²C communication
- STM32 I²C peripheral configuration
- I²C register read and write operations
- Repeated START conditions
- ENS160 register map
- Reading multi-byte sensor data
- SSD1306 OLED communication over I²C
- Air Quality Index (AQI)
- Total Volatile Organic Compounds (TVOC)
- Equivalent CO₂ (eCO₂)
- GPIO output control using LEDs

## Features

- Bare-metal I²C driver
- Read the ENS160 Part ID
- Configure the ENS160 operating mode
- Read AQI, TVOC, and eCO₂ measurements
- Display measurements on an SSD1306 OLED
- Green, yellow, and red LEDs indicate air quality
- No HAL or third-party libraries used for sensor communication

## Hardware Components

- STM32 Nucleo-L432KC
- ENS160 Air Quality Sensor
- SSD1306 I²C OLED Display (128×64)
- 3 LEDs (Green, Yellow, Red)
- Current-limiting resistors
- Breadboard
- Jumper wires

## Pin Connections

### ENS160

| STM32 Pin | ENS160 |
| ----------|--------|
| PB6       | SCL    |
| PB7       | SDA    |
| 3.3V      | VIN    |
| GND       | GND    |

### SSD1306 OLED

| STM32 Pin | OLED |
| ----------|------|
| PB6       | SCL  |
| PB7       | SDA  |
| 3.3V      | VCC  |
| GND       | GND  |

### Status LEDs

| STM32 Pin | Function |
| ----------|----------|
| PA0       | Red LED |
| PA1       | Yellow LED |
| PA3       | Green LED |

## What You'll Learn

1. How the I²C protocol works
2. How to configure the STM32 I²C peripheral
3. How register-based communication works
4. How repeated START conditions are used
5. How to read single-byte and multi-byte registers
6. How to interface multiple I²C devices on the same bus
7. How to display sensor data on an OLED
8. How to use GPIO pins for simple status indicators

## Board

- STM32 Nucleo-L432KC

## Disclaimer

This code is provided for **educational purposes only**.

It demonstrates direct register-level programming of the STM32 microcontroller without using the STM32 HAL. While every effort has been made to keep the code simple and easy to understand, it may contain bugs, omissions, or simplifications.

Always consult the reference manual, datasheet, and sensor documentation for your specific hardware before using this code in your own projects.

This project is **not intended for production, commercial, or safety-critical applications**.

Equip Embedded assumes no responsibility for hardware damage, data loss, or other issues resulting from the use or misuse of this code.