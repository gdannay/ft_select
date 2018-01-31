/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 14:54:28 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/31 14:03:59 by gdannay          ###   ########.fr       */
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

# define UP 1
# define DOWN 2
# define RIGHT 3
# define LEFT 4

typedef struct	s_arg
{
	char		*name;
	int			select;
	int			high;
	int			del;
}				t_arg;

struct winsize	display_args(struct winsize size, int *key, t_arg *arg, int *line);
int				ft_getch();
void			print_first(int ac, char **av, struct winsize size);
int				print_args(t_arg *arg, struct winsize size);
int				ft_putint(int c);
int				nb_args(t_arg *arg, int booldel);
int				get_precision(t_arg *arg);
void			highlight(t_arg *arg, int line, struct winsize size);

#endif
