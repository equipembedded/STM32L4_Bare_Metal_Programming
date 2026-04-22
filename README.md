All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, .ld, HAL drivers) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — ICM-20948 Interface (Lesson 11)

This repository contains **bare-metal STM32L4 code** demonstrating how to **interface an ICM-20948 9-axis motion tracking device** over SPI.  
No HAL is used — only CMSIS device headers and memory-mapped registers.

## Lesson 11: ICM-20948 Interface
In this lesson, we build on the SPI driver from Lesson 09 to **communicate with the ICM-20948 sensor**.  
You'll learn how to read the WHO_AM_I register, verify device identity, and implement robust SPI read/write functions.

## Key Concepts Covered
- **ICM-20948 Protocol**: Register map, read/write bit convention  
- **SPI Read Operation**: Sending address with READ_BIT (0x80), reading response  
- **SPI Write Operation**: Sending address with WRITE_BIT (0x00), then data  
- **Device Verification**: Reading WHO_AM_I register (expected 0xEA)  
- **Robust SPI Functions**: Full-duplex tx/rx for 8-bit transfers  
- **Bare-Metal Sensor Integration**: Direct register access without HAL

## Features
- `spi_init()` – Configure SPI1 in master mode with software slave management  
- `spi_tx_8bit(uint8_t data)` – Transmit a single byte over SPI, return received byte  
- Manual CS control via GPIO  
- ICM-20948 WHO_AM_I verification routine  
- Direct register manipulation of SPI1 peripheral

## Hardware Components
- **STM32 Nucleo-STM32L432**  
- **ICM-20948 9-axis motion tracking device** (smartphones, wearables, IoT, drones)  
- **Logic Analyzer** (optional, for debugging SPI signals)

## Pin Connections
| STM32 Pin | SPI Signal | Function                        |
|-----------|------------|---------------------------------|
| PA4       | CS         | Chip Select (GPIO controlled)   |
| PA5       | SCK        | Serial Clock (AF5)              |
| PA6       | MISO       | Master In Slave Out (AF5)       |
| PA7       | MOSI       | Master Out Slave In (AF5)       |

## What You'll Learn
1. How to read from an SPI sensor using bare-metal code  
2. How to interpret an ICM-20948 datasheet for register access  
3. How to send the READ_BIT (0x80) before the register address  
4. How to verify device connection using WHO_AM_I (0xEA)  
5. How to debug SPI transactions with a logic analyzer  
6. How to extend a generic SPI driver for a specific peripheral  
7. How to handle CS assertion/deassertion timing for reads

## Code Structure
- `spi.h` – Function prototypes and register definitions  
- `spi.c` – SPI driver implementation (init, tx/rx)  
- `main.c` – ICM-20948 WHO_AM_I read and verification loop

## Board
- STM32 Nucleo L4 series

## Disclaimer
This code is for **educational purposes only**.  
SPI communication involves direct register manipulation which may cause **unexpected peripheral behavior if misconfigured**.  
Always verify timing constraints with a logic analyzer before connecting to sensitive SPI devices.  
The code may contain bugs or simplifications and is **not intended for production or safety-critical applications**.