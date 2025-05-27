NAME        = cub3D

# Library paths
LIBFT_PATH  = libs/libft
LIBFT_LIB   = $(LIBFT_PATH)/libft.a
MLX_PATH    = libs/minilibx-linux
MLX_LIB     = $(MLX_PATH)/libmlx.a
GNL_PATH    = libs/get_next_line

# Source files
SRCS = \
    src/main.c \
    src/helper_tools.c \
    src/parsing/parsing_utils_1.c \
    src/parsing/parsing_utils_2.c \
	src/parsing/parsing_utils_3.c \
    src/parsing/finalize_grid.c \
    src/parsing/validate_map.c \
	src/player/player_init.c \
	src/player/player_movement.c \
	src/hooks/exit_game_helpers.c \
	src/hooks/key_handler.c \
	src/hooks/key_press_helpers.c \
	src/hooks/loop_hook.c \
	src/data/data_init.c \
	src/data/data_parsing_color.c \
    src/render/render.c \
    src/render/render_init.c \
    src/render/render_init_utils_1.c \
	src/render/render_init_utils_2.c \
    src/render/render_ray_utils.c \
    src/render/render_tex_utils.c \
    $(GNL_PATH)/get_next_line.c \
    $(GNL_PATH)/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -O3 -g \
          -Iinc \
          -I$(GNL_PATH) \
          -I$(LIBFT_PATH) \
          -I$(MLX_PATH)
LDFLAGS = -L$(MLX_PATH) -lmlx \
          -L$(LIBFT_PATH) -lft \
          -lX11 -lXext -lm

# ---------------------------------------------------------------------------- #
#                                  RULES                                       #
# ---------------------------------------------------------------------------- #

all: $(LIBFT_LIB) $(MLX_LIB) $(NAME)

# Build libft silently, only the archive (no tests)
$(LIBFT_LIB):
	@$(MAKE) -s --no-print-directory -C $(LIBFT_PATH) libft.a

# Build MiniLibX (only the static lib, no tests)
$(MLX_LIB):
	@cd $(MLX_PATH) && ./configure > /dev/null 2>&1 || true
	@cd $(MLX_PATH) && \
	  $(MAKE) -s --no-print-directory -f makefile.gen libmlx.a > /dev/null 2>&1 || true



# Link final executable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Compile each .c to .o
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -rf $(MLX_PATH)/obj \
	        $(MLX_PATH)/libmlx.a \
	        $(MLX_PATH)/libmlx_Linux.a


fclean: clean
	@rm -f $(NAME) $(LIBFT_LIB)
	@$(MAKE) -s --no-print-directory -C $(LIBFT_PATH) fclean


# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
