# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abonnel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 15:46:15 by abonnel           #+#    #+#              #
#    Updated: 2021/03/24 12:29:11 by abonnel          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


SRCS	= ft_strcmp.s ft_read.s ft_write.s ft_strlen.s ft_strcpy.s ft_strdup.s

OBJS	= $(SRCS:.s=.o)

NAME	= libasm.a

CC		= nasm

RM		= rm -rf

CFLAGS	= -fmacho64

.s.o:
			$(CC) $(CFLAGS) -s $< -o $(<:.s=.o)

all:		$(NAME)
			gcc -Wall -Wextra -Werror main.c libasm.a

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME) a.out

re:			fclean all

.PHONY:		all clean fclean re
