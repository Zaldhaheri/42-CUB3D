# Compiler that will be used to compile
CC = cc
# Name of the library that will be created
NAME = libft.a
# These are the compiler flags that will be used
COMP_FLAGS = -Wall -Werror -Wextra

SRCS = ft_calloc.c ft_memset.c ft_memmove.c ft_isalnum.c ft_isdigit.c ft_isalpha.c \
		ft_isascii.c ft_isprint.c ft_memcpy.c ft_tolower.c ft_toupper.c \
		ft_strlen.c ft_atoi.c ft_bzero.c ft_strlcpy.c ft_strncmp.c ft_strchr.c \
		ft_memchr.c ft_strrchr.c ft_strlcat.c ft_memcmp.c ft_substr.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strdup.c \
		ft_strjoin.c ft_strtrim.c ft_striteri.c ft_strnstr.c ft_strmapi.c ft_itoa.c ft_split.c\

BON_SRC =  ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c\

OBJ = $(SRCS:.c=.o)

BON_OBJ = $(BON_SRC:.c=.o)

# Rule checks if the file exists in OBJ, then creates them if they dont exist
# $@ is the target in our case $(NAME)
$(NAME) : $(OBJ)
	ar -rcs $@ $(OBJ)

# Pattern rule that says how to create a .o file from a .c file.
# $? is the dependency list. (the .c files)
%.o: %.c
	$(CC) -c $(COMP_FLAGS) $?

re: fclean all

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(BON_OBJ)

bonus:	$(BON_OBJ)
	ar rcs $(NAME) $(BON_OBJ)

.PHONY:			all clean fclean re bonus