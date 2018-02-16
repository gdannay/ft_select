/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 10:03:59 by gdannay           #+#    #+#             */
/*   Updated: 2018/02/16 12:39:27 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		init_term(t_term *term)
{
	struct termios	canon;

	if (!isatty(STDOUT_FILENO)
			|| !(term->name = getenv("TERM"))
			|| tgetent(NULL, term->name) == -1
			|| tcgetattr(STDOUT_FILENO, &canon) == -1
			|| tcgetattr(STDOUT_FILENO, &(term->origin)) == -1
			|| ioctl(STDOUT_FILENO, TIOCGWINSZ, &(term->size)) < 0)
		return (-1);
	canon.c_lflag &= ~(ECHO);
	canon.c_lflag &= ~(ICANON);
	canon.c_cc[VMIN] = 0;
	canon.c_cc[VTIME] = 0;
	if (tcsetattr(STDOUT_FILENO, TCSANOW, &canon) == -1)
		return (-1);
	ft_printf("\e[?25l");
	manage_signal(term);
	return (0);
}

int		default_term(t_term *term)
{
	char	*cd;

	cd = tgetstr("cd", NULL);
	tputs(cd, 1, &ft_putint);
	ft_printf("\e[?25h");
	if (tcsetattr(STDOUT_FILENO, TCSANOW, &(term->origin)) == -1)
		return (-1);
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
	term->arg[0].high = 1;
	term->nb = ac - 1;
	return (1);
}
