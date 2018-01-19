/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 20:33:51 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/19 21:52:41 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	first_print(int ac, char **av)
{
	int	i;
	int	size;

	i = 1;
	size = (int)ft_strlen(av[1]);
	while (++i < ac)
	{
		if ((int)ft_strlen(av[i]) > size)
			size =(int)ft_strlen(av[i]);
	}
	size++;
	i = 0;
	while (++i < ac)
		ft_printf("%-*s", size, av[i]);
	ft_printf("\n");
}

int	ft_getch()
{
	int buf;

	buf = 0;
	if (read(0, &buf, 1) < 0)
		return (-1);
	return (buf);
}

void		display_args(struct winsize size, int size2)
{
	int		li;
	int 	co;
	int		key;
	struct winsize size;

	if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
		printf("TIOCGWINSZ error");
	(void)size2;
	while ((li = tgetnum("li") == *line)
			&& (co = tgetnum("col") == *col)
			&& (key = ft_getch()) != 32)
	{
	/*if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
		printf("TIOCGWINSZ error");
		printf("%d rows, %d columns\n", size.ws_row, size.ws_col);*/
		dprintf(1, "JAJA = %d %d %d %d\n", co, *col, li, *line);
	}
	*exit = 1;
}
