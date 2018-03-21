/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 10:03:59 by gdannay           #+#    #+#             */
/*   Updated: 2018/03/21 20:03:45 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	get_precision(t_term *term)
{
	int i;

	i = -1;
	term->prec = 0;
	while (term->arg[++i].name)
		term->prec = term->prec < (int)ft_strlen(term->arg[i].name)
			? (int)ft_strlen(term->arg[i].name) : term->prec;
	term->prec = term->prec + 1;
}

int		init_term(t_term *term)
{
	struct termios	canon;

	if (!(term->name = getenv("TERM"))
		|| tgetent(NULL, term->name) == -1
		|| tcgetattr(0, &canon) == -1
		|| !(term->origin = (struct termios *)malloc(sizeof(struct termios)))
		|| tcgetattr(0, term->origin) == -1
		|| ioctl(0, TIOCGWINSZ, &(term->size)) < 0)
		return (-1);
	canon.c_lflag &= ~(ECHO);
	canon.c_lflag &= ~(ICANON);
	canon.c_cc[VMIN] = 0;
	canon.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &canon) == -1)
		return (-1);
	manage_signal(term);
	term->key = 0;
	ft_printf("\e[?25l");
	return (0);
}

int		default_term(t_term *term)
{
	char	*cd;

	cd = tgetstr("cd", NULL);
	tputs(cd, 2, &ft_putint);
	ft_printf("\e[?25h");
	if (tcsetattr(0, TCSANOW, term->origin) == -1)
		return (-1);
	free(term->origin);
	return (0);
}

int		init_arg(int ac, char **av, t_term *term)
{
	int		i;

	i = 0;
	if ((term->arg = (t_arg *)malloc(sizeof(t_arg) * ac)) == NULL)
		return (0);
	while (++i < ac)
	{
		term->arg[i - 1].name = ft_strdup(av[i]);
		term->arg[i - 1].select = 0;
		term->arg[i - 1].high = 0;
		term->arg[i - 1].last = 0;
	}
	term->arg[i - 1].name = NULL;
	term->arg[i - 1].last = 1;
	term->arg[0].high = 1;
	term->nb = ac - 1;
	return (1);
}

void	free_term(t_term *term)
{
	int i;

	i = -1;
	while (term->arg[++i].name)
		ft_strdel(&(term->arg[i].name));
	free(term->arg);
	free(term);
}
