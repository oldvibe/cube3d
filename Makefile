NAME = cube3d
MLX = -L./minilibx-linux/ -lmlx -lXext -lX11 -lm

SRC = src/main.c \
      src/garbage_collecter.c \
      src/init.c \
      src/render.c \
      maps/map_example.c \
      src/get_next_line.c \
      src/get_next_line_utils.c

CC = cc

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

HEADER = cube3d.h

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX) -o $(NAME)

clean: 
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
.PHONY: all re clean fclean