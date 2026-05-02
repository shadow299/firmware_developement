# Project name
TARGET = blink

# Toolchain
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# Flags
CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -Wall -nostdlib -ffreestanding
LDFLAGS = -T linker.ld

# Source files
SRCS = main.c startup.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET).bin

# Compile
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link
$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Convert to binary
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Clean
clean:
	rm -f *.o *.elf *.bin