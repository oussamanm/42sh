/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 21:06:25 by onouaman          #+#    #+#             */
/*   Updated: 2019/09/22 21:06:27 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


/*
**	fill structs : Job_controle & Logical_opr & pipe
*/

static void     ft_fill_jobctr(t_cmds *st_cmds)
{
	t_jobctr	*st_jobctr;
	t_tokens	*st_token;
	t_tokens	*st_temp;

	// alloc st_jobctr
	st_cmds->st_jobctr = ft_new_jobctr();
	st_jobctr = st_cmds->st_jobctr;

	// alloc t_tokens 
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
			if (st_temp->next) // if exist more tokens
			{
				st_jobctr->next = ft_new_jobctr();
				st_jobctr = st_jobctr->next;
				st_jobctr->st_tokens = ft_new_token();
				st_token = st_jobctr->st_tokens;
			}
		}
		st_temp = st_temp->next;
	}
}

static void     ft_fill_logopr(t_jobctr *st_jobctr)
{
	t_logopr	*st_logopr;
	t_tokens	*st_token;
	t_tokens	*st_temp;

	// alloc st_logopr
	st_jobctr->st_logopr = ft_new_logopr();
	st_logopr = st_jobctr->st_logopr;

	// alloc t_tokens in st_token
	st_logopr->st_tokens = ft_new_token();
	st_token = st_logopr->st_tokens;

	st_temp = st_jobctr->st_tokens;
	while (st_temp)
	{
		if (st_temp->token != T_LOGOPR_AND && st_temp->token != T_LOGOPR_OR)
			ft_dup_token(&st_token, st_temp, T_LOGOPR_AND);
		else
		{
			st_logopr->bl_jobctr = (st_jobctr->status) ? 1 : 0;
			st_logopr->status = st_temp->token;
			if (st_temp->next) // if exist more tokens
			{
				st_logopr->next = ft_new_logopr();
				st_logopr = st_logopr->next;
				st_logopr->st_tokens = ft_new_token();
				st_token = st_logopr->st_tokens;
			}
		}
		st_temp = st_temp->next;
	}
}

static void     ft_fill_pipe(t_logopr *st_logopr)
{
	t_pipes		*st_pipes;
	t_tokens	*st_token;
	t_tokens	*st_temp;

	// alloc st_logopr
	st_logopr->st_pipes = ft_new_pipe();
	st_pipes = st_logopr->st_pipes;

	// alloc t_tokens in st_token
	st_pipes->st_tokens = ft_new_token();
	st_token = st_pipes->st_tokens;

	st_temp = st_logopr->st_tokens;
	while (st_temp)
	{
		if (st_temp->token != T_PIPE)
			ft_dup_token(&st_token, st_temp, T_PIPE);
		else
		{
			st_pipes->bl_jobctr = (st_logopr->bl_jobctr) ? 1 : 0; 
			if (st_temp->next) // if exist more tokens
			{
				st_pipes->next = ft_new_pipe();
				st_pipes = st_pipes->next;
				st_pipes->st_tokens = ft_new_token();
				st_token = st_pipes->st_tokens;
			}
		}
		st_temp = st_temp->next;
	}
}


/*
** Fill Intern and Temp variables
*/

static void		ft_fill_vrbs(t_pipes *st_pipes)
{
	char		**tmp_env;

	if (!st_pipes)
		return ;
	if (!ft_check_intern(st_pipes))	/// Fill intern variable
		ft_fill_intern(st_pipes);
	else										/// temp environ
	{
		tmp_env = ft_tokens_arg_env(st_pipes->st_tokens);
		st_pipes->tmp_env = ft_fill_env(tmp_env);
	}
}


/*
** Fill args with token except T_EQUAL
*/

static void		ft_fill_args(t_pipes *st_pipes)
{
	if (!st_pipes)
		return ;
	while (st_pipes)
	{
		/// add condition in function below : ! T_EQUAL T_SUBSHELL
		ft_tokens_args(st_pipes);

		st_pipes = st_pipes->next;
	}
}

void            ft_parse_cmd(t_cmds *st_cmds)
{
	t_jobctr	*st_jobctr;
	t_logopr	*st_logopr;

	if (!st_cmds)
		return ;
	/// Fill Job_Controle
	ft_fill_jobctr(st_cmds);
	st_jobctr = st_cmds->st_jobctr;
	while (st_jobctr)
	{
		/// Fill Log_Operator
		ft_fill_logopr(st_jobctr);
		st_logopr = st_jobctr->st_logopr;
		while (st_logopr)
		{
			/// Fill Pipe
			ft_fill_pipe(st_logopr);
			// Fill intern variable and tmp_env
			if (st_logopr->st_pipes && !st_logopr->st_pipes->next && ft_check_token(st_logopr->st_pipes->st_tokens, T_EQUAL))
				ft_fill_vrbs(st_logopr->st_pipes);

			/// Fill args without T_EQUAL , T_SUBSHL,
			ft_fill_args(st_logopr->st_pipes);
			st_logopr = st_logopr->next;
		}
		st_jobctr = st_jobctr->next;
	}
}
