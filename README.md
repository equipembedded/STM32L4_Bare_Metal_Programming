All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, linker script, CMSIS device headers, etc.) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — USART Communication

This repository contains **bare-metal STM32L4 code** demonstrating how to configure and use **USART2** for serial communication.

No HAL is used—only CMSIS device headers and memory-mapped peripheral registers.

## Lesson: USART Communication

In this lesson, we configure **USART2** for asynchronous serial communication at **115200 baud**.

The STM32L432KC is running at **80 MHz**. USART2 is configured with:

- TX for transmitting data
- RX for receiving data
- 115200 baud rate
- Asynchronous communication

The program waits for a character to be received and then sends it back through the USART connection.

The received character can also control an LED:

- Send `h` to turn the LED on
- Send `l` to turn the LED off

## Key Concepts Covered

- Bare-metal USART configuration
- Asynchronous serial communication
- USART transmitter and receiver
- Baud rate configuration
- USART status and data registers
- Character transmission
- Character reception
- String transmission
- GPIO alternate functions
- Direct register access
- UART vs. USART

## Features

- USART2 initialization
- 115200 baud communication
- Character transmission
- Character reception
- String transmission
- Echoing received characters
- LED control using serial commands
- No HAL or third-party libraries

## Hardware Components

- STM32 Nucleo-L432KC
- USB connection to the onboard ST-LINK
- Serial terminal application

## USART Configuration

| Parameter | Value |
| --------- | ----- |
| System Clock | 80 MHz |
| Peripheral | USART2 |
| Baud Rate | 115200 |
| TX Pin | PA2 |
| RX Pin | PA15 |
| TX Alternate Function | AF7 |
| RX Alternate Function | AF3 |
| Communication Mode | Asynchronous |
| Data Direction | Transmit and Receive |

## What You'll Learn

1. How to enable the USART2 peripheral clock
2. How to configure GPIO pins for USART alternate functions
3. How to configure the USART baud rate
4. How to enable the USART transmitter and receiver
5. How to transmit a character
6. How to transmit a string
7. How to receive a character
8. How to use USART communication to control an LED
9. The difference between UART and USART
10. How asynchronous serial communication works


## Disclaimer

This code is provided for **educational purposes only**.

It demonstrates direct register-level programming of the STM32 microcontroller without using the STM32 HAL. While every effort has been made to keep the code simple and easy to understand, it may contain bugs, omissions, or simplifications.

Always consult the reference manual and datasheet for your specific hardware before using this code in your own projects.

This project is **not intended for production, commercial, or safety-critical applications**.

Equip Embedded assumes no responsibility for injury, hardware damage, data loss, or other issues resulting from the use or misuse of this code.