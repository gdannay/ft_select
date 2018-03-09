/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:20:45 by gdannay           #+#    #+#             */
/*   Updated: 2018/03/09 11:53:02 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				ft_getch(void)
{
	int buf;

	buf = 0;
	if (read(0, &buf, 1) < 0)
		return (-1);
	return (buf);
}

int				ft_putint(int c)
{
	write(0, &c, 1);
	return (0);
}

static void		manage_keys(t_term *term)
{
	print_args(term);
	while (term->key != SPACE && term->key != ARROW
			&& term->key != ENTER && term->key != DEL)
		term->key = ft_getch();
	if (term->key == SPACE)
		space(term);
	else if (term->key == DEL)
		del(term);
	else if (term->key == ARROW)
		arrow(term);
}

static void		output(t_term *term)
{
	int i;
	int pre;

	i = -1;
	pre = 0;
	while (term->arg[++i].name)
	{
		if (!pre && term->arg[i].select)
		{
			write(STDOUT_FILENO, term->arg[i].name,
					ft_strlen(term->arg[i].name));
			pre = 1;
		}
		else if (pre && term->arg[i].select)
		{
			write(STDOUT_FILENO, " ", 1);
			write(STDOUT_FILENO, term->arg[i].name,
					ft_strlen(term->arg[i].name));
		}
	}
}

int				main(int ac, char **av)
{
	t_term		*term;

	if (ac > 1)
	{
		if (!(term = (t_term *)malloc(sizeof(t_term)))
				|| init_term(term) == -1
				|| !(init_arg(ac, av, term)))
			return (-1);
		while (term->key != ECHAP && term->key != ENTER)
			manage_keys(term);
		output(term);
		default_term(term);
		free_term(term);
	}
	return (0);
}
