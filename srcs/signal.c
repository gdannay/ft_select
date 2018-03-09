/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 17:37:40 by gdannay           #+#    #+#             */
/*   Updated: 2018/03/09 12:02:18 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_term	*g_cp_term;

static void		cont(int signum)
{
	char	*cd;

	(void)signum;
	cd = tgetstr("cd", NULL);
	tputs(cd, 1, &ft_putint);
	init_term(g_cp_term);
	print_args(g_cp_term);
	signal(SIGTSTP, &suspend);
}

static void		quit(int signum)
{
	char	*cd;

	(void)signum;
	cd = tgetstr("cd", NULL);
	tputs(cd, 1, &ft_putint);
	default_term(g_cp_term);
	free_term(g_cp_term);
	exit(1);
}

void			suspend(int signum)
{
	char	*cd;

	(void)signum;
	cd = tgetstr("cd", NULL);
	tputs(cd, 2, &ft_putint);
	if (default_term(g_cp_term) == -1)
		return ;
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\032");
	signal(SIGCONT, &cont);
}

static void		winchange(int signum)
{
	(void)signum;
	if (!isatty(STDOUT_FILENO)
		|| ioctl(0, TIOCGWINSZ, &(g_cp_term->size)) == -1)
		return ;
	print_args(g_cp_term);
}

void			manage_signal(t_term *term)
{
	int i;

	g_cp_term = term;
	i = -1;
	while (++i < 32)
	{
		if (i == SIGTSTP)
			signal(SIGTSTP, &suspend);
		else if (i == SIGCONT)
			signal(SIGCONT, &cont);
		else if (i == SIGWINCH)
			signal(SIGWINCH, &winchange);
		else
			signal(i, &quit);
	}
}
