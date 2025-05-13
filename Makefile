NAME = cub3D

SRC_DIR	= ./src
SRCS = $(SRC_DIR)/main.c														\
	$(SRC_DIR)/render/render.c	$(SRC_DIR)/render/render_init.c					\
	$(SRC_DIR)/render/render_init_utils.c	$(SRC_DIR)/render/render_ray_utils.c\
	$(SRC_DIR)/render/render_tex_utils.c
INC_DIR	= ./inc
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -g -I$(INC_DIR) -I/usr/include -I$(MLX_PATH) -fsanitize=address,undefined

MLX_PATH = libs/minilibx-linux
MLX_LIB = $(MLX_PATH)/libmlx.a

all: $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_PATH)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(MLX_PATH) -lmlx -lX11 -lXext -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(MLX_PATH) clean

re: fclean all

.PHONY: all clean fclean re

