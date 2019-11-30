/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_contin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 14:09:29 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/30 14:09:31 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

int			get_last_flag(int *maps)
{
	int i;

	if (!maps)
		return (0);
	i = 0;
	while (maps[i])
		i++;
	return (i - 1);
}

int			find_flag(int *maps, int flag)
{
	int index;

	index = 0;
	if (!maps || !*maps)
		return (-1);
	while (*maps)
	{
		if (*maps == flag)
			return (index);
		index++;
		maps++;
	}
	return (-1);
}

void		clean_maps(int *maps)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!maps || find_flag(maps, -1) == -1)
		return ;
	while (maps[i])
	{
		if (maps[i] != -1)
			maps[j++] = maps[i];
		i++;
	}
	ft_bzero(&maps[j], 1000 - j - 1);
}

int			count_key(int *maps, int key)
{
	int i;

	i = 0;
	if (!maps || !*maps)
		return (0);
	while (maps[i] == key)
		i++;
	return (i);
}

int			closed_dquot(int *maps)
{
	int i;

	if (!maps)
		return (-1);
	i = 0;
	while (maps[i])
	{
		if (maps[i] == 'S')
			return (-1);
		else if (maps[i] == 'Q')
			return (i);
		i++;
	}
	return (0);
}
