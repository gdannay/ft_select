/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 11:56:27 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/07 11:58:22 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_joinpath(char *dir, char *name)
{
	char	*file_dir;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if ((file_dir = (char *)malloc(sizeof(char) *
					(ft_strlen(dir) + ft_strlen(name) + 2))) == NULL)
		return (NULL);
	while (dir && dir[++i] != '\0')
		file_dir[i] = dir[i];
	if (i >= 0 && file_dir[i - 1] != '/')
	{
		file_dir[i] = '/';
		i++;
	}
	while (name && name[j] != '\0')
	{
		file_dir[i] = name[j];
		i++;
		j++;
	}
	file_dir[i] = '\0';
	return (file_dir);
}
