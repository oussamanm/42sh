/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_srcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 20:48:37 by mfilahi           #+#    #+#             */
/*   Updated: 2019/12/08 20:48:40 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_alias		*get_next_node(t_aliaspkg *data, char *value)
{
	t_alias *curr;

	curr = data->head_ref;
	while (curr)
	{
		if ((ft_strcmp(value, curr->shortcut) == 0))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

char		*get_value(t_aliaspkg *data, char *key)
{
	t_alias *curr;

	curr = data->head_ref;
	while (curr && (ft_strcmp(curr->shortcut, key) != 0))
		curr = curr->next;
	if (curr->cmd)
		return (ft_strdup(curr->cmd));
	return (NULL);
}

void		freetmplistalias(t_aliashel **head)
{
	t_aliashel	*next;
	t_aliashel	*curr;

	curr = *head;
	next = *head;
	while (curr)
	{
		next = curr->next;
		ft_strdel(&curr->string);
		free(curr);
		curr = next;
	}
}

int			value_found_as_key(t_aliaspkg *data, char *valueaskey)
{
	t_alias *curr;

	curr = data->head_ref;
	while (curr && (ft_strcmp(valueaskey, curr->shortcut) != 0))
		curr = curr->next;
	if (curr)
		return (1);
	return (0);
}
