All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, .ld, HAL drivers) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — SPI Communication (Lesson 09)

This repository contains **bare-metal STM32L4 code** demonstrating how to **implement SPI (Serial Peripheral Interface) communication**.  
No HAL is used — only CMSIS device headers and memory-mapped registers.

## Lesson 09: SPI Communication
In this lesson, we build an **SPI driver from scratch** to communicate with SPI peripherals.  
You'll learn how to configure SPI in master mode, generate clock signals, and transmit data to SPI devices.

## Key Concepts Covered
- **SPI Protocol**: Understanding MOSI, MISO, SCK, and CS lines  
- **Master Mode Configuration**: Setting up STM32 as SPI master  
- **Software Slave Management**: Using SSM and SSI bits for manual CS control  
- **Baud Rate Generation**: Configuring clock dividers for proper SPI speed  
- **Blocking Transmission**: Polling TXE flag for data transmission  
- **Bare-Metal Driver Design**: Creating reusable functions for SPI initialization and transmission

## Features
- `spi_init()` – Configure SPI1 in master mode with software slave management  
- `spi_en()` – Enable SPI peripheral  
- `spi_tx_8bit(uint8_t data)` – Transmit a single byte over SPI (blocking)  
- Manual CS control via GPIO  
- Direct register manipulation of SPI1 peripheral  
- Ready-to-use, reusable bare-metal driver functions

## Hardware Components
- **STM32 Nucleo-STM32L432**  
- **SPI Peripheral** (sensor, display, or any SPI device)  
- **Oscilloscope/Logic Analyzer** (optional, for visualizing SPI signals)

## Pin Connections
| STM32 Pin | SPI Signal | Function                        |
|-----------|------------|---------------------------------|
| PA4       | CS         | Chip Select (GPIO controlled)   |
| PA5       | SCK        | Serial Clock (AF5)              |
| PA6       | MISO       | Master In Slave Out (AF5)       |
| PA7       | MOSI       | Master Out Slave In (AF5)       |

## What You'll Learn
1. How to configure SPI peripheral registers (CR1, CR2, SR, DR)  
2. How to set baud rate using prescaler bits (BR[2:0])  
3. How to enable software slave management for manual CS control  
4. How to poll TXE flag for transmit buffer status  
5. How to structure reusable bare-metal peripheral drivers  
6. How to manage CS timing before and after transmission  
7. The relationship between clock speed, baud rate, and SPI timing

## Code Structure
- `spi.h` – Function prototypes and register definitions  
- `spi.c` – SPI driver implementation (initialization, enable, transmit)  
- `main.c` – GPIO configuration and SPI demo with 0x5A transmission

## Board
- STM32 Nucleo L4 series

## Disclaimer
This code is for **educational purposes only**.  
SPI communication involves direct register manipulation which may cause **unexpected peripheral behavior if misconfigured**.  
Always verify timing constraints with an oscilloscope or logic analyzer before connecting to sensitive SPI devices.  
The code may contain bugs or simplifications and is **not intended for production or safety-critical applications**.
