NAME = libft.a
SRC = ./ft_char.c ./ft_strdup.c ./ft_strcmp.c ./ft_putstr.c ./ft_putchar.c ./ft_strsub.c ./ft_putnbr.c ./ft_strjoin.c ./ft_strlen.c
HEADER = libft.h
OBJECTS = ./*.o

all : $(NAME)

$(NAME) :
	gcc -Wall -Wextra -Werror -I=./$(HEADR) -c $(SRC)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

clean :
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
