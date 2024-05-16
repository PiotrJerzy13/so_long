# Compiler
CC = gcc

# Compiler flags
CFLAGS = -I./include

# Linker flags
LDFLAGS = -L./lib -lmlx42 -lglfw -ldl -lm

# Source files
SOURCES = simple_window.c

# Object files (same as source files but with .o extension)
OBJECTS = $(SOURCES:.c=.o)

# Executable name
EXECUTABLE = simple_window

# Default target
all: $(EXECUTABLE)

# Rule to create the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Rule to create object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
