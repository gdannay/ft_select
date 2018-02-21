/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 10:07:13 by gdannay           #+#    #+#             */
/*   Updated: 2018/02/21 12:07:56 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		space(t_term *term)
{
	int i;

	i = 0;
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
	term->key = 0;
}

void		del(t_term *term)
{
	int i;
	int	j;

	i = 0;
	j = 0;
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
	term->nb = term->nb - 1;
	term->key = 0;
}

static void	arrow_up_down(t_term *term, int i, int j)
{
	if (term->key == UP)
	{
		if (i >= term->elem)
			term->arg[i - term->elem].high = 1;
		else if (term->arg[j].name == NULL && term->nb % term->elem == 0)
			term->arg[term->nb - term->elem + i].high = 1;
		else if (term->arg[j].name == NULL && term->nb % term->elem > i)
			term->arg[term->nb - term->nb % term->elem + i].high = 1;
		else if (term->arg[j].name)
			term->arg[j].high = 1;
		else
			term->arg[term->nb - 1].high = 1;
		term->key = 0;
	}
	else if (term->key == DOWN)
	{
		if (term->arg[i + term->elem - 1].last == 0
				&& i < term->nb - term->elem)
			term->arg[i + term->elem].high = 1;
		else if (term->arg[j].name == NULL && term->nb % term->elem == 0)
			term->arg[i - term->nb + term->elem].high = 1;
		else
			term->arg[i % term->elem].high = 1;
		term->key = 0;
	}
}

static void	arrow_left_right(t_term *term, int i, int j)
{
	if (term->key == RIGHT)
	{
		if (term->arg[i + 1].name == NULL || term->arg[i].last == 1)
			term->arg[0].high = 1;
		else
			term->arg[i + 1].high = 1;
		term->key = 0;
	}
	else if (term->key == LEFT)
	{
		if (i == 0 && term->arg[term->nb - 1].last == 0)
			term->arg[term->nb - 1].high = 1;
		else if (i == 0)
			term->arg[j].high = 1;
		else
			term->arg[i - 1].high = 1;
		term->key = 0;
	}
}

void		arrow(t_term *term)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (term->arg[i].name && term->arg[i].high == 0)
		i++;
	while (term->arg[j].name && term->arg[j].last == 0)
		j++;
	ft_getch();
	if ((term->key = ft_getch()) == UP || term->key == DOWN)
		arrow_up_down(term, i, j);
	else if (term->key == RIGHT || term->key == LEFT)
		arrow_left_right(term, i, j);
	else
		term->key = 1;
	term->arg[i].high = 0;
}
