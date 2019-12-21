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
	unsigned int value;

	if (!key)
		return (0);
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

int				hash_table(char **args, char **tmpenv)
{
	int		err;
	char	*ret;

	err = 0;
	if (!args[0])
		display_hash_table();
	else if (args[0][0] != '-')
	{
		while (*args)
		{
			if (!(ret = ft_find_path(*args, tmpenv)))
				(err = 1) ? print_error("not found", "hash: ", *args, 0) : 0;
			ft_strdel(&ret);
			args++;
		}
	}
	else if (args[0][0] == '-' && check_hash_op(args[0] + 1))
		erase_hash_table();
	else
	{
		print_error("invalid option ", "42sh: hash: ", args[0], 0);
		print_error("hash [-r]", NULL, "hash: usage: ", 0);
		return (EXIT_FAILURE);
	}
	return (err ? EXIT_FAILURE : EXIT_SUCCESS);
}
