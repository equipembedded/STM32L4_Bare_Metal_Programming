All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, .ld, HAL drivers) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — SSD1306 I2C Interface

This repository contains **bare-metal STM32L4 code** demonstrating how to **interface an SSD1306 OLED display** over I2C.  
No HAL is used — only CMSIS device headers and memory-mapped registers.

## Lesson: SSD1306 I2C Interface
In this lesson, we build a minimal **bare-metal I2C driver** for STM32L432 and verify communication with an SSD1306 OLED display using address ACK detection.

## Key Concepts Covered
- **I2C Standard Mode**: 100kHz bus configuration  
- **I2C Peripheral Initialization**: TIMINGR configuration and PE control  
- **7-bit Addressing**: STM32 hardware-managed address phase  
- **ACK/NACK Detection**: Verifying slave response through ISR flags  
- **START and STOP Generation**: Basic I2C transaction control  
- **Open-Drain Communication**: Proper SDA/SCL GPIO configuration  
- **Bare-Metal I2C Communication**: Direct register manipulation without HAL

## Features
- `i2c_init()` – Configure I2C1 for 100kHz standard mode  
- `i2c_check_addr(uint8_t addr)` – Verify slave ACK response  
- Automatic START and STOP generation  
- Direct register manipulation of I2C1 peripheral  
- Minimal bare-metal I2C implementation

## Hardware Components
- **STM32 Nucleo-STM32L432**  
- **SSD1306 OLED Display**  
- **Breadboard and jumper wires**  
- **Logic Analyzer** (optional, for debugging I2C traffic)

## Pin Connections
| STM32 Pin | I2C Signal | Function                  |
|-----------|------------|---------------------------|
| PB6       | SCL        | I2C1 Serial Clock (AF4)  |
| PB7       | SDA        | I2C1 Serial Data (AF4)   |

## What You'll Learn
1. How to initialize I2C1 without HAL  
2. How STM32 handles 7-bit slave addressing  
3. How to detect ACK and NACK responses  
4. How START and STOP conditions are generated  
5. How to configure open-drain GPIO for I2C  
6. How pull-up resistors affect I2C communication  
7. How to validate I2C communication with SSD1306

## Code Structure
- `i2c.h` – Function prototypes and interface definitions  
- `i2c.c` – I2C driver implementation  
- `main.c` – SSD1306 address ACK verification loop

## Board
- STM32 Nucleo L4 series

## Disclaimer
This code is for **educational purposes only**.  
I2C communication involves direct register manipulation which may cause **unexpected peripheral behavior if misconfigured**.  
Always verify wiring, pull-up resistors, and voltage compatibility before connecting external peripherals.  
The code may contain bugs or simplifications and is **not intended for production or safety-critical applications**.  
Equip Embedded bears no responsibility for hardware damage, data loss, or other issues resulting from the use or misuse of this code.