All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, .ld, HAL drivers) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — SSD1306 OLED Driver

This repository contains **bare-metal STM32L4 code** demonstrating how to interface an **SSD1306 OLED display** over I2C using direct register access.  
No HAL is used — only CMSIS device headers and memory-mapped peripheral registers.

## Lesson: Writing Graphics Data to SSD1306 GDDRAM

In this lesson, we extend the SSD1306 bare-metal driver beyond initialization and begin writing directly to the display's **Graphic Display Data RAM (GDDRAM)**.

The project demonstrates how to configure display addressing, clear the OLED, define drawing regions, and render raw bitmap data manually by transmitting byte patterns over I2C.

## Key Concepts Covered

- **Bare-Metal I2C Communication** using STM32 register access
- **SSD1306 Command vs Data Transfers**
- **Control Byte Usage** (`0x00` for commands, `0x40` for display data)
- **Horizontal Addressing Mode**
- **Column and Page Addressing** using `0x21` and `0x22`
- **SSD1306 GDDRAM Layout**
- **Display Memory Window Selection**
- **Writing Raw Bitmap Data**
- **Manual Character Rendering**

## Features

- `i2c_write()` – Send command or data bytes over I2C
- `ssd1306_cmd()` – Send SSD1306 command bytes
- `ssd1306_data()` – Send display data bytes
- `ssd1306_init()` – Initialize SSD1306 controller
- Display clearing using full GDDRAM writes
- Partial display region addressing
- Rendering custom bitmap patterns directly to the OLED

## Hardware Components

- **STM32 Nucleo-STM32L432KC**
- **SSD1306 OLED Display (I2C)**
- **Breadboard and jumper wires**
- **Logic Analyzer** (optional)

## Pin Connections

| STM32 Pin | I2C Signal | Function |
|-----------|------------|----------|
| PB6 | SCL | I2C1 Serial Clock (AF4) |
| PB7 | SDA | I2C1 Serial Data (AF4) |

## What You'll Learn

1. How SSD1306 GDDRAM is organized
2. How to select column and page address ranges
3. How command and data transfers differ
4. How to clear OLED display memory
5. How raw bytes map to vertical pixel columns
6. How bitmap characters are rendered manually
7. How STM32 I2C hardware handles SSD1306 transactions

## Code Structure

- `ssd1306.h` – SSD1306 macros and declarations
- `ssd1306.c` – SSD1306 driver implementation
- `main.c` – Display memory addressing and rendering example

## Board

- STM32 Nucleo L4 series

## Disclaimer
This code is for **educational purposes only**.  
I2C communication involves direct register manipulation which may cause **unexpected peripheral behavior if misconfigured**.  
Always verify wiring, pull-up resistors, and voltage compatibility before connecting external peripherals.  
The code may contain bugs or simplifications and is **not intended for production or safety-critical applications**.  
Equip Embedded bears no responsibility for hardware damage, data loss, or other issues resulting from the use or misuse of this code.