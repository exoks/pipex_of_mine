# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 15:57:20 by oezzaou           #+#    #+#              #
#    Updated: 2022/10/03 11:57:53 by oezzaou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME := libft.a
SRCM := $(wildcard ft_[!l]*.c)
SRCB := $(wildcard *.c)
OBJM := ${SRCM:.c=.o}
OBJB := ${SRCB:.c=.o}
CFLAGS := -Wall -Wextra -Werror
HEADER := libft.h
CC := cc
GREEN := \033[1;32m
RED := \033[1;31m
CYAN := \033[1;36m
NOCLR := \033[1;0m

$(NAME): $(OBJM)
	@ar -r $@ $^
	@echo "$(GREEN)LIBFT CREATED ✔️"


all: $(NAME)

bonus: $(OBJB)
	@ar -r $(NAME) $^
	@echo "$(GREEN)DONE ✔️"

%.o: %.c
	@echo "$(NOCLR)COMPILING: $(CYAN)$<" 
	@$(CC) $(CFLAGS) -c $< -I $(HEADER)

clean:
	@echo "$(RED)CLEANING..."
	@rm -f *.o
	@echo "$(GREEN)DONE ✔️"

fclean: clean
	@rm -f $(NAME)

re: fclean all
	@echo "$(GREEN)DONE ✔️"

.PHONY : all bonus clean fclean re
