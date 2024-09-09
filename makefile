NAME = so_long

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

CFLAGS_MLX := -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX := ./lib/MLX42

HEADERS := -I ./include -I $(LIBMLX)/include

LIBFTNAME = bin/libft/libft.a
LIBFTDIR = src/libft
OBJDIR = ./bin
SRCDIR = ./src

LIBMLXA := $(LIBMLX)/build/libmlx42.a
MLX_PATH := lib/MLX42

HEADERS := -I ./include -I $(LIBMLX)/include
LIB_MLX := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRC_MLX := $(shell find ./src -iname "*.c")
OBJ_MLX := ${SRC_MLX:.c=.o}

SRCS = error_cleaning.c event_handling.c flood_fill.c free_assets.c free_map.c game_initialization.c coins_initialization.c image_initialization.c main.c map_check.c map_initialization.c render.c validation.c validate_elements.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Isrc -c $< -o $@

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

all: init-submodules $(NAME)

init-submodules:
	@if [ -z "$(shell ls -A $(MLX_PATH))" ]; then \
		git submodule init $(MLX_PATH); \
		git submodule update $(MLX_PATH); \
	fi

$(LIBMLXA):
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

makelibft:
	@if [ ! -f "$(LIBFTNAME)" ]; then \
		make -C $(LIBFTDIR) --no-print-directory; \
	fi

$(NAME): makelibft $(LIBMLXA) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_MLX) $(HEADERS) -L$(OBJDIR)/libft -lft

clean-empty-dirs:
	@if [ -d $(OBJDIR) ]; then find $(OBJDIR) -type d -empty -exec rmdir {} +; fi

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFTDIR) clean --no-print-directory
	@$(MAKE) clean-empty-dirs
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean --no-print-directory
	@$(MAKE) clean-empty-dirs

re: fclean all

.PHONY: all clean fclean norm re bonus
