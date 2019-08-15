NAME = ft_ls
SRC = ./ft_ls.c ./get_one_file.c ./ft_sort.c ./get_flag_tab.c ./print_list.c ./ft_l_flag.c ./ft_blocks.c ./ft_files_dirs.c ./print_all.c ./ft_recursive_flag.c ./ft_sort_helper.c ./free.c ./ft_l_flag2.c ./ft_l_flag3.c ./ft_color.c ./ft_putstr_error.c
HEADER = ./ft_ls.h
OBJECTS = ./*.o
LIBFT_PATH = ./libft/

all : $(NAME)

$(NAME) :
	$(MAKE) -C ./libft
	gcc -Wall -Wextra -Werror -I=$(HEADR)  $(SRC) -L $(LIBFT_PATH) -lft -o $(NAME)
	
clean :
	/bin/rm -f $(OBJECTS)
	$(MAKE) -C ./libft/ clean

fclean : clean
	/bin/rm -f $(NAME)
	$(MAKE) -C ./libft/ fclean

re : fclean all