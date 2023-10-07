SRCS =	main.c gnl/get_next_line_utils.c gnl/get_next_line.c


CC = gcc

MLX = mlx/libmlx.a

CFLAGS = -Wall -Wextra -Werror

NAME = cub3D

FRAMEWORK = -Lmlx -lmlx -framework OpenGL -framework AppKit #-fsanitize=address -g

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