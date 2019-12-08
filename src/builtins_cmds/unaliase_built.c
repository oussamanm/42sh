/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unaliase_built.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:57:34 by mfilahi           #+#    #+#             */
/*   Updated: 2019/11/09 14:57:47 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** - followed to down function;
*/

int		removeal_2(t_aliaspkg *data, t_alias *curr, t_alias *prev)
{
	if (curr == data->head_ref)
		data->head_ref = curr->next;
	else if (curr == data->tail_ref)
	{
		prev->next = NULL;
		data->tail_ref = prev;
	}
	else
		prev->next = curr->next;
	ft_strdel(&curr->shortcut);
	ft_strdel(&curr->equal);
	ft_strdel(&curr->cmd);
	free(curr);
	if (!data->head_ref)
		data->tail_ref = NULL;
	return (1);
}

/*
** - remove a specific alias or all aliases;
*/

int		rm_alias_by_elem_flag(char *shortcut)
{
	t_aliaspkg	*data;
	t_alias		*curr;
	t_alias		*prev;

	data = storeaddrstruct(NULL);
	if (data->head_ref == NULL)
		return (0);
	curr = data->head_ref;
	prev = curr;
	while (curr)
	{
		if ((ft_strcmp(curr->shortcut, shortcut) == 0))
			break ;
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return (0);
	return (removeal_2(data, curr, prev));
}

/*
** - free alias list;
*/

int		freealiaslist(void)
{
	t_aliaspkg	*data;
	t_alias		*prev;

	data = storeaddrstruct(NULL);
	prev = data->head_ref;
	while (data->head_ref)
	{
		data->head_ref = data->head_ref->next;
		ft_strdel(&prev->shortcut);
		ft_strdel(&prev->equal);
		ft_strdel(&prev->cmd);
		free(prev);
		prev = data->head_ref;
	}
	data->tail_ref = NULL;
	data->head_ref = data->tail_ref;
	return (1);
}

int		ft_buil_unalias_1(t_tokens *st_token)
{
	int		flag;
	char	*arg;

	flag = 0;
	while (st_token)
	{
		arg = st_token->value;
		if ((arg[0] == '=' || arg[ft_strlen(arg) - 1] == '=') && (flag = 1))
			print_error("not found", "unalias: ", arg, 0);
		else
		{
			if (!(rm_alias_by_elem_flag(arg)))
				print_error("not found", "unalias: ", arg, 0);
		}
		st_token = st_token->next;
	}
	return (flag);
}

/*
** - the main func called in shell
*/

int		ft_buil_unalias(t_tokens *st_token)
{
	int		flag;

	(st_token) ? (st_token = st_token->next) : NULL;
	if (!st_token)
	{
		print_error("[-a] [name[=value] ... ]", NULL, "unalias: usage: ", 0);
		return (EXIT_FAILURE);
	}
	else if ((ft_strcmp(st_token->value, "-a") == 0))
	{
		freealiaslist();
		return (EXIT_SUCCESS);
	}
	else if (st_token->value[0] == '-')
		return (alias_invalid_option(st_token->value));
	flag = ft_buil_unalias_1(st_token);
	if (flag)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
