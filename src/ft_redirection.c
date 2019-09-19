/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 20:44:28 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/03 20:44:30 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
** Redirection output >	 :
*/

void	ft_redi_out(t_redir *st_redir, t_tokens *st_tokens)
{
	ft_init_redi(st_redir, 1);
	if (st_tokens->token == T_RED_OUT_S)
	{
		if (PREV && PREV->indx == st_tokens->indx &&
			ft_isalldigit(PREV->value) && PREV->token == 0)
		{
			PREV->is_arg = 1;
			st_redir->fd_red = ft_atoi(PREV->value);
		}
		st_redir->fd_des = -2;
		st_redir->fd_file = st_tokens->next->value;
		st_tokens->next->is_arg = 1;
	}
	else if (st_tokens->token == T_RED_OUT_A)
		ft_redi_out_h(st_redir, st_tokens);
	else if (st_tokens->token == T_RED_OUT_B)
	{
		if (PREV && PREV->indx == st_tokens->indx && ft_isalldigit(PREV->value))
		{
			PREV->is_arg = 1;
			st_redir->fd_close = ft_atoi(PREV->value);
		}
		else
			st_redir->fd_close = 1;
	}
}

/*
** Redirection input <	 :
*/

void	ft_redi_in(t_redir *st_redir, t_tokens *st_tokens)
{
	ft_init_redi(st_redir, 0);
	if (st_tokens->token == T_RED_IN_S)
	{
		if (PREV && PREV->indx == st_tokens->indx &&
			ft_isalldigit(PREV->value) && (PREV->is_arg = 1))
			st_redir->fd_red = ft_atoi(st_tokens->prev->value);
		st_redir->fd_des = -2;
		st_redir->fd_file = st_tokens->next->value;
		st_tokens->next->is_arg = 1;
	}
	else if (st_tokens->token == T_RED_IN_A)
	{
		if (PREV && PREV->indx == st_tokens->indx &&
			ft_isalldigit(PREV->value) && (PREV->is_arg = 1))
			st_redir->fd_red = ft_atoi(st_tokens->prev->value);
		st_redir->fd_des = ft_atoi(st_tokens->next->value);
		st_tokens->next->is_arg = 1;
	}
	else if (st_tokens->token == T_RED_IN_B)
	{
		if (PREV && PREV->indx == st_tokens->indx &&
			ft_isalldigit(PREV->value) && (PREV->is_arg = 1))
			st_redir->fd_close = ft_atoi(PREV->value);
	}
}

/*
** Redirection append >> :
*/

void	ft_redi_app(t_redir *st_redir, t_tokens *st_tokens)
{
	ft_init_redi(st_redir, 2);
	if (st_tokens->token == T_RED_APP_S)
	{
		if (PREV && PREV->indx == st_tokens->indx && ft_isalldigit(PREV->value))
		{
			PREV->is_arg = 1;
			st_redir->fd_red = ft_atoi(PREV->value);
		}
		st_redir->fd_des = -2;
		st_redir->fd_file = st_tokens->next->value;
		st_tokens->next->is_arg = 1;
	}
	else if (st_tokens->token == T_RED_APP_A)
	{
		st_redir->fd_red = 1;
		st_redir->fd_err = 2;
		if (st_tokens->next && st_tokens->next->value &&
			ft_isallalphanum(st_tokens->next->value))
		{
			st_redir->fd_des = -2;
			st_redir->fd_file = st_tokens->next->value;
			st_tokens->next->is_arg = 1;
		}
	}
}

/*
** Redirection input <>	 :
*/

void	ft_redi_both(t_redir *st_redir, t_tokens *st_tokens)
{
	ft_init_redi(st_redir, 3);
	if (st_tokens->prev->indx == st_tokens->indx &&
		ft_isalldigit(st_tokens->prev->value))
	{
		st_tokens->prev->is_arg = 1;
		st_redir->fd_red = ft_atoi(st_tokens->prev->value);
	}
	st_redir->fd_des = -2;
	st_redir->fd_file = st_tokens->next->value;
	st_tokens->next->is_arg = 1;
}

/*
** Redirection : Here-doc :
*/

void	ft_redi_her(t_redir *st_redir, t_tokens *st_tokens)
{
	char *content;

	ft_init_redi(st_redir, 4);
	if (PREV != NULL && PREV->indx == st_tokens->indx &&
		ft_isallprint(PREV->value))
	{
		st_redir->fd_red = ft_atoi(PREV->value);
		PREV->is_arg = 1;
	}
	if (st_tokens->next != NULL && st_tokens->next->value &&
		ft_isallprint(st_tokens->next->value))
	{
		st_tokens->next->is_arg = 1;
		content = ft_read_heredoc(st_tokens->next->value);
		ft_strdel(&(st_tokens->next->value));
		st_tokens->next->value = content;
		st_redir->fd_file = content;
		st_redir->fd_des = -2;
	}
}
