# STM32 Sensor Firmware

Bare-metal firmware for an STM32F103 "Blue Pill" board that communicates with SPI sensors and prints data over USART.

## Project Overview

This repository contains a minimal embedded firmware stack written in C.

- `main/` - application entry point, startup code, and the firmware `Makefile`
- `gpio/` - GPIO register definitions and helper functions
- `uart/` - USART driver and formatted serial output
- `spi/` - SPI1 driver and sensor register access
- `core/` - core utility functions and low-level MCU helpers
- `mode_config.md` / `pin_config.md` - STM32 GPIO configuration reference notes

The main firmware initializes UART1 and SPI1, configures an SPI sensor, reads calibration/data registers, and continuously prints sensor output.

## Features

- SPI1 master support for SPI sensor communication
- Manual chip-select control for external sensor devices
- USART1 serial debug output
- Bare-metal register-level drivers for STM32F103
- Simple build pipeline using `arm-none-eabi-gcc`

## Build Instructions

Requirements:

- `arm-none-eabi-gcc`
- `arm-none-eabi-objcopy`

Build from the `main` directory:

```bash
cd /home/lemon/code/c-codes/firmware_developement/main
make
```

This produces:

- `BMP280.elf`
- `BMP280.bin`

## Project Structure

- `main/main.c` - application logic and sensor communication loop
- `main/startup.c` - MCU startup code
- `main/linker.ld` - linker script for the target firmware image
- `core/core.c`, `core/core.h` - common low-level functions
- `gpio/gpio.c`, `gpio/gpio.h` - GPIO configuration and pin helpers
- `uart/uart.c`, `uart/uart.h` - USART initialization and output helpers
- `spi/spi.c`, `spi/spi.h` - SPI1 driver and generic sensor read/write helpers

## Hardware Notes

- `SPI1` on Blue Pill uses:
  - `PA5` = SCK
  - `PA6` = MISO
  - `PA7` = MOSI
- The current sensor chip select pin is controlled with `BMP280_CS_PIN` defined in `main/main.h`
- UART1 is typically available on `PA9`/`PA10`

## Usage

1. Build the firmware.
2. Flash `main/BMP280.bin` to the STM32F103 board using your preferred programmer.
3. Open a serial terminal at the configured baud rate.
4. The board prints sensor data continuously.

## Notes

- The firmware is intentionally small and platform-specific; it does not depend on HAL or standard library support.
- `mode_config.md` and `pin_config.md` contain STM32 GPIO configuration notes useful for extending or modifying pin assignments.

## License

No license file is included. Use and adapt this firmware according to your own project requirements.
