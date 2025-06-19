NAME := pipex
CC := cc
CFLAGS := -Wall -Werror -Wextra

SRC := main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c get_path.c utile1.c utils.c action_childes.c
OBJ := $(SRC:.c=.o)

all : $(NAME)
bonus : $(NAME)

$(NAME) : $(OBJ)
	@$(MAKE) -C ft_printf
	@$(MAKE) -C libft
	$(CC) $(OBJ) $(CFLAGS) libft/libft.a ft_printf/libftprintf.a -o $(NAME)
	
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(MAKE) clean -C ft_printf
	@$(MAKE) clean -C libft
	@rm -f $(OBJ)

fclean : clean
	@$(MAKE) fclean -C ft_printf
	@$(MAKE) fclean -C libft
	@rm -f $(NAME)

re :fclean all

.PHONY : all clean fclean re