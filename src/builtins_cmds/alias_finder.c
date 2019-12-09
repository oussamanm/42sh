/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_finder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 20:43:06 by mfilahi           #+#    #+#             */
/*   Updated: 2019/12/08 20:43:11 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*aliasfinder_2(t_aliaspkg *data, t_aliashel **head,\
t_aliashel **tail, t_alias *curr)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	if (ft_list(head, tail, curr->shortcut, &str))
	{
		tmp = str;
		if ((ft_strcmp((*head)->string, str) != 0))
		{
			str = get_value(data, str);
			ft_strdel(&tmp);
			return (str);
		}
		else
		{
			str = ft_strdup((*head)->string);
			ft_strdel(&tmp);
			return (str);
		}
	}
	return (NULL);
}

char	*aliasfinder_3(t_aliaspkg *data, t_alias *curr, char *new)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	tmp = NULL;
	ret = get_value(data, curr->shortcut);
	if (new)
	{
		tmp = ret;
		ret = ft_strjoin(ret, new);
		ft_strdel(&tmp);
		ft_strdel(&new);
	}
	return (ret);
}

char	*aliasfinder_5(t_alias *curr, t_aliashel **head,\
char **arr, char *lastkey)
{
	t_aliaspkg	*data;
	char		*ret;

	data = storeaddrstruct(NULL);
	ret = aliasfinder_3(data, curr, lastkey);
	free_elem(NULL, arr, head);
	return (ret);
}

int		aliasfinder_4(t_alias **curr, t_aliashel **head,\
char **ret, char **arr)
{
	t_aliaspkg *data;

	data = storeaddrstruct(NULL);
	if ((*curr = get_next_node(data, arr[0])))
		ft_free2d(arr);
	else
	{
		*ret = ft_strdup(arr[0]);
		ft_free2d(arr);
		freetmplistalias(head);
		return (1);
	}
	return (0);
}

char	*aliasfinder(t_alias *curr, char *value, char *lastkey)
{
	t_aliaspkg	*data;
	t_aliashel	*head;
	t_aliashel	*tail;
	char		**arr;
	char		*ret;

	data = storeaddrstruct(NULL);
	init_var(&head, &tail, &arr);
	while (1)
	{
		value = get_value(data, curr->shortcut);
		(arr = ft_strsplit(value, ' ')) ? ft_strdel(&value) : 0;
		if (value_found_as_key(data, arr[0]))
		{
			ft_checker(arr, &lastkey);
			if ((ret = aliasfinder_2(data, &head, &tail, curr)))
				return ((free_elem(lastkey, arr, &head) ? ret : ret));
		}
		else
			return (aliasfinder_5(curr, &head, arr, lastkey));
		if (aliasfinder_4(&curr, &head, &ret, arr))
			return (ret);
	}
	return (NULL);
}
