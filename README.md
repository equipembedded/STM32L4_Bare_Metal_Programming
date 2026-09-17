All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, linker script, CMSIS device headers, etc.) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — GPS Communication Using USART

This repository contains **bare-metal STM32L4 code** demonstrating how to communicate with an **ATGM336H GPS receiver** using USART1 and forward the received data through USART2 to a serial terminal.

No HAL is used—only CMSIS device headers and memory-mapped peripheral registers.

## Lesson: GPS Communication Using USART

In this lesson, we configure **USART1** to communicate with an ATGM336H GPS receiver at **9600 baud**.

The STM32L432KC is running at **80 MHz**. USART1 is configured with:

- TX for transmitting data to the GPS receiver
- RX for receiving data from the GPS receiver
- 9600 baud rate
- Asynchronous communication

USART2 is configured to communicate with a PC running a serial terminal such as PuTTY.

The STM32 receives the GPS data one character at a time through USART1 and immediately sends it through USART2 so the raw GPS data can be viewed on the PC.

The GPS receiver sends its navigation data using the **NMEA 0183** format.

## Key Concepts Covered

- Bare-metal USART configuration
- Asynchronous serial communication
- USART transmitter and receiver
- Baud rate configuration
- USART status and data registers
- Character transmission
- Character reception
- GPIO alternate functions
- Direct register access
- GPS communication
- NMEA 0183 data
- Raw GPS data

## Features

- USART1 initialization for GPS communication
- USART2 initialization for PC communication
- 9600 baud communication
- Character reception
- Character transmission
- Forwarding GPS data from USART1 to USART2
- Viewing raw NMEA data using a serial terminal
- No HAL or third-party libraries

## Hardware Components

- STM32 Nucleo-L432KC
- ATGM336H GPS receiver
- USB connection to the onboard ST-LINK
- Serial terminal application such as PuTTY

## USART Configuration

| Parameter | USART1 | USART2 |
| --------- | ------ | ------ |
| Purpose | GPS communication | PC/terminal communication |
| Baud Rate | 9600 | 9600 |
| TX Pin | PA9 | PA2 |
| RX Pin | PA10 | PA15 |
| TX Alternate Function | AF7 | AF7 |
| RX Alternate Function | AF7 | AF3 |
| Communication Mode | Asynchronous | Asynchronous |
| Data Direction | Transmit and Receive | Transmit and Receive |

## GPS Connection

The ATGM336H GPS receiver is connected to USART1:

- GPS TXD → STM32 PA10 (USART1 RX)
- GPS RXD → STM32 PA9 (USART1 TX)
- GPS GND → STM32 GND

The GPS receiver continuously sends NMEA messages through its TXD pin.

## Example NMEA Messages

The GPS receiver can send different types of NMEA messages, including:

- `$GNGGA` — Position and fix information
- `$GNGSA` — Satellite and position solution information
- `$GPGSV` — GPS satellites in view
- `$BDGSV` — BeiDou satellites in view
- `$GNRMC` — Basic navigation information
- `$GNVTG` — Course and speed information
- `$GNZDA` — Date and time information
- `$GPTXT` — Receiver status information

In this lesson, the STM32 does not parse these messages. It simply forwards the raw data to the PC so they can be viewed in a serial terminal.

## What You'll Learn

1. How to enable the USART1 and USART2 peripheral clocks
2. How to configure GPIO pins for USART alternate functions
3. How to configure the USART baud rate
4. How to enable the USART transmitter and receiver
5. How to receive data from a GPS receiver
6. How to transmit a character through USART
7. How to forward data from one USART to another
8. How to view raw GPS NMEA data using PuTTY
9. The difference between UART and USART
10. How GPS receivers communicate with microcontrollers using asynchronous serial communication

## Disclaimer

This code is provided for **educational purposes only**.

It demonstrates direct register-level programming of the STM32 microcontroller without using the STM32 HAL. While every effort has been made to keep the code simple and easy to understand, it may contain bugs, omissions, or simplifications.

Always consult the reference manual and datasheet for your specific hardware before using this code in your own projects.

This project is **not intended for production, commercial, or safety-critical applications**.

Equip Embedded assumes no responsibility for injury, hardware damage, data loss, or other issues resulting from the use or misuse of this code.