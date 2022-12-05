# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 13:03:13 by oezzaou           #+#    #+#              #
#    Updated: 2022/12/05 16:30:30 by oezzaou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRC = pipex.c pipex_utils.c pipex_here_doc.c
CFLAGS = -Wall -Wextra -Werror
CC = gcc
HEADER = -Ipipex.h -Ift_printf/include/ -Ift_printf/libft
NAME = pipex

all: $(NAME)

$(NAME): $(SRC)
	make -C ft_printf/
	$(CC) $(CFLAGS) $^ ft_printf/libftprintf.a $(HEADER) -o $@

clean: 
	make -C ft_printf/ clean
	rm -rf $(NAME)

fclean: clean
	make -C ft_printf/ fclean

re : fclean all

bonus: fclean all

test:
	./$(NAME) "file1" "./hello world.sh" "cat -e" "file2" && cat file2
.PHONEY: all clean fclean re test
