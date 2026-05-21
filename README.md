All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, .ld, HAL drivers) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — SSD1306 OLED Driver

This repository contains **bare-metal STM32L4 code** demonstrating how to interface an **SSD1306 OLED display** over I2C using direct register access.  
No HAL is used — only CMSIS device headers and memory-mapped peripheral registers.

## Lesson: SSD1306 OLED Initialization over I2C

In this lesson, we build a minimal **bare-metal SSD1306 driver** for the STM32L432 and initialize the OLED display by transmitting commands over I2C.

## Key Concepts Covered

- **Bare-Metal I2C Communication**: Direct peripheral register access without HAL  
- **SSD1306 Command Interface**: Sending initialization commands over I2C  
- **START and STOP Generation**: STM32 hardware-controlled I2C transactions  
- **AUTOEND Mode**: Automatic STOP generation after transfer completion  
- **I2C TX Flow**: Monitoring TXIS and STOPF status flags  
- **Horizontal Addressing Mode**: SSD1306 memory configuration  
- **OLED Initialization Sequence**: Configuring contrast, scan direction, and charge pump

## Features

- `i2c_write()` – Send SSD1306 command or data bytes over I2C  
- `ssd1306_cmd()` – Send a single command byte to the display  
- `ssd1306_init()` – Initialize SSD1306 OLED controller  
- Direct manipulation of STM32 I2C1 peripheral registers  
- Minimal SSD1306 bare-metal driver implementation

## Hardware Components

- **STM32 Nucleo-STM32L432KC**  
- **SSD1306 OLED Display (I2C)**  
- **Breadboard and jumper wires**  
- **Logic Analyzer** (optional, for debugging I2C traffic)

## Pin Connections

| STM32 Pin | I2C Signal | Function                  |
|-----------|------------|---------------------------|
| PB6       | SCL        | I2C1 Serial Clock (AF4)  |
| PB7       | SDA        | I2C1 Serial Data (AF4)   |

## What You'll Learn

1. How to send I2C transactions without HAL  
2. How SSD1306 command transfers work  
3. How STM32 handles I2C byte transmission  
4. How to configure SSD1306 display settings  
5. How TXIS and STOPF flags control data flow  
6. How horizontal addressing mode works  
7. How to initialize an OLED display from scratch

## Code Structure

- `ssd1306.h` – SSD1306 macros and function declarations  
- `ssd1306.c` – SSD1306 driver implementation  
- `main.c` – OLED initialization example

## Board

- STM32 Nucleo L4 series

## Disclaimer
This code is for **educational purposes only**.  
I2C communication involves direct register manipulation which may cause **unexpected peripheral behavior if misconfigured**.  
Always verify wiring, pull-up resistors, and voltage compatibility before connecting external peripherals.  
The code may contain bugs or simplifications and is **not intended for production or safety-critical applications**.  
Equip Embedded bears no responsibility for hardware damage, data loss, or other issues resulting from the use or misuse of this code.