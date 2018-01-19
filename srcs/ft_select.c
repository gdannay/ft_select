/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:20:45 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/19 21:50:14 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		init_canon()
{
	struct termios	canon;

	if (tcgetattr(0, &canon) == -1)
		return (-1);
	canon.c_lflag &= ~(ECHO);
	canon.c_lflag &= ~(ICANON);
	canon.c_cc[VMIN] = 0;
	canon.c_cc[VTIME] = 1;
	if (tcsetattr(0, TCSANOW, &canon) == -1)
		return (-1);
	return (0);

}

static t_arg		*init_arg(int ac, char **av)
{
	t_arg	*arg;
	int		i;

	i = 0;
	if ((arg = (t_arg *)malloc(sizeof(t_arg) * ac)) == NULL)
		return (NULL);
	while (++i < ac)
	{
		arg[i - 1].name = ft_strdup(av[i]);
		arg[i - 1].select = 0;
		arg[i - 1].high = 0;
	}
	return (arg);
}

static t_arg		*ft_select(int ac, char **av, int biggest)
{
	struct winsize	size;
	struct winsize	size2;
	t_arg			*arg;
	int				i;
	int				c;

	exit = 0;
	i = 1;
	if ((arg = init_arg(ac, av)) == NULL)
		return (NULL);
	while (++i < ac)
		biggest = biggest < (int)ft_strlen(av[i]) ? (int)ft_strlen(av[i]) : biggest;
	while ((c = ft_getch() != 32))
	{
		if (ioctl(0,TIOCGWINSZ, &size2) < 0)
			return (NULL);
		display_args(size, biggest);
	}
	return (arg);

}

int				main(int ac, char **av)
{
	char			*name_term;
	struct termios	origin;
	t_arg			*arg;

	if ((name_term = getenv("TERM")) == NULL
			|| tgetent(NULL, name_term) == -1
			|| tcgetattr(0, &origin) == -1
			|| init_canon() == -1)
		return (-1);
	if (ac > 1)
	{
		if (!(arg = ft_select(ac, av, (int)ft_strlen(av[1]))))
			return (1);
	}
	return (0);
}
