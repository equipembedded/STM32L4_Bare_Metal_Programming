All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, .ld, HAL drivers) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — SSD1306 OLED Driver

This repository contains **bare-metal STM32L4 code** demonstrating how to interface an **SSD1306 OLED display** over I2C using direct register access.  
No HAL is used — only CMSIS device headers and memory-mapped peripheral registers.

## Lesson: Drawing Graphics on an SSD1306 OLED

In this lesson, we build a simple graphics library for the SSD1306 OLED display using a framebuffer stored in STM32 memory.

The project demonstrates how to manipulate individual pixels, draw basic shapes, render bitmap fonts, and update the display by transferring the framebuffer to the SSD1306 over I2C.

## Key Concepts Covered

- **Bare-Metal I2C Communication** using STM32 register access
- **SSD1306 Command vs Data Transfers**
- **Frame Buffer Organization**
- **SSD1306 GDDRAM Layout**
- **Pixel Addressing**
- **Drawing Lines**
- **Drawing Rectangles**
- **Drawing Circles**
- **Rendering 5x7 Bitmap Fonts**
- **Updating the Display from RAM**

## Features

- `i2c_write()` – Send command or data bytes over I2C
- `ssd1306_cmd()` – Send SSD1306 command bytes
- `ssd1306_data()` – Send display data bytes
- `ssd1306_init()` – Initialize SSD1306 controller
- `ssd1306_clear_buffer()` – Clear the framebuffer
- `ssd1306_update()` – Copy the framebuffer to the display
- `ssd1306_draw_pixel()` – Draw individual pixels
- `ssd1306_draw_line()` – Draw straight lines
- `ssd1306_draw_rect()` – Draw rectangle outlines
- `ssd1306_draw_circle()` – Draw circle outlines
- `ssd1306_draw_char()` – Draw 5x7 bitmap characters
- `ssd1306_print()` – Print strings

## Hardware Components

- **STM32 Nucleo-STM32L432KC**
- **SSD1306 OLED Display (I2C)**
- **Breadboard and jumper wires**

## Pin Connections

| STM32 Pin | I2C Signal | Function |
|-----------|------------|----------|
| PB6 | SCL | I2C1 Serial Clock (AF4) |
| PB7 | SDA | I2C1 Serial Data (AF4) |

## What You'll Learn

1. How the SSD1306 framebuffer is organized
2. How pixels map into display memory
3. How to draw individual pixels
4. How to draw lines, rectangles, and circles
5. How bitmap fonts are stored and rendered
6. How to display text on the OLED
7. How to update the OLED efficiently from RAM

## Code Structure

- `ssd1306.h` – SSD1306 macros, fonts, and function declarations
- `ssd1306.c` – SSD1306 driver and graphics library
- `main.c` – Graphics and text rendering example

## Board

- STM32 Nucleo-L432KC

## Disclaimer

This code is for **educational purposes only**.  
I2C communication involves direct register manipulation which may cause **unexpected peripheral behavior if misconfigured**.  
Always verify wiring, pull-up resistors, and voltage compatibility before connecting external peripherals.  
The code may contain bugs or simplifications and is **not intended for production or safety-critical applications**.  
Equip Embedded bears no responsibility for hardware damage, data loss, or other issues resulting from the use or misuse of this code.