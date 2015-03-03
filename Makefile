#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <zboub@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/15 19:01:48 by mcanal            #+#    #+#              #
#    Updated: 2015/03/03 12:50:57 by mcanal           ###   ########.fr        #
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

.PHONY: all lib soft clean fclean zclean re brute

all:
	@make -C libft
	@$(MAKE) $(NAME)

$(NAME): $(SRCO) $(LIB) $(INC)
	$(CC) $(CFLAGS) $(SRCO) $(LIB) -o $@

$(O_DIR)/%.o: %.c
	@$(RM) $(NAME)
	$(CC) $(CFLAGS) -c $^ -o $@

soft:
	@$(RM) $(NAME)
	@$(CC) -I./inc/ $(SRCC) $(LIB) -o $(NAME)
	@./$(NAME)

clean:
	@$(RM) $(SRCO)

fclean: clean
	@$(RM) $(NAME)

zclean: fclean
	@make -C libft fclean

re: fclean all

brute: zclean all
