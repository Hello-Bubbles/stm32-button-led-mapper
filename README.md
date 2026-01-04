<img width="324" height="463" alt="image" src="https://github.com/user-attachments/assets/5ef83c26-4473-494e-8452-efc3f0431dab" />STM32 BUTTON-TO-LED MAPPER (BARE-METAL)

A bare-metal STM32F411 firmware project that maps button interrupts (EXTI)
to LED actions using a function-pointer mapping table, similar to a small
software interrupt table.

The project is built without an IDE and includes a custom startup file,
linker script, and Makefile to demonstrate the complete embedded firmware
bring-up flow.

## Design Rationale

Why function pointers?
Avoids large if/else or switch-case blocks
Makes button behavior extensible without touching ISR logic
Mirrors real-world embedded patterns (keypads, menu systems, HMI)

Why a common ISR?
Reduces duplicated code
Centralizes EXTI clearing logic
Keeps interrupt latency predictable

Why bare-metal build (no IDE)?

Forces understanding of:
startup flow
linker memory layout
vector table placement
toolchain-driven builds


TARGET / HARDWARE
-----------------
MCU      : STM32F411 (Cortex-M4)
Inputs   : Buttons on PD0 / PD1 (EXTI0 / EXTI1)
Outputs  : LEDs on PD12 / PD13
Approach : Register-level programming (no HAL / LL)


FEATURES
--------
- GPIO configuration using MODER / OTYPER / PUPDR registers
- EXTI interrupt configuration for button inputs
- NVIC interrupt enable for EXTI0 and EXTI1
- Button-to-action mapping using function pointers
- Common interrupt handler to reduce duplicated ISR logic

  

WHAT MAKES THIS PROJECT PORTFOLIO-WORTHY
----------------------------------------
Even though the application is small, this project includes the complete
bare-metal firmware infrastructure that many demos omit:

- startup.c
  - Vector table (.isr_vector)
  - Reset handler entry point
  - Weak aliases for unused interrupts

- linker.ld
  - FLASH and SRAM memory regions
  - Section placement for vector table, code, data, and bss
  - Symbol definitions used during startup

- Makefile
  - GCC ARM toolchain build (arm-none-eabi-gcc)
  - No IDE dependency
  - Generates ELF and MAP files for inspection

This demonstrates understanding of:
- toolchain-based builds
- linker and memory layout
- MCU startup and interrupt vector mapping


PROJECT STRUCTURE
-----------------
main.c ----->   Application logic (GPIO, EXTI, mapping table)
startup.c --->  Vector table and reset/startup code
linker.ld---->  Memory map and section placement
makefile---->   Build system (no IDE)
stm32f4xx.h---> Minimal register definitions


BUILD INSTRUCTIONS
------------------
Prerequisite:
- arm-none-eabi-gcc toolchain installed

Build firmware:
    make

Artifacts generated:
- final.elf   Firmware image
- final.map   Linker map file

Clean build:
    make clean


FLASHING / DEBUGGING
-------------------
The firmware was built and tested using arm-none-eabi-gdb directly,
without relying on an IDE.

Flashing was performed from within GDB using monitor commands
provided by the debug probe/server.

Typical workflow:
1. Build the firmware ELF using the Makefile
2. Launch GDB with the ELF file
3. Flash the image to the target using a monitor command
4. Debug using breakpoints, register inspection, and memory examination

Example:
    arm-none-eabi-gdb final.elf

Inside GDB:
    target remote <debug-probe>
    monitor flash write_image erase final.elf
    monitor reset
    continue

This approach allows verification of startup code execution,
vector table placement, and EXTI interrupt handling at the
instruction and register level.



HOW IT WORKS (HIGH LEVEL)
-------------------------
1. Configure PD12 and PD13 as output pins for LEDs
2. Configure PD0 and PD1 as input pins with pull-down resistors
3. Route PD0/PD1 to EXTI0/EXTI1 via SYSCFG EXTICR registers
4. Enable EXTI interrupt lines and NVIC IRQs
5. Define a mapping table of button lines to callback functions
6. Interrupt handler clears the EXTI pending bit and calls the mapped action


MAPPING TABLE CONCEPT
---------------------
Each button is associated with a callback function:

- Button on EXTI0 -> blink LED1
- Button on EXTI1 -> blink LED2

To add new functionality:
- Write a new callback function
- Add one entry to the mapping table

The interrupt logic itself does not need to change.

## What I Learned / Bugs I Hit

How the Cortex-M reset flow jumps from vector table → Reset_Handler
Importance of correct vector table placement in FLASH
Why unused interrupts should have weak aliases
EXTI pitfalls:
forgetting to clear pending bits causes repeated interrupts
incorrect SYSCFG EXTICR mapping breaks EXTI routing
NVIC enable alone is not enough — EXTI + SYSCFG + GPIO must all agree
How linker symbols are used during startup for .data and .bss init
How to debug early startup code before main() using GDB

## Limitations

Busy-wait delay (not timer-based)
No button debounce logic
Only two EXTI lines demonstrated
Minimal register header (not CMSIS-complete)
No low-power modes used

## Possible Extensions

Add software debounce using a timer
Support both rising and falling edge triggers
Expand mapping table to support:
long-press
double-click
Replace busy-wait with SysTick or TIM delay
Add event queue instead of direct callback invocation
Extend to matrix keypad scanning
N

