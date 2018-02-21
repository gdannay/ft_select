/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 17:37:40 by gdannay           #+#    #+#             */
/*   Updated: 2018/02/21 11:27:49 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_term	*cp_term;

static void		cont(int signum)
{
	char	*cd;

	(void)signum;
	cd = tgetstr("cd", NULL);
	tputs(cd, 1, &ft_putint);
	init_term(cp_term);
	print_args(cp_term);
	signal(SIGTSTP, &suspend);
}

static void		quit(int signum)
{
	char	*cd;

	(void)signum;
	cd = tgetstr("cd", NULL);
	tputs(cd, 1, &ft_putint);
	default_term(cp_term);
	free_term(cp_term);
	exit(1);
}

void			suspend(int signum)
{
	char	*cd;

	(void)signum;
	cd = tgetstr("cd", NULL);
	tputs(cd, 1, &ft_putint);
	default_term(cp_term);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\032");
	signal(SIGCONT, &cont);
}

static void		winchange(int signum)
{
	(void)signum;

	if (!isatty(STDOUT_FILENO)
		|| ioctl(0, TIOCGWINSZ, &(cp_term->size)) == -1)
		return ;
	print_args(cp_term);
}

void			manage_signal(t_term *term)
{
	int i;

	cp_term = term;
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
