# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/23 21:29:48 by fde-jesu          #+#    #+#              #
#    Updated: 2024/05/24 23:49:16 by fde-jesu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER = libft.h
CFLAGS = -Wall -Werror -Wextra

FUN = $(wildcard *.c)
RED:=\033[0;31m
default_colour=\033[0m
OBJ = ${FUN:.c=.o}

all: $(NAME)

$(NAME):
	    cc ${CFLAGS} -c ${HEADER} ${FUN}
		ar rc ${NAME} ${OBJ}
		@echo "${RED}RETIRAR WILDCARD NO LIBFT${default_colour}\n"
clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)
      
re: fclean all

.PHONY: all clean fclean re
.SILENT: