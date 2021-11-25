# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tuytters <tuytters@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/12 10:43:01 by tuytters          #+#    #+#              #
#    Updated: 2021/10/18 11:40:54 by tuytters         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

SRCS		=	philo.c			\
				srcs/convert.c	\
				srcs/error.c	\
				srcs/free.c		\
				srcs/utils.c

OBJS		=	$(SRCS:%.c=%.o)

.c.o:
				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus:			all

RM			=	rm -rf

clean	:
				@$(RM) $(OBJS)

fclean	:		clean
				@$(RM) $(NAME)

re		:		fclean all
.PHONY	:		all clean fclean re	test bonus
