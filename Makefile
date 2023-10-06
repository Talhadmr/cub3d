CC = gcc

NAME = cub


CFLAGS = -Wall -Wextra -Werror  



SRC = gnl/get_next_line.c \
    gnl/get_next_line_utils.c \
	main.c

OBJS := $(SRC:.c=.o)

%.o: %.c
	$(CC)  -Werror -Imlx -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	make -C mlx
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -rf *.o

fclean: clean
	rm -f ${OBJS} $(NAME)

re: fclean ${NAME}