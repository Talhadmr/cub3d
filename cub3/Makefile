SRCS = gnl/get_next_line_utils.c gnl/get_next_line.c main.c init.c utils_game.c pix.c ray_cast.c utils_raycasting.c control.c act.c act1.c   	check/wall.c check/more_utils.c check/map.c check/check_input.c check/check_map.c check/utils.c check/walls.c

CC = gcc

MLX = mlx/libmlx.a

CFLAGS = -Wall -Wextra -Werror -g

NAME = cub3D

FRAMEWORK = -Lmlx -lmlx -framework OpenGL -framework AppKit

RM = rm -rf

all: $(NAME)

OBJS = $(SRCS:.c=.o)
$(NAME): $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(FRAMEWORK) -o $(NAME)

$(MLX):
	make -C mlx

clean:
	$(RM) $(OBJS)
	make clean -C mlx

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean re