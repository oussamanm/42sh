/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:01:27 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/03 21:01:28 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	ft_call_redire : calls function redirection
*/

void			ft_call_redire(t_redir *st_redir, t_tokens *st_tokens)
{
	if (CHECK_TOKEN(st_tokens->token, T_RED_OUT_S, T_RED_OUT_A, T_RED_OUT_B))
		ft_redi_out(st_redir, st_tokens);
	else if (CHECK_TOKEN(st_tokens->token, T_RED_IN_S, T_RED_IN_A, T_RED_IN_B))
		ft_redi_in(st_redir, st_tokens);
	else if (CHECK_TOKEN(st_tokens->token, T_RED_APP_S, T_RED_APP_M,
		T_RED_APP_A))
		ft_redi_app(st_redir, st_tokens);
	else if (st_tokens->token == T_RED_BOTH)
		ft_redi_both(st_redir, st_tokens);
}

/*
**	ft_read_tokens : Read token and fill struct t_redir with redirection
*/

static void		ft_read_tokens(t_pipes *st_pipes, t_tokens *st_tokens)
{
	t_redir		*st_redir;
	t_redir		*head;

	head = st_pipes->st_redir;
	st_redir = head;
	while (st_tokens != NULL)
	{
		if (st_tokens->token < 0 && st_tokens->token != T_RED_HER_D)
		{
			if (head == NULL)
			{
				st_redir = ft_new_redir();
				head = st_redir;
			}
			else
			{
				st_redir->next = ft_new_redir();
				st_redir = st_redir->next;
			}
			ft_call_redire(st_redir, st_tokens);
		}
		st_tokens = st_tokens->next;
	}
	st_pipes->st_redir = head;
}

/*
**	ft_apply_redi : apply redirection
*/

static int		ft_apply_redi(t_pipes *st_pipes)
{
	t_redir	*st_r;

	if (st_pipes == NULL)
		return (REDI_KO);
	st_r = st_pipes->st_redir;
	while (st_r != NULL)
	{
		(st_r->type_red == 4) ? ft_apply_hered(st_r) : NULL;
		if (st_r->fd_close != -1)
			close(st_r->fd_close);
		if (st_r->fd_red != -1 && st_r->fd_des != -1)
		{
			if (st_r->fd_des == -2)
				st_r->fd_des = ft_open_file(st_r->fd_file, st_r->type_red);
			if (st_r->fd_des == -1 || !ft_exist_fd(st_r->fd_des))
				return (REDI_KO);
			if (dup2(st_r->fd_des, st_r->fd_red) == -1)
				return (ft_putendl_fd("Error in dub", 2) && 0);
		}
		if (st_r->fd_err != -1 && st_r->fd_des != -1)
			if (dup2(st_r->fd_des, st_r->fd_err) == -1)
				return (ft_putendl_fd("Error in dub", 2) && 0);
		st_r = st_r->next;
	}
	return (REDI_OK);
}

/*
**	ft_update_args : update args by remove redirection
*/

static void		ft_update_args(t_pipes *st_pipes)
{
	int			count;
	int			i;
	t_tokens	*st_temp;

	count = 0;
	i = 0;
	st_temp = st_pipes->st_tokens;
	while (st_temp != NULL && st_temp->value != NULL)
	{
		if (!(st_temp->token < 0 || st_temp->is_arg == 1) && st_temp->is_arg != T_EQUAL)
			count++;
		st_temp = st_temp->next;
	}
	st_temp = st_pipes->st_tokens;
	ft_strrdel(st_pipes->args);
	st_pipes->args = ft_strr_new(count);
	while (st_temp != NULL && st_temp->value != NULL)
	{
		if (!(st_temp->token < 0 || st_temp->is_arg))
			(st_pipes->args)[i++] = ft_strdup(st_temp->value);
		st_temp = st_temp->next;
	}
	(st_pipes->args)[i] = NULL;
}

/*
**	ft_parse_redir : read tokens and apply redirection
*/

int				ft_parse_redir(t_pipes *st_pipes)
{
	ft_update_tokens(st_pipes->st_tokens);
	ft_read_tokens(st_pipes, st_pipes->st_tokens);
	if (ft_apply_redi(st_pipes) == REDI_KO)
		return (PARSE_KO);
	ft_update_args(st_pipes);
	return (PARSE_OK);
}
