/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 17:37:40 by gdannay           #+#    #+#             */
/*   Updated: 2018/02/21 09:52:56 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_term	*cp_term;

void	cont(int signum)
{
	char	*cd;

	(void)signum;
	cd = tgetstr("cd", NULL);
	tputs(cd, 1, &ft_putint);
	init_term(cp_term);
	cp_term->line = print_args(cp_term->arg, cp_term->size);
	signal(SIGTSTP, &suspend);
}

void	free_all(t_term *term)
{
	int i;

	i = -1;
	while (term->arg[++i].name)
		ft_strdel(&(term->arg[i].name));
	free(term->arg);
	free(term);
}


void	quit(int signum)
{
	char	*cd;

	(void)signum;
	cd = tgetstr("cd", NULL);
	tputs(cd, 1, &ft_putint);
	default_term(cp_term);
	free_all(cp_term);
	exit(1);
}

void	suspend(int signum)
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
		else
			signal(i, &quit);
	}
}
