/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:14:35 by mfilahi           #+#    #+#             */
/*   Updated: 2019/11/09 17:14:37 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** - store @ of hash array;
*/

t_hash			**store_addr_of_hash(t_hash **hash_arr, int flag)
{
	static t_hash **tmp_arr;

	if (hash_arr || flag)
		tmp_arr = hash_arr;
	return (tmp_arr);
}

/*
** - hash a key;
*/

unsigned int	hash(char *key)
{
	int value;

	value = key[0] - 'a';
	return (value % SIZE);
}

/*
** - display hash array content;
*/

void			display_hash_table_2(t_hash **hash_arr, int *flag)
{
	t_hash	*node;
	int		i;
	int		r;
	int		n;

	i = -1;
	r = 1;
	n = 0;
	while (++i < SIZE)
	{
		node = hash_arr[i];
		while (node && (*flag = 1))
		{
			n = r;
			if (n)
				ft_putendl_fd("hits       command", 1);
			r = 0;
			ft_putnbr_fd(node->counter, 1);
			ft_putstr_fd("          ", 1);
			ft_putendl_fd(node->value, 1);
			node = node->next;
		}
	}
}

/*
** - display hash array content;
*/

void			display_hash_table(void)
{
	t_hash	**hash_arr;
	int		flag;

	flag = 0;
	hash_arr = store_addr_of_hash(NULL, 0);
	display_hash_table_2(hash_arr, &flag);
	if (!flag)
		ft_putendl_fd("hash: hash table empty", 1);
}

/*
** main func called in shell
*/

void			hash_table(char **args)
{
	if (ft_strcmp(args[0], "-r") == 0)
	{
		erase_hash_table();
		return ;
	}
	else if (!args[0])
		display_hash_table();
}