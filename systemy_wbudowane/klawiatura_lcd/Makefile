# Define compiler and flags
CC = avr-gcc
MMCU = atmega32
CFLAGS = -Wall -Os -mmcu=$(MMCU)

# Source folder
SRCS_DIR := src

# Include folder
INCLUDE_DIR := include

# Source files
SRCS := $(wildcard $(SRCS_DIR)/*.c)
OBJS := $(SRCS:.c=.o)

# Target
TARGET := program

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	avr-objcopy -j .text -j .data -O ihex $(TARGET) $(TARGET).hex

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).hex

.PHONY: all clean