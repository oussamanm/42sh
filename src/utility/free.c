/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 19:26:08 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/07 18:03:20 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		free_list_pipe(t_pipes *st_pipes)
{
	t_pipes	*temp;

	temp = NULL;
	while (st_pipes)
	{
		free_list_redir(st_pipes->st_redir);
		temp = st_pipes->next;
		free_tokens(st_pipes->st_tokens, 0);
		ft_strrdel(st_pipes->tmp_env);
		ft_strrdel(st_pipes->args);
		free(st_pipes);
		st_pipes = temp;
	}
}

void		free_list_logopr(t_logopr *st_logopr)
{
	t_logopr	*temp;

	temp = NULL;
	while (st_logopr)
	{
		free_list_pipe(st_logopr->st_pipes);
		temp = st_logopr->next;
		free_tokens(st_logopr->st_tokens, 0);
		free(st_logopr);
		st_logopr = temp;
	}
}

void		free_list_jobctr(t_jobctr *st_jobctr)
{
	t_jobctr	*temp;

	temp = NULL;
	while (st_jobctr)
	{
		free_list_logopr(st_jobctr->st_logopr);
		temp = st_jobctr->next;
		free_tokens(st_jobctr->st_tokens, 0);
		free(st_jobctr);
		st_jobctr = temp;
	}
}

void		free_list_cmds(t_cmds *st_cmds)
{
	t_cmds *st_temp;

	if (!st_cmds)
		return ;
	while (st_cmds)
	{
		st_temp = st_cmds->next;
		free_tokens(st_cmds->st_tokens, 1);
		free_list_jobctr(st_cmds->st_jobctr);
		free(st_cmds->fd);
		free(st_cmds);
		st_cmds = st_temp;
	}
}
