# Embedded C Projects - Freshman Year Training Code

This repository contains a collection of Embedded C projects developed during my freshman year training. These projects focus on fundamental embedded systems concepts using AVR microcontrollers.

## Overview

This collection serves as a foundational learning experience in embedded programming, covering various peripherals and basic control logic. Each subdirectory represents a distinct project or module, demonstrating different functionalities.

## Features (Examples from ADC project)

- **Analog-to-Digital Conversion (ADC)**: Reading analog sensor data.
- **LCD Interfacing**: Displaying information on a Liquid Crystal Display.
- **Temperature Monitoring**: Example of reading temperature (or a similar analog value) and taking action based on thresholds.
- **Digital Output Control**: Controlling LEDs or other digital outputs based on sensor readings.

## Project Structure

The repository is organized into several subdirectories, each containing a specific embedded C project.

- `ADC/`: Analog-to-Digital Converter project, likely for reading sensor data and displaying it on an LCD.
    - `ADC.c`: Main C source file for the ADC project.
    - `ADC.APS`, `ADC.AWS`: Project files (possibly from an IDE like Atmel Studio).
    - `hfuse.bin`, `lfuse.bin`: Fuse bit settings for the AVR microcontroller.
- `BELL-1/`, `BELL-2/`, `BELL1/`, `BELL2/`: Likely projects related to controlling bells or sound outputs.
- `Black-white/`: Could be related to image processing or simple display patterns.
- `CLOCK/`: A project for implementing a real-time clock or timer.
- `converging/`: Potentially a project involving converging patterns or signals.
- `Distancemeasure/`: Project for measuring distance using sensors (e.g., ultrasonic).
- `HEART/`: Could be related to heart rate monitoring or a heart-shaped LED display.
- `KEYPAD/`: Interfacing with a keypad for user input.
- `LCDstringnum/`: Demonstrates displaying strings and numbers on an LCD.
- `LFR/`: Line Follower Robot related code.
- `LOADING/`: Possibly a loading animation or progress indicator.
- `newshapes/`: Projects for displaying new shapes on a graphical display or LEDs.
- `sinleleftshift/`: Likely a project demonstrating bitwise operations, specifically left shifts.

## Technologies Used

- **AVR Microcontrollers**: The primary target platform for these embedded C projects.
- **Embedded C**: Programming language used for development.
- **Atmel Studio / AVR-GCC**: Development environment and compiler.
- **Various Peripherals**: LCDs, ADCs, GPIOs, etc.

## Setup and Compilation

To compile and run these projects, you will typically need:

1. **AVR Toolchain**: Install `avr-gcc`, `avr-libc`, and `avrdude`.
2. **Development Environment**: An IDE like Atmel Studio (Windows) or VS Code with appropriate extensions (cross-platform) can be used.
3. **Programmer**: An AVR ISP programmer (e.g., USBasp, AVRISP mkII) to flash the compiled `.hex` files onto the microcontroller.

**General Compilation Steps (Example for `ADC.c`):**

```bash
# Compile the C source file
avr-gcc -mmcu=atmega32 -Os -c ADC.c -o ADC.o

# Link the object file to create an executable
avr-gcc -mmcu=atmega32 -o ADC.elf ADC.o

# Convert the ELF file to Intel HEX format
avr-objcopy -O ihex -R .eeprom ADC.elf ADC.hex

# Flash the .hex file to the microcontroller (replace with your programmer and port)
avrdude -c usbasp -p m32 -U flash:w:ADC.hex:i
```

*(Note: Specific `mmcu` and programmer details may vary per project and hardware setup.)*
