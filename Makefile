NAME = cub3d

SRC = main.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra
MLX = MLX

LINK = -lmlx -framework OpenGL -framework AppKit -L$(MLX)

COMPILE = $(CC) $(CFLAGS) $(LINK)

all : $(NAME)

$(NAME) : $(OBJ)
	$(COMPILE) $(OBJ) -o $(NAME)

$(MLX)/libmlx.a:
	$(MAKE) -C $(MLX)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

mlxmake :
	cd ./MLX && $(MAKE) all

mlxclean :
	cd ./MLX && $(MAKE) clean

mlxre :
	cd ./MLX && &(MAKE) re

.PHONY : all clean fclean re