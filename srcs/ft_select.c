/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:20:45 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/31 14:44:59 by gdannay          ###   ########.fr       */
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
	canon.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &canon) == -1)
		return (-1);
	return (0);

}

static t_arg		*init_arg(int ac, char **av)
{
	t_arg	*arg;
	int		i;
	int		j;
	int		slash;

	i = 0;
	if ((arg = (t_arg *)malloc(sizeof(t_arg) * ac)) == NULL)
		return (NULL);
	while (++i < ac)
	{
		j = -1;
		slash = 0;
		while (av[i][++j])
		{
			if (av[i][j] == '/')
				slash = j;
		}
		//		arg[i - 1].name = ft_strsub(av[i], slash + 1,
		//				ft_strlen(av[i]) - slash - 1);
		arg[i - 1].name = ft_strdup(av[i]);
		arg[i - 1].select = 0;
		arg[i - 1].high = 0;
		arg[i - 1].del = 0;
	}
	arg[i - 1].name = NULL;
	arg[0].high = 1;
//	dprintf(1, "ICI = %s", arg[50].name);
	return (arg);
}

static t_arg		*ft_select(int ac, char **av)
{
	struct winsize	size;
	t_arg			*arg;
	int				c;
	int				line;

	c = 0;
	if ((arg = init_arg(ac, av)) == NULL)
		return (NULL);
	if (ioctl(0,TIOCGWINSZ, &size) < 0)
		return (NULL);
	line = print_args(arg, size);
	highlight(arg, line, size);
	while (c != 32 && (c = ft_getch() != 32))
		size = display_args(size, &c, arg, &line);
	return (arg);

}

int				main(int ac, char **av)
{
	char			*name_term;
	struct termios	origin;
	t_arg			*arg;
	char			*rc;

	if ((name_term = getenv("TERM")) == NULL
			|| tgetent(NULL, name_term) == -1
			|| tcgetattr(0, &origin) == -1
			|| init_canon() == -1)
		return (-1);
	if (ac > 1)
	{
//		ft_printf("\e[?25l");
		if (!(arg = ft_select(ac, av)))
			return (1);
		rc = tgetstr("rc", NULL);
		tputs(rc, 1, &ft_putint);
	}
//	ft_printf("\e[?25h");
	return (0);
}
