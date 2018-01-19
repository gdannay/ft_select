# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdannay <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 18:54:36 by gdannay           #+#    #+#              #
#    Updated: 2018/01/17 10:50:42 by gdannay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=		libft.a

SRCS	=		ft_memset.c			\
				ft_bzero.c			\
				ft_memcpy.c			\
				ft_memccpy.c		\
				ft_memmove.c		\
				ft_atoi.c			\
				ft_isalnum.c		\
				ft_isalpha.c		\
				ft_isascii.c		\
				ft_isdigit.c		\
				ft_isprint.c		\
				ft_memalloc.c		\
				ft_memchr.c			\
				ft_memcmp.c			\
				ft_memdel.c			\
				ft_strcat.c			\
				ft_strlcat.c		\
				ft_strchr.c			\
				ft_strcmp.c			\
				ft_strcpy.c			\
				ft_strdup.c			\
				ft_wstrdup.c		\
				ft_strlen.c			\
				ft_strncat.c		\
				ft_strncmp.c		\
				ft_strncpy.c		\
				ft_strnew.c			\
				ft_strnstr.c		\
				ft_strrchr.c		\
				ft_strstr.c			\
				ft_tolower.c		\
				ft_toupper.c		\
				ft_strdel.c			\
				ft_strclr.c			\
				ft_striter.c		\
				ft_striteri.c		\
				ft_strmap.c			\
				ft_strmapi.c		\
				ft_strequ.c			\
				ft_strjoin.c		\
				ft_strnequ.c		\
				ft_strsplit.c		\
				ft_strsub.c			\
				ft_strtrim.c		\
				ft_itoa.c			\
				ft_strsub.c			\
				ft_putchar.c		\
				ft_putstr.c			\
				ft_putendl.c		\
				ft_putnbr.c			\
				ft_putchar_fd.c		\
				ft_putstr_fd.c		\
				ft_putendl_fd.c		\
				ft_putnbr_fd.c		\
				ft_lstnew.c			\
				ft_lstdelone.c		\
				ft_lstdel.c			\
				ft_lstappend.c		\
				ft_lstadd.c			\
				ft_lstiter.c		\
				ft_lstmap.c			\
				ft_puttab.c			\
				ft_lstsize.c		\
				ft_capitalize.c		\
				ft_lowercase.c		\
				ft_strndup.c		\
				ft_bchar.c			\
				ft_chartostr.c		\
				ft_lennbr.c			\
				ft_atoi_base.c		\
				ft_wstrlen.c		\
				ft_printf.c			\
				ft_printflib.c		\
				manage_flag.c		\
				check_wp.c			\
				manage_buff.c		\
				display.c			\
				ltoa_base.c			\
				display_type.c		\
				display_flag.c		\
				display_wps.c		\
				display_uni.c		\
				display_wstr.c		\
				ft_joinpath.c		\
				ft_tabdup.c			\
				get_next_line.c		\
				ft_joinwchar.c		\
				ft_strsplitspace.c	\
				ft_tabjoin.c		\
				ft_tablen.c			\
				ft_strjoinwq.c		\
				ft_strlenwq.c		\
				ft_strdupwq.c		\
				ft_strndupwq.c		\
				ft_atol.c			\
				ft_tabdel.c

CC		=		gcc

OBJS	=		$(SRCS:.c=.o)

CFLAGS	=		-Wall -Wextra -Werror -I./

all		:		$(NAME)

$(NAME)	:		$(OBJS)
				ar rc $(NAME) $(OBJS)
				ranlib $(NAME)

clean	:
				rm -rf $(OBJS)

fclean	:		clean
				rm -rf $(NAME)

re		:		fclean all
