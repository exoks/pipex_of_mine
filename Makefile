# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 13:03:13 by oezzaou           #+#    #+#              #
#    Updated: 2022/11/24 22:04:38 by oezzaou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRC = pipex.c pipex_utils.c
CFLAGS = -Wall -Wextra -Werror
CC = gcc
HEADER = -I. -I libft
NAME = pipex

all: $(NAME)

$(NAME): $(SRC)
	make -C libft/
	$(CC) $(CFLAGS) $^ libft/libft.a $(HEADER) -o $@

clean: 
	make -C libft/ clean
	rm -rf $(NAME)

fclean: clean
	make -C libft/ fclean

re : fclean all

test:
	./$(NAME) "file1" "cat" "cat -e" "file2" && cat file2
.PHONEY: all clean fclean re
