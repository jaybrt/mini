# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -pedantic

# Source file
SRC = mini.c

# Build directory
BUILD_DIR = build

# Executable name
EXEC = $(BUILD_DIR)/mini

# Default target
all: $(EXEC)

# Rule to create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to make executable
$(EXEC): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Clean rule
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
