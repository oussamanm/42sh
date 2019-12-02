/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:05:48 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/02 12:05:53 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
** Initiale alias and hash_table
*/

void		init_alias_hash(void)
{
	t_aliaspkg	*data;
	t_hash		**hash_arr;
	int			i;

	i = -1;
	data = (t_aliaspkg *)ft_memalloc(sizeof(t_aliaspkg));
	storeaddrstruct(data);
	createaliasfile();
	importaliasfilecontent(NULL);
	hash_arr = (t_hash **)ft_memalloc(sizeof(t_hash *) * SIZE);
	while (++i < SIZE)
		hash_arr[i] = NULL;
	store_addr_of_hash(hash_arr, 1);
}

/*
** Save adresse t_history to t_select , to easy access from other function
*/

void		save_address(t_select **select)
{
	static t_select	*p_select;

	if (*select != NULL)
		p_select = *select;
	else
		*select = p_select;
}

/*
** Initiale terminle attr , fill struct info and call function Read
*/

void		initial_read_line(t_history *his, t_select **select)
{
	restore_history(his);
	g_sign = 0;
	*select = (t_select *)ft_memalloc(sizeof(t_select));
	(*select)->start = -1;
	(*select)->end = -1;
	(*select)->save = NULL;
	save_address(select);
}
