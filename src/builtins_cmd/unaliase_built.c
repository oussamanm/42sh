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

int		removeal_2(t_aliaspkg *data, t_alias *curr, t_alias *prev, int flag)
{
	if (curr == data->head_ref && flag)
		data->head_ref = curr->next;
	else if (curr == data->tail_ref && flag)
	{
		prev->next = NULL;
		data->tail_ref = prev;
	}
	else if (flag)
		prev->next = curr->next;
	if (flag)
	{
		ft_strdel(&curr->shortcut);
		ft_strdel(&curr->cmd);
		free(curr);
		if (!data->head_ref)
			data->tail_ref = NULL;
		return (1);
	}
	return (0);
}

int		removealiasbyelemorbyflag(char *shortcut, int check)
{
	t_aliaspkg	*data;
	t_alias		*curr;
	t_alias		*prev;
	int			flag;

	flag = 0;
	data = storeaddrstruct(NULL);
	if (data->head_ref == NULL)
		return (0);
	curr = data->head_ref;
	prev = curr;
	(!check) ? (shortcut = ft_strjoin(shortcut, "=")) : 0;
	while (curr)
	{
		if ((ft_strcmp(curr->shortcut, shortcut) == 0) || (curr->flag && check))
		{
			flag = 1;
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	if (removeal_2(data, curr, prev, flag))
		return (1);
	return (0);
}

void	ft_buil_updatealias(char **args)
{
	if (!(ft_strcmp(*args, "42shrc") == 0))
		print_error("No such file or directory", NULL, *args, 0);
	else
	{
		while (removealiasbyelemorbyflag(NULL, 1))
			;
		importaliasfilecontent();
	}
}

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
		ft_strdel(&prev->cmd);
		free(prev);
		prev = data->head_ref;
	}
	data->tail_ref = NULL;
	data->head_ref = data->tail_ref;
	return (1);
}

int		ft_buil_unalias(t_tokens *st_token, int flag)
{
	char	*arg;

	(st_token) ? (st_token = st_token->next) : NULL;
	if (!st_token)
	{
		print_error("unalias: usage: ", "42sh:", "[-a] [name[=value] ... ]", 0);
		return (0);
	}
	if ((ft_strcmp(st_token->value, "-a") == 0) ? freealiaslist() : 0)
		return (0);
	while (st_token)
	{
		arg = st_token->value;
		if ((arg[0] == '=' || arg[ft_strlen(arg) - 1] == '=') && (flag = 1))
			print_error("not found", "42sh: unalias: ", arg, 0);
		else
		{
			if (!(removealiasbyelemorbyflag(arg, 0)) && (flag = 1))
				print_error("not found", "42sh: unalias: ", arg, 0);
		}
		st_token = st_token->next;
	}
	if (!st_token || flag)
		return (1);
	return (0);
}
