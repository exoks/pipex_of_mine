# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 13:03:13 by oezzaou           #+#    #+#              #
#    Updated: 2022/11/27 22:01:49 by oezzaou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRC = pipex.c pipex_utils.c
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
	./$(NAME) "file1" "ls -l" "wc" "file2" && cat file2
.PHONEY: all clean fclean re
