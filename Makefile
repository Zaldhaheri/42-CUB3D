NAME = cub3D

SRCS = \
	$(SRCDIR)/main.c \
	$(SRCDIR)/game.c \
	$(SRCDIR)/hooks.c \
	$(SRCDIR)/hooks_move.c \
	$(SRCDIR)/raycast.c \
	$(SRCDIR)/raycast2.c \
	$(SRCDIR)/content_check.c \
	$(SRCDIR)/map.c \
	$(SRCDIR)/parse.c \
	$(SRCDIR)/texturing_check.c \
	$(SRCDIR)/utils_2.c \
	$(SRCDIR)/map_helpers.c \
	$(SRCDIR)/texture_helpers.c \
		#$(SRCDIR)/free_all.c

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3

OS:= ${shell uname}
ifeq (${OS},Darwin)
	MLXDIR = srcs/MLX
	MLXFLG = -framework OpenGL -framework Appkit
	CFLAGS += -D OSX
else
	MLXDIR = srcs/mlx-linux
	MLXFLG = -lXext -lX11
	CFLAGS += -D LINUX
 endif

SRCDIR = srcs

OBJDIR = objs

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

LIB = srcs/LIBFT/libft.a

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(MLXDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

# $(NAME): $(OBJDIR) $(OBJS)
# 	make -C srcs/LIBFT
# 	make -C $(MLXDIR)
# 	$(CC) $(OBJS) $(CFLAGS) -L$(MLXDIR) -lmlx -lm -march=native $(MLXFLG) -o $(NAME) $(LIB)

$(NAME): $(OBJDIR) $(OBJS)
	make -C srcs/LIBFT
	$(CC) $(OBJS) $(CFLAGS) -L$(MLXDIR) -lm -march=native -o $(NAME) $(LIB)


norm: 
	@python3 -m norminette

clean:
	rm -rf $(OBJS) $(OBJDIR)
	make clean -C srcs/LIBFT
	make clean -C $(MLXDIR)

fclean: clean
	rm -f $(NAME)
	rm -f srcs/LIBFT/libft.a

re: fclean all
# OBJ = $(SRC:.c=.o)

# CC = cc

# CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3
# MLX = srcs/MLX
# LIBFT = srcs/LIBFT

# LINK = -L$(MLX) -lmlx -framework OpenGL -framework AppKit -L$(LIBFT) -lft

# COMPILE = $(CC) $(CFLAGS) $(LINK)

# all: $(NAME)

# $(NAME): $(OBJ) $(MLX)/libmlx.a $(LIBFT)/libft.a
# 	$(COMPILE) $(OBJ) -o $(NAME)

# $(MLX)/libmlx.a:
# 	$(MAKE) -C $(MLX)

# $(LIBFT)/libft.a:
# 	$(MAKE) -C $(LIBFT)

# clean:
# 	rm -f $(OBJ)
# 	$(MAKE) -C $(MLX) clean
# 	$(MAKE) -C $(LIBFT) clean

# fclean: clean
# 	rm -f $(NAME)
# 	$(MAKE) -C $(MLX) fclean
# 	$(MAKE) -C $(LIBFT) fclean

# re: fclean all

# .PHONY: all clean fclean re