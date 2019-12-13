/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 21:06:25 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/10 04:27:41 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	fill structs : Job_controle & Logical_opr & pipe
*/

static void		ft_fill_jobctr(t_cmds *st_cmds)
{
	t_jobctr	*st_jobctr;
	t_tokens	*st_token;
	t_tokens	*st_temp;

	st_cmds->st_jobctr = ft_new_jobctr();
	st_jobctr = st_cmds->st_jobctr;
	st_jobctr->st_tokens = ft_new_token();
	st_token = st_jobctr->st_tokens;
	st_temp = st_cmds->st_tokens;
	while (st_temp)
	{
		if (st_temp->token != T_JOBCTR)
			ft_dup_token(&st_token, st_temp, T_JOBCTR);
		else
		{
			st_jobctr->status = 1;
			if (st_temp->next && (st_jobctr->next = ft_new_jobctr()))
			{
				st_jobctr = st_jobctr->next;
				st_jobctr->st_tokens = ft_new_token();
				st_token = st_jobctr->st_tokens;
			}
		}
		st_temp = st_temp->next;
	}
}

static void		ft_fill_logopr(t_jobctr *st_jobctr)
{
	t_logopr	*st_logopr;
	t_tokens	*st_token;
	t_tokens	*st_temp;

	st_jobctr->st_logopr = ft_new_logopr();
	st_logopr = st_jobctr->st_logopr;
	st_logopr->st_tokens = ft_new_token();
	st_token = st_logopr->st_tokens;
	st_temp = st_jobctr->st_tokens;
	while (st_temp)
	{
		if (st_temp->token != T_LOGOPR_AND && st_temp->token != T_LOGOPR_OR)
			ft_dup_token(&st_token, st_temp, T_LOGOPR_AND);
		else if ((st_logopr->status = st_temp->token))
		{
			if (st_temp->next && (st_logopr->next = ft_new_logopr()))
			{
				st_logopr = st_logopr->next;
				st_logopr->st_tokens = ft_new_token();
				st_token = st_logopr->st_tokens;
			}
		}
		st_temp = st_temp->next;
	}
	st_logopr->bl_jobctr = st_jobctr->status;
}

static void		ft_fill_pipe(t_logopr *st_logopr)
{
	t_pipes		*st_pipes;
	t_tokens	*st_token;
	t_tokens	*st_temp;

	st_logopr->st_pipes = ft_new_pipe();
	st_pipes = st_logopr->st_pipes;
	st_pipes->st_tokens = ft_new_token();
	st_token = st_pipes->st_tokens;
	st_temp = st_logopr->st_tokens;
	while (st_temp)
	{
		st_pipes->bl_jobctr = st_logopr->bl_jobctr;
		if (st_temp->token != T_PIPE)
			ft_dup_token(&st_token, st_temp, T_PIPE);
		else
		{
			if (st_temp->next && (st_pipes->next = ft_new_pipe()))
			{
				st_pipes = st_pipes->next;
				st_pipes->st_tokens = ft_new_token();
				st_token = st_pipes->st_tokens;
			}
		}
		st_temp = st_temp->next;
	}
}

/*
** Parse with semi-colon
*/

t_cmds			*parse_semicolon(t_tokens *tokens)
{
	t_cmds		*st_cmds;
	t_cmds		*cmds_head;
	t_tokens	*st_tokens;

	if (!tokens)
		return (NULL);
	st_cmds = ft_new_cmds();
	cmds_head = st_cmds;
	st_cmds->st_tokens = ft_new_token();
	st_tokens = st_cmds->st_tokens;
	while (tokens)
	{
		if (tokens->token != T_SEMICLN)
			ft_dup_token(&st_tokens, tokens, T_SEMICLN);
		else if (tokens->next && (st_cmds->next = ft_new_cmds()))
		{
			st_cmds = st_cmds->next;
			st_cmds->st_tokens = ft_new_token();
			st_tokens = st_cmds->st_tokens;
		}
		tokens = (tokens) ? tokens->next : tokens;
	}
	return (cmds_head);
}

/*
** Parse command and fill lists: job_ctr, logi_opr, pipes @
*/

void			ft_parse_cmd(t_cmds *st_cmds)
{
	t_jobctr	*st_jobctr;
	t_logopr	*st_logopr;

	if (!st_cmds)
		return ;
	ft_fill_jobctr(st_cmds);
	st_jobctr = st_cmds->st_jobctr;
	while (st_jobctr)
	{
		ft_fill_logopr(st_jobctr);
		st_logopr = st_jobctr->st_logopr;
		while (st_logopr)
		{
			ft_fill_pipe(st_logopr);
			handle_variable(st_logopr->st_pipes);
			st_logopr = st_logopr->next;
		}
		st_jobctr = st_jobctr->next;
	}
}
