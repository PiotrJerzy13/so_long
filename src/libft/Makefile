# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Library name
NAME = libft.a

# Build directory
BUILD_DIR = build

# Source files for libft
SOURCES = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_utoa_base.c \
	ft_printf.c ft_putunsignednbr_fd.c print_hex.c \
	get_next_line.c ft_strleni.c ft_realloc.c

# Object files in build directory
OBJECTS = $(SOURCES:%.c=$(BUILD_DIR)/%.o)

# Bonus source files
BSOURCES = \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

# Bonus object files in build directory
BOBJECTS = $(BSOURCES:%.c=$(BUILD_DIR)/%.o)

# Main target
all: $(NAME)

# Rule to create build directory and compile .c to .o 
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I./ -c $< -o $@

# Rule for creating the library
$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

# Rule for bonus part of the library
bonus: $(OBJECTS) $(BOBJECTS)
	ar rcs $(NAME) $(OBJECTS) $(BOBJECTS)

# Clean up object files
clean:
	rm -rf $(BUILD_DIR)

# Clean up object files and the library
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all bonus clean fclean re
