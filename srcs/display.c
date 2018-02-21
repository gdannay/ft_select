/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 20:33:51 by gdannay           #+#    #+#             */
/*   Updated: 2018/02/21 11:55:43 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	get_precision(t_term *term)
{
	int i;

	i = -1;
	term->prec = 0;
	while (term->arg[++i].name)
		term->prec = term->prec < (int)ft_strlen(term->arg[i].name)
			? (int)ft_strlen(term->arg[i].name) : term->prec;
	term->prec = term->prec + 1;
}

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
	if (i + 1 > *tmp && i != 0)
	{
		ft_printf("\n");
		*tmp = *tmp + term->elem;
		term->line = term->line + 1;
	}
	if (term->line > term->size.ws_row - 2)
	{
		i -= 2;
		while (term->arg[++i].name)
			term->arg[i].last = 1;
		ft_printf("...");
		*tmp = -1;
	}
	if (term->arg[i].high == 1)
		display_highlight(term, i);
	else
		display_normal(term, i);
	term->arg[i].last = 0;
}

void		print_args(t_term *term)
{
	int		i;
	int		tmp;
	char	*up;
	char	*cr;
	char	*cd;

	i = -1;
	term->line = 1;
	up = tgetstr("up", NULL);
	cr = tgetstr("cr", NULL);
	cd = tgetstr("cd", NULL);
	get_precision(term);
	term->elem = (term->size.ws_col - 10) / term->prec;
	tmp = term->elem;
	tputs(cd, 1, &ft_putint);
	while (tmp != -1 && term->arg[++i].name)
		manage_display(term, i, &tmp);
	i = 0;
	while (++i < term->line)
		tputs(up, 1, &ft_putint);
	tputs(cr, 1, &ft_putint);
}
