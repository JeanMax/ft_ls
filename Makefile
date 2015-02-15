#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <zboub@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/15 19:01:48 by mcanal            #+#    #+#              #
#    Updated: 2015/02/15 19:02:41 by mcanal           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ls

C_SRC =	ft_ls.c			sort.c		print.c			convert.c	\
		check_arg.c		read.c		libft/libft.a	space.c		\
		greatest.c		flagn.c		calc.c	
O_DIR = obj
VPATH = src
SRCC =  $(C_SRC:%.c=src/%.c)
SRCO =  $(C_SRC:%.c=$(O_DIR)/%.o)
LIB =   libft/libft.a
INC =   inc/header.h
CC =    gcc
RM =    rm -f
CFLAGS =  -Wall -Wextra -Werror -I./inc/

.PHONY: all lib soft debug optimize clean fclean zclean re

all:
	@make -C libft
	@$(MAKE) $(NAME)

$(NAME): $(SRCO) $(LIB) $(INC)
	@$(CC) $(CFLAGS) $(SRCO) $(LIB) -o $@

$(O_DIR)/%.o: %.c
	@$(RM) $(NAME)
	@$(CC) $(CFLAGS) -c $^ -o $@

soft:
	@$(RM) $(NAME)
	@$(CC) $(SRCC) $(LIB) -o $(NAME)
	@./$(NAME)

debug: re
	@$(CC) $(CFLAGS) -ggdb $(SRCO) $(LIB) -o $(NAME)
	@gdb $(NAME)

optimize: re
	@$(CC) $(CFLAGS) -O2 $(SRCO) $(LIB) -o $(NAME)

clean:
	@$(RM) $(SRCO)

fclean: clean
	@$(RM) $(NAME)

zclean: fclean
	@make -C libft fclean

re: fclean all
