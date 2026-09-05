All code written by Equip Embedded in this repository is licensed under the MIT License.
STM32CubeIDE-generated files (startup, linker script, CMSIS device headers, etc.) remain under STMicroelectronics copyright.

# STM32 Nucleo Bare-Metal Series — External Interrupts (EXTI)

This repository contains **bare-metal STM32L4 code** demonstrating how to configure and use **external interrupts (EXTI)** to respond to a button press.

No HAL is used—only CMSIS device headers and memory-mapped peripheral registers.

## Lesson: External Interrupts (EXTI)

In this lesson, we configure a **GPIO pin as a button input** and use the **EXTI peripheral** to generate an interrupt whenever the button is pressed.

The STM32L432KC is running at **80 MHz**. EXTI is configured with:

- PA1 mapped as the EXTI1 interrupt source
- Falling-edge trigger detection
- Interrupt unmasked and enabled in the NVIC

When the button is pressed, the EXTI1 interrupt fires and the ISR toggles an LED on PA0.

The LED state is controlled entirely from within the interrupt service routine—no polling is used in the main loop.

## Key Concepts Covered

- Bare-metal EXTI configuration
- Mapping a GPIO pin to an EXTI line via SYSCFG
- Edge-triggered interrupt detection (falling edge)
- NVIC interrupt enable
- Writing an interrupt service routine (ISR)
- Clearing a write-1-to-clear pending flag correctly
- Reading GPIO input state from within an ISR
- Toggling GPIO output state from within an ISR
- Low-power idle using `__WFI()`
- Direct register access

## Features

- EXTI1 initialization
- Falling-edge triggered interrupt
- Button-controlled LED toggle
- Interrupt-driven design (no polling)
- Low-power wait-for-interrupt main loop
- No HAL or third-party libraries

## Hardware Components

- STM32 Nucleo-L432KC
- Onboard user button / external push-button
- Onboard or external LED
- USB connection to the onboard ST-LINK

## EXTI Configuration

| Parameter | Value |
| --------- | ----- |
| System Clock | 80 MHz |
| Peripheral | EXTI1 |
| Trigger Edge | Falling |
| Button Pin | PA1 |
| LED Pin | PA0 |
| Pull Configuration | Pull-up (button input) |
| Interrupt Controller | NVIC |
| Power Mode | Wait-for-interrupt (`__WFI()`) |

## What You'll Learn

1. How to enable the GPIOA and SYSCFG peripheral clocks
2. How to configure GPIO pins for digital input and output
3. How to map a GPIO pin to an EXTI line using SYSCFG
4. How to configure falling-edge trigger detection
5. How to unmask and enable an EXTI interrupt line
6. How to enable an interrupt in the NVIC
7. How to write and structure an interrupt service routine (ISR)
8. How to correctly clear a write-1-to-clear pending flag
9. How to read and toggle GPIO state from within an ISR
10. How to use `__WFI()` for low-power idle in the main loop

## Disclaimer

This code is provided for **educational purposes only**.

It demonstrates direct register-level programming of the STM32 microcontroller without using the STM32 HAL. While every effort has been made to keep the code simple and easy to understand, it may contain bugs, omissions, or simplifications.

Always consult the reference manual and datasheet for your specific hardware before using this code in your own projects.

This project is **not intended for production, commercial, or safety-critical applications**.

Equip Embedded assumes no responsibility for injury, hardware damage, data loss, or other issues resulting from the use or misuse of this code.
