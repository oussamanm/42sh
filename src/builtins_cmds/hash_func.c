/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:18:54 by mfilahi           #+#    #+#             */
/*   Updated: 2019/11/09 17:21:48 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** - lookup for a value by a hashed key;
*/

char	*lookup_hash(char *key)
{
	t_hash			**hash_arr;
	unsigned int	index;
	t_hash			*curr;

	if (!key)
		return (NULL);
	hash_arr = store_addr_of_hash(NULL, 0);
	index = hash(key);
	curr = hash_arr[index];
	while (curr != NULL && ft_strcmp(curr->key, key) != 0)
		curr = curr->next;
	if (curr)
		return (curr->value);
	return (NULL);
}

/*
** - lookup for a value by a hashed key;
*/

t_hash	*lookup_hash_2(char *key)
{
	t_hash			**hash_arr;
	unsigned int	index;
	t_hash			*curr;

	hash_arr = store_addr_of_hash(NULL, 0);
	index = hash(key);
	curr = hash_arr[index];
	while (curr != NULL && ft_strcmp(curr->key, key) != 0)
		curr = curr->next;
	return (curr);
}

/*
** - insertion key and value in list
*/

void	insert_hash_2(t_hash *node, t_hash **hash_arr, char *key, char *value)
{
	unsigned int	index;
	t_hash			*curr;

	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->counter = 1;
	node->next = NULL;
	index = hash(key);
	ft_strdel(&value);
	if (!hash_arr[index])
		hash_arr[index] = node;
	else
	{
		curr = hash_arr[index];
		while (curr->next)
			curr = curr->next;
		curr->next = node;
	}
}

/*
** - insertion key and value into a hashed key in list.
*/

void	insert_hash(char *key, char *value)
{
	t_hash	*node;
	t_hash	**hash_arr;

	if (!key || !value)
		return ;
	hash_arr = store_addr_of_hash(NULL, 0);
	if ((node = lookup_hash_2(key)))
	{
		node->counter++;
		ft_strdel(&value);
		return ;
	}
	if (!(node = (t_hash *)malloc(sizeof(t_hash))))
		return ;
	insert_hash_2(node, hash_arr, key, value);
}

/*
** - Remove element of hash array;
*/

void	erase_hash_table(void)
{
	t_hash	**hash_arr;
	t_hash	**node;
	t_hash	*tmp;
	int		i;

	hash_arr = store_addr_of_hash(NULL, 0);
	node = NULL;
	i = -1;
	while (++i < SIZE)
	{
		node = &hash_arr[i];
		while (*node)
		{
			tmp = (*node)->next;
			ft_strdel(&(*node)->key);
			ft_strdel(&(*node)->value);
			free(*node);
			*node = tmp;
		}
	}
}
