
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -I./include

# Linker flags (ensure paths to libglfw and libmlx42 are correct)
LDFLAGS = -L./lib -lmlx42 -lglfw -ldl -lm

# Source files
SOURCES = main.c init.c render.c game.c cleanup.c map_check.c image_block_gen.c error.c ft_strlen.c get_next_line.c get_next_line_utis.c helper_function.c helper_function2.c
# Object files (same as source files but with .o extension)
OBJECTS = $(SOURCES:.c=.o)

# Executable name
EXECUTABLE = game

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