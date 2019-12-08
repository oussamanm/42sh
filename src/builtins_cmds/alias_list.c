/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 20:46:14 by mfilahi           #+#    #+#             */
/*   Updated: 2019/12/08 20:46:16 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_checker(char **arr, char **newvalue)
{
	if (arr[1])
	{
		(*newvalue) ? ft_strdel(newvalue) : 0;
		*newvalue = ft_strjoin(" ", arr[1]);
	}
}

int		free_elem(char *lastkey, char **arr, t_aliashel **head)
{
	if (lastkey)
		ft_strdel(&lastkey);
	freetmplistalias(head);
	ft_free2d(arr);
	return (1);
}

void	init_var(t_aliashel **head, t_aliashel **tail, char ***arr)
{
	*head = NULL;
	*tail = NULL;
	*arr = NULL;
}

int		aliaschecker(t_aliashel **head, char *key, char **ptr)
{
	t_aliashel *curr;

	curr = *head;
	while (curr)
	{
		if ((ft_strcmp(curr->string, key) == 0))
		{
			*ptr = ft_strdup(key);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int		ft_list(t_aliashel **head, t_aliashel **tail,\
char *shortkey, char **ptr)
{
	t_aliashel *newnode;

	if (*head)
	{
		if (aliaschecker(head, shortkey, ptr))
			return (1);
	}
	if (!(newnode = (t_aliashel *)malloc(sizeof(t_aliashel))))
		return (0);
	newnode->string = ft_strdup(shortkey);
	newnode->next = NULL;
	if (!*head && !*tail)
	{
		*head = newnode;
		*tail = *head;
	}
	else
	{
		(*tail)->next = newnode;
		*tail = newnode;
	}
	return (0);
}
