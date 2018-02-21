/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 14:54:28 by gdannay           #+#    #+#             */
/*   Updated: 2018/02/21 19:58:39 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdio.h>
# include <term.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define UP 'A'
# define DOWN 'B'
# define RIGHT 'C'
# define LEFT 'D'
# define ECHAP 1
# define ENTER 10
# define ARROW 27
# define SPACE 32
# define DEL 127

typedef struct	s_arg
{
	char		*name;
	int			select;
	int			high;
	int			last;
}				t_arg;

typedef struct	s_term
{
	char			*name;
	t_arg			*arg;
	int				nb;
	int				elem;
	int				prec;
	int				line;
	struct winsize	size;
	struct termios	*origin;
	int				key;
}				t_term;

t_arg				*ft_select(t_term *term);
int					init_arg(int ac, char **av, t_term *term);
int					ft_getch();
void				manage_signal(t_term *term);
void				print_args(t_term *term);
int					ft_putint(int c);
void				highlight(t_arg *arg, int line, struct winsize size);
void				suspend(int signum);
int					init_term(t_term *term);
int					default_term(t_term *term);
void				free_term(t_term *term);
void				space(t_term *term);
void				del(t_term *term);
void				arrow(t_term *term);
void				get_precision(t_term *term);

#endif
