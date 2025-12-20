# STM32 Button to LED Function Mapper


Created a bare-metal firmware to map button inputs to LED output logic using GPIO interrupts and polling
mechanisms.
• Authored a custom Makefile, startup code, and linker script to compile and link firmware without using an IDE.
• Built and flashed using GCC ARM toolchain and GDB; validated timing and response through GPIO toggling and LED
behavior.

This STM32F411 project uses EXTI0/1 to detect button presses and map each to a corresponding function (like blinking an LED).
## Features
- Manual register configuration
- Bare-metal interrupt setup
- Custom struct to map button to action

- custom startup and linker file


