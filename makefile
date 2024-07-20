# Compiler
CC = cc

# Compiler flags
CFLAGS = -I./include -I./libft

# Linker flags (ensure paths to libglfw and libmlx42 are correct)
LDFLAGS = -L./lib -lmlx42 -lglfw -ldl -lm -L./libft -lft

# Source files
SOURCES = main.c init.c render.c movement.c map_check.c image_block_gen.c utils.c helper_function.c helper_function2.c validation.c

# Build directory
BUILD_DIR = build

# Object files (same as source files but with .o extension in build directory)
OBJECTS = $(SOURCES:%.c=$(BUILD_DIR)/%.o)

# Executable name
EXECUTABLE = so_long

# Default target
all: $(EXECUTABLE)

# Rule to create the executable
$(EXECUTABLE): $(OBJECTS) libft/libft.a
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Rule to create object files in the build directory
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure libft is built
libft/libft.a:
	make -C libft all

# Clean up build files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	make -C libft clean

fclean: clean
	rm -f $(EXECUTABLE)
	make -C libft fclean

re: fclean all

