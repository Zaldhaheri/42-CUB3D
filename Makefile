NAME = cub3d

SRC = main.c raycast.c raycast2.c main2.c srcs/content_check.c srcs/map.c srcs/texturing_check.c srcs/utils_2.c srcs/map_helpers.c srcs/texture_helpers.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3
MLX = srcs/MLX
LIBFT = srcs/LIBFT

LINK = -L$(MLX) -lmlx -framework OpenGL -framework AppKit -L$(LIBFT) -lft

COMPILE = $(CC) $(CFLAGS) $(LINK)

all: $(NAME)

$(NAME): $(OBJ) $(MLX)/libmlx.a $(LIBFT)/libft.a
	$(COMPILE) $(OBJ) -o $(NAME)

$(MLX)/libmlx.a:
	$(MAKE) -C $(MLX)

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(MLX) clean
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(MLX) fclean
	$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re