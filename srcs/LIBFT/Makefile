# Compiler that will be used to compile
CC = cc
# Name of the library that will be created
NAME = libft.a
# These are the compiler flags that will be used
COMP_FLAGS = -Wall -Werror -Wextra

SRCS = ft_split.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_strrchr.c get_next_line.c ft_substr.c ft_strdup.c ft_strchr.c ft_strtrim.c ft_itoa.c\

OBJ = $(SRCS:.c=.o)

# Rule checks if the file exists in OBJ, then creates them if they dont exist
# $@ is the target in our case $(NAME)
$(NAME) : $(OBJ)
	@ar -rcs $@ $(OBJ)

# Pattern rule that says how to create a .o file from a .c file.
# $? is the dependency list. (the .c files)
%.o: %.c
	@$(CC) -c $(COMP_FLAGS) $?

re: fclean all

all: $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

.PHONY:			all clean fclean re