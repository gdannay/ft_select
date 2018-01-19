/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 14:54:28 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/19 21:50:58 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT
# define FT_SELECT

#include <stdio.h>
#include <term.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <curses.h>
#include <sys/ioctl.h>
#include "../libft/libft.h"

# define SUB \033[4m
# define ENDSUB \033[0m

typedef struct	s_arg
{
	char		*name;
	int			select;
	int			high;
}				t_arg;

void			display_args(struct winsize size, int biggest);
int				ft_getch();
void			print_first(int ac, char **av, struct winsize size);

#endif
