All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, linker script, CMSIS device headers, etc.) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — STM32 Clock Configuration (RCC & PLL)

This repository contains **bare-metal STM32L4 code** demonstrating how to configure the **Reset and Clock Control (RCC)** peripheral using direct register access.

No HAL is used—only CMSIS device headers and memory-mapped peripheral registers.

## Lesson: Configuring the STM32 System Clock

In this lesson, we configure the STM32L432KC to run at **80 MHz** using the internal **HSI16 oscillator** and the **Phase-Locked Loop (PLL)**.

The project also demonstrates how to output the system clock using the **Microcontroller Clock Output (MCO)** pin, allowing the clock frequency to be verified with an oscilloscope or logic analyzer.

## Key Concepts Covered

- **Reset and Clock Control (RCC)**
- **HSI16 Internal Oscillator**
- **Phase-Locked Loop (PLL)**
- **Flash Wait States**
- **System Clock (SYSCLK)**
- **PLL Configuration**
- **Clock Switching**
- **Microcontroller Clock Output (MCO)**
- **Verifying the System Clock with an Oscilloscope or Logic Analyzer**

## Features

- `rcc_pll80mhz_init()` – Configure the system clock to 80 MHz using the PLL
- Output SYSCLK on the MCO pin (PA8)
- Verify the configured clock frequency externally

## Hardware Components

- **STM32 Nucleo-L432KC**
- **Oscilloscope or Logic Analyzer (optional)**
- **Breadboard and jumper wires (optional)**

## Pin Connections

| STM32 Pin | Function |
|-----------|----------|
| PA8 | MCO (Microcontroller Clock Output) |

## What You'll Learn

1. How the STM32 clock tree works
2. Why the default clock configuration is not the maximum operating frequency
3. How to configure the PLL
4. How to switch the system clock to the PLL
5. Why Flash wait states are required
6. How to output SYSCLK using MCO
7. How to verify the clock frequency with test equipment

## Code Structure

- `clocks.h` – Clock configuration function declarations
- `clocks.c` – RCC and PLL initialization
- `main.c` – MCO configuration example

## Board

- STM32 Nucleo-L432KC

## Disclaimer

This code is for **educational purposes only**.
Clock configuration involves direct register manipulation, which may prevent the microcontroller from operating correctly if configured improperly.
Always verify your clock settings against the reference manual and datasheet for your specific STM32 device.
The code may contain bugs or simplifications and is **not intended for production or safety-critical applications**.
Equip Embedded bears no responsibility for hardware damage, data loss, or other issues resulting from the use or misuse of this code.