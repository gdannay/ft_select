/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:20:45 by gdannay           #+#    #+#             */
/*   Updated: 2018/02/16 12:33:01 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				main(int ac, char **av)
{
	t_term		*term;

	if (ac > 1)
	{
		if (!(term = (t_term *)malloc(sizeof(t_term)))
				|| init_term(term) == -1
				|| !(init_arg(ac, av, term)))
			return (-1);
		while (term->key != 10 && (term->key = ft_getch()) != 10)
		{
			if (display_args(term) == -1)
				return (-1);
		}
		default_term(term);
		free_all(term);
	}
	return (0);
}
