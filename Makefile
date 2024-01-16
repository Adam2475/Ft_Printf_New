CC = cc
CFLAGS = -Wall -Wextra -Werror -c -I
RM = rm -f
NAME = libftprintf.a

SRC = ./ft_printf.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re