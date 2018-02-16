/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 20:33:51 by gdannay           #+#    #+#             */
/*   Updated: 2018/02/16 12:39:34 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		nb_args(t_arg *arg)
{
	int i;
	int nb;

	i = -1;
	nb = 0;
	while (arg[++i].name)
		nb++;
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
	int line;
	int tmp;
	int	elem;
	int prec;
	char			*up = tgetstr("up", NULL);
	char			*cr = tgetstr("cr", NULL);
	char			*so = tgetstr("so", NULL);
	char			*se = tgetstr("se", NULL);

	i = -1;
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
		if (line > size.ws_row - 2)
		{
			i -= 2;
			while (arg[++i].name)
				arg[i].last = 1;
			ft_printf("...");
			break ;
		}
		if (arg[i].high == 1 && prec < size.ws_col && arg[i].select == 1)
		{
			tputs(so, 1, &ft_putint);
			ft_printf("%s%-*s%s", tgetstr("us", NULL), prec, arg[i].name, tgetstr("ue", NULL));
			tputs(se, 1, &ft_putint);
		}
		else if (arg[i].high == 1 && arg[i].select == 1)
		{
			tputs(so, 1, &ft_putint);
			ft_printf("%s%-.*s%s", tgetstr("us", NULL), prec, arg[i].name, tgetstr("ue", NULL));
			tputs(se, 1, &ft_putint);
		}
		else if (arg[i].high == 1 && prec < size.ws_col)
			ft_printf("%s%-*s%s", tgetstr("us", NULL), prec, arg[i].name, tgetstr("ue", NULL));
		else if (arg[i].high == 1)
			ft_printf("%s%-.*s%s", tgetstr("us", NULL), prec, arg[i].name, tgetstr("ue", NULL));
		else if (prec < size.ws_col && arg[i].select == 1)
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
		arg[i].last = 0;
	}
	i = 0;
	while (++i < line)
		tputs(up, 1, &ft_putint);
	tputs(cr, 1, &ft_putint);
	line += elem * 10000;
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

int		manage_arrow(t_arg *arg, int nb, int elm)
{
	int c = 0;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg[i].name && arg[i].high == 0)
		i++;
	while (arg[j].name && arg[j].last == 0)
		j++;
	ft_getch();
	if ((c = ft_getch()) == UP)
	{
		if (i >= elm)
			arg[i - elm].high = 1;
		else if (arg[j].name == NULL && nb % elm == 0)
			arg[nb - elm + i].high = 1;
		else if (arg[j].name == NULL && nb % elm > i)
			arg[nb - nb % elm + i].high = 1;
		else if (arg[j].name)
			arg[j].high = 1;
		else
			arg[nb - 1].high = 1;
	}
	else if (c == DOWN)
	{
		if (arg[i + elm - 1].last == 0 && i < nb - elm)
			arg[i + elm].high = 1;
		else if (arg[j].name == NULL && nb % elm == 0)
			arg[i - nb + elm].high = 1;
		else
			arg[i % elm].high = 1;
	}
	else if (c == RIGHT)
	{
		if (arg[i + 1].name == NULL || arg[i].last == 1)
			arg[0].high = 1;
		else
			arg[i + 1].high = 1;
	}
	else if (c == LEFT)
	{
		if (i == 0 && arg[nb - 1].last == 0)
			arg[nb - 1].high = 1;
		else if (i == 0)
			arg[j].high = 1;
		else
			arg[i - 1].high = 1;
	}
	else
		c = 10;
	arg[i].high = 0;
	return (c);
}

int		display_args(t_term *term)
{
	struct winsize 	tmp;
	int				i;
	char			*cd = tgetstr("cd", NULL);
	int				j;
	int				elm;

	i = 0;
	j = 0;
	elm = 0;
	term->line = print_args(term->arg, term->size);
	if (ioctl(0, TIOCGWINSZ, (char *) &tmp) < 0)
		return (-1);
	while (term->size.ws_row == tmp.ws_row
			&& term->size.ws_col == tmp.ws_col
			&& (term->key = ft_getch()) != 32
			&& term->key != 27
			&& term->key != 10
			&& term->key != 127)
	{
		if (ioctl(0, TIOCGWINSZ, (char *) &tmp) < 0)
			return (-1);
	}
	if (term->key == 32)
	{
		while (term->arg[i].name && term->arg[i].high == 0)
			i++;
		if (term->arg[i].select == 0)
			term->arg[i].select = 1;
		else
			term->arg[i].select = 0;
		term->arg[i].high = 0;
		if (term->arg[i + 1].name == NULL)
			term->arg[0].high = 1;
		else
			term->arg[i + 1].high = 1;
	}
	if (term->key == 127)
	{
		while (term->arg[i].name && term->arg[i].high == 0)
			i++;
		if (term->arg[i + 1].name == NULL && i > 0)
			term->arg[i - 1].high = 1;
		else if (term->arg[i + 1].name == NULL)
			term->arg[0].high = 1;
		else
			term->arg[i + 1].high = 1;
		ft_strdel(&(term->arg[i].name));
		j = i;
		while (term->arg[++j].name)
			term->arg[j - 1] = term->arg[j];
		term->arg[j - 1] = term->arg[j];
	}
	if (term->key == 27)
	{
		elm = term->line / 10000;
		term->line = term->line % 10000;
		term->key = manage_arrow(term->arg, nb_args(term->arg), elm);
	}
	tputs(cd, 1, &ft_putint);
	term->size = tmp;
	return (1);
}
