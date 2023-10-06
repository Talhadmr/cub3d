SRCS =	main.c gnl/get_next_line_utils.c gnl/get_next_line.c

OBJS = $(SRCS:.c=.o)

CC = gcc

FRAMEWORK = -framework OpenGL -framework AppKit

CFLAGS = -Wall -Wextra -Werror

NAME = cub3D

MLX = mlx/libmlx.a

RM = rm -rf

all: $(NAME)

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