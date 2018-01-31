/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 20:33:51 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/31 17:58:45 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		nb_args(t_arg *arg, int booldel)
{
	int i;
	int nb;

	i = -1;
	nb = 0;
	while (arg[++i].name)
	{
		if (booldel || arg[i].del == 0)
			nb++;
	}
	return (nb);
}

int		get_precision(t_arg *arg)
{
	int 			i;
	int 			prec;

	i = -1;
	prec = 0;
	while (arg[++i].name)
		prec = prec < (int)ft_strlen(arg[i].name) ? (int)ft_strlen(arg[i].name) : prec;
	prec++;
	return (prec);

}

int		print_args(t_arg *arg, struct winsize size)
{
	int	i;
	int	nb;
	int line;
	int tmp;
	int	elem;
	int prec;
	char			*sc = tgetstr("sc", NULL);
	char			*up = tgetstr("up", NULL);
	char			*cr = tgetstr("cr", NULL);
	char			*so = tgetstr("so", NULL);
	char			*se = tgetstr("se", NULL);

	i = -1;
	nb = nb_args(arg, 1);
	line = 1;
	i = -1;
	prec = get_precision(arg);
	tmp = (size.ws_col - 10) / prec;
	elem = tmp;
	while (arg[++i].name)
	{
		if (i + 1 > tmp && i != 0)
		{
			ft_printf("\n");
			tmp += elem;
			line++;
		}
		if (prec < size.ws_col && arg[i].select == 1)
		{
			tputs(so, 1, &ft_putint);
			ft_printf("%-*s", prec, arg[i].name);
			tputs(se, 1, &ft_putint);
		}
		else if (arg[i].select == 1)
		{
			tputs(so, 1, &ft_putint);
			ft_printf("%-.*s", size.ws_col, arg[i].name);
			tputs(se, 1, &ft_putint);
		}
		else if (prec < size.ws_col)
			ft_printf("%-*s", prec, arg[i].name);
		else
			ft_printf("%-.*s", size.ws_col, arg[i].name);
		if (line > size.ws_row - 2)
		{
			ft_printf("\n...");
			line++;
			break ;
		}
	}
	i = 0;
	while (++i < line)
		tputs(up, 1, &ft_putint);
	tputs(cr, 1, &ft_putint);
	tputs(sc, 1, &ft_putint);
	return (line);
}

int	ft_getch()
{
	int buf;

	buf = 0;
	if (read(0, &buf, 1) < 0)
		return (-1);
	return (buf);
}

int		ft_putint(int c)
{
	write(1, &c, 1);
	return (0);
}

void	highlight(t_arg *arg, int line, struct winsize size)
{
	int		i;
	int		prec;
	char	*rc;
	char	*dow;
	char	*nd;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (nb_args(arg, 1) % line == 0)
		line++;
	prec = get_precision(arg);
	rc = tgetstr("rc", NULL);
	dow = tgetstr("dow", NULL);
	nd = tgetstr("nd", NULL);
	while (arg[i].name && arg[i].high == 0)
		i++;
	while (i + 1 > (++j * (nb_args(arg, 1) / line + 1)))
		tputs(dow, 1, &ft_putint);
	while ((j - 1) * (nb_args(arg, 1) / line + 1) + k < i)
	{
		k++;
	//	dprintf(1, "ICI %d %d %d\n", j, k, i)
	}
	k *= get_precision(arg);
	while (--k >= 0)
		tputs(nd, 1, &ft_putint);
	if (prec < size.ws_col)
		ft_printf("%s%-*s%s", tgetstr("us", NULL), prec, arg[i].name, tgetstr("ue", NULL));
	else
		ft_printf("%s%-.*s%s", tgetstr("us", NULL), prec, arg[i].name, tgetstr("ue", NULL));
	tputs(rc, 1, &ft_putint);
}

t_arg	*manage_arrow(t_arg *arg, int line)
{
	int c = 0;
	int	i;

	i = 0;
	if (nb_args(arg, 1) % line == 0)
		line++;
	while (arg[i].name && arg[i].high == 0)
		i++;
	arg[i].high = 0;
	ft_getch();
	if ((c = ft_getch()) == 'A')
	{
		if (i > nb_args(arg, 1) / line)
			arg[i - nb_args(arg, 1) / line - 1].high = 1;
		else if (nb_args(arg, 1) % (nb_args(arg, 1) / line + 1) == 0)
			arg[nb_args(arg, 1) - nb_args(arg, 1) / line - 1 + i].high = 1;
		else if (nb_args(arg, 1) % (nb_args(arg, 1) / line + 1) > i)
			arg[nb_args(arg, 1) - nb_args(arg, 1) % (nb_args(arg, 1) / line + 1) + i].high = 1;
		else
			arg[nb_args(arg, 1) - 1].high = 1;
	}
	else if (c == 'B')
	{
		if (i < nb_args(arg, 1) - (nb_args(arg, 1) / line + 1))
			arg[i + nb_args(arg, 1) / line + 1].high = 1;
		else if (nb_args(arg, 1) % (nb_args(arg, 1) / line + 1) == 0)
			arg[i - nb_args(arg, 1) + nb_args(arg, 1) / line + 1].high = 1;
		else
			arg[i % (nb_args(arg, 1) / line + 1)].high = 1;
	}
	else if (c == 'C')
	{
		if (arg[i + 1].name == NULL)
			arg[0].high = 1;
		else
			arg[i + 1].high = 1;
	}
	else if (c == 'D')
	{
		if (i == 0)
			arg[nb_args(arg, 1) - 1].high = 1;
		else
			arg[i - 1].high = 1;
	}
	return (arg);
}

struct winsize	display_args(struct winsize size, int *key, t_arg *arg, int *line)
{
	struct winsize 	tmp;
	int				i;
	char			*cd = tgetstr("cd", NULL);
	char			*rc = tgetstr("rc", NULL);

	i = 0;
	if (ioctl(0, TIOCGWINSZ, (char *) &tmp) < 0)
		return size;
	while (size.ws_row == tmp.ws_row
			&& size.ws_col == tmp.ws_col
			&& (*key = ft_getch()) != 32
			&& *key != 27)
	{
		if (ioctl(0, TIOCGWINSZ, (char *) &tmp) < 0)
			return (size);
	}
	if (*key == 27)
		manage_arrow(arg, *line);
	tputs(rc, 1, &ft_putint);
	tputs(cd, 1, &ft_putint);
	*line = print_args(arg, tmp);
	highlight(arg, *line, tmp);
	return (tmp);
}
