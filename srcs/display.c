/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 11:56:11 by gdannay           #+#    #+#             */
/*   Updated: 2018/03/21 19:10:19 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	display_highlight(t_term *term, int i)
{
	char *so;
	char *se;

	so = tgetstr("so", NULL);
	se = tgetstr("se", NULL);
	if (term->prec < term->size.ws_col && term->arg[i].select == 1)
	{
		tputs(so, 1, &ft_putint);
		ft_printf("%s%-*s%s", tgetstr("us", NULL), term->prec,
				term->arg[i].name, tgetstr("ue", NULL));
		tputs(se, 1, &ft_putint);
	}
	else if (term->arg[i].select == 1)
	{
		tputs(so, 1, &ft_putint);
		ft_printf("%s%-.*s%s", tgetstr("us", NULL), term->prec,
				term->arg[i].name, tgetstr("ue", NULL));
		tputs(se, 1, &ft_putint);
	}
	else if (term->prec < term->size.ws_col)
		ft_printf("%s%-*s%s", tgetstr("us", NULL), term->prec,
				term->arg[i].name, tgetstr("ue", NULL));
	else
		ft_printf("%s%-.*s%s", tgetstr("us", NULL), term->prec,
				term->arg[i].name, tgetstr("ue", NULL));
}

static void	display_normal(t_term *term, int i)
{
	char *so;
	char *se;

	so = tgetstr("so", NULL);
	se = tgetstr("se", NULL);
	if (term->prec < term->size.ws_col && term->arg[i].select == 1)
	{
		tputs(so, 1, &ft_putint);
		ft_printf("%-*s", term->prec, term->arg[i].name);
		tputs(se, 1, &ft_putint);
	}
	else if (term->arg[i].select == 1)
	{
		tputs(so, 1, &ft_putint);
		ft_printf("%-.*s", term->size.ws_col, term->arg[i].name);
		tputs(se, 1, &ft_putint);
	}
	else if (term->prec < term->size.ws_col)
		ft_printf("%-*s", term->prec, term->arg[i].name);
	else
		ft_printf("%-.*s", term->size.ws_col, term->arg[i].name);
}

static void	manage_display(t_term *term, int i, int *tmp)
{
	if (*tmp >= term->elem)
	{
		ft_printf("\n");
		*tmp = 0;
		term->line = term->line + 1;
	}
	if (term->arg[i].high == 1)
		display_highlight(term, i);
	else
		display_normal(term, i);
	*tmp = *tmp + 1;
	term->arg[i].last = 0;
}

static int	check_space_term(t_term *term)
{
	int		high;
	int		part;
	int		i;

	high = 0;
	part = 0;
	get_precision(term);
	if ((term->elem = (term->size.ws_col - 10) / term->prec) == 0)
		term->elem = 1;
	while (term->arg[high].name && term->arg[high].high == 0)
		high++;
	while (part * (term->size.ws_row - 1) * term->elem < high + 1)
		part++;
	i = (part - 1) * (term->size.ws_row - 1) * term->elem - 1;
	if (i + term->size.ws_row * term->elem < term->nb)
		term->arg[i + (term->size.ws_row - 1) * term->elem + 1].last = 1;
	return (i);
}

void		print_args(t_term *term)
{
	int		i;
	int		tmp;
	char	*up;
	char	*cr;
	char	*cd;

	term->line = 1;
	up = tgetstr("up", NULL);
	cr = tgetstr("cr", NULL);
	cd = tgetstr("cd", NULL);
	tmp = 0;
	tputs(cd, 2, &ft_putint);
	i = check_space_term(term);
	while (term->arg[++i].name && term->arg[i].last == 0)
		manage_display(term, i, &tmp);
	i = -1;
	while (term->arg[++i].name)
		term->arg[i].last = 0;
	term->arg[i].last = 1;
	i = 0;
	while (++i < term->line)
		tputs(up, 2, &ft_putint);
	tputs(cr, 2, &ft_putint);
}
