# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdannay <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/19 18:14:52 by gdannay           #+#    #+#              #
#    Updated: 2018/03/21 20:00:33 by gdannay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_select

SRCS	=	srcs/ft_select.c		\
			srcs/display.c			\
			srcs/signal.c			\
			srcs/term.c				\
			srcs/keys.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Werror -Wextra -I includes

LFLAGS	=	-L libft -lft -ltermcap

CC		=	gcc

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			make -C libft
			$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

%.o		:	%.c
			$(CC) -o $@ -c $< $(CFLAGS)

clean	:
			make clean -C libft
			rm -rf $(OBJS)

fclean	:
			make fclean -C libft
			rm -rf $(OBJS)
			rm -rf $(NAME)

re		:	fclean all
