/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hash_and_alias.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:16:43 by mfilahi           #+#    #+#             */
/*   Updated: 2019/11/15 18:21:05 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** free alias list;
*/

void	free_alias_list(void)
{
	t_aliaspkg	*data;
	t_alias		*curr;
	t_alias		*tmp;

	data = storeaddrstruct(NULL);
	curr = data->head_ref;
	while (curr)
	{
		tmp = curr->next;
		(curr->shortcut) ? ft_strdel(&curr->shortcut) : 0;
		(curr->equal) ? ft_strdel(&curr->equal) : 0;
		(curr->cmd) ? ft_strdel(&curr->cmd) : 0;
		free(curr);
		curr = NULL;
		curr = tmp;
	}
}

/*
** free hash and alias;
*/

void	free_hash_and_alias(void)
{
	t_hash	**hash_arr;
	int		i;

	hash_arr = store_addr_of_hash(NULL, 0);
	erase_hash_table();
	i = -1;
	while (++i < SIZE)
		free(hash_arr[i]);
	free_alias_list();
}
