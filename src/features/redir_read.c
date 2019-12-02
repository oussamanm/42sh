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
** Redirection output >	 @
*/

void	ft_redi_out(t_redir *st_redir, t_tokens *st_tokens)
{
	ft_init_redi(st_redir, 1);
	if (st_tokens->token == T_RED_OUT_S)
	{
		if (SAME_ARG(PREV, st_tokens) && PREV->token == T_TXT)
		{
			PREV->is_arg = 1;
			st_redir->fd_red = ft_atoi(PREV->value);
		}
		st_redir->fd_des = -2;
		st_redir->fd_file = get_value_next(NEXT);
	}
	else if (st_tokens->token == T_RED_OUT_A)
		ft_redi_out_h(st_redir, st_tokens);
	else if (st_tokens->token == T_RED_OUT_B)
	{
		if (SAME_ARG(PREV, st_tokens))
		{
			PREV->is_arg = 1;
			st_redir->fd_close = ft_atoi(PREV->value);
		}
		else
			st_redir->fd_close = 1;
	}
}

/*
** Redirection input <	 @
*/

void	ft_redi_in(t_redir *st_redir, t_tokens *st_tokens)
{
	char *temp;

	ft_init_redi(st_redir, 0);
	if (st_tokens->token == T_RED_IN_S)
	{
		if (SAME_ARG(PREV, st_tokens) && (PREV->is_arg = 1))
			st_redir->fd_red = ft_atoi(PREV->value);
		st_redir->fd_des = -2;
		st_redir->fd_file = get_value_next(NEXT);
	}
	else if (st_tokens->token == T_RED_IN_A)
	{
		if (SAME_ARG(PREV, st_tokens) && (PREV->is_arg = 1))
			st_redir->fd_red = ft_atoi(PREV->value);
		temp = get_value_next(NEXT);
		st_redir->fd_des = ft_atoi(temp);
		free(temp);
	}
	else if (st_tokens->token == T_RED_IN_B)
	{
		if (SAME_ARG(PREV, st_tokens) && (PREV->is_arg = 1))
			st_redir->fd_close = ft_atoi(PREV->value);
	}
}

/*
** Redirection append >> @
*/

void	ft_redi_app(t_redir *st_redir, t_tokens *st_tokens)
{
	char *temp;

	ft_init_redi(st_redir, 2);
	temp = get_value_next(NEXT);
	if (st_tokens->token == T_RED_APP_S)
	{
		if (SAME_ARG(PREV, st_tokens))
		{
			PREV->is_arg = 1;
			st_redir->fd_red = ft_atoi(PREV->value);
		}
		st_redir->fd_des = -2;
		st_redir->fd_file = temp;
	}
	else if (st_tokens->token == T_RED_APP_A)
	{
		st_redir->fd_red = 1;
		st_redir->fd_err = 2;
		if (NEXT && NEXT->value &&
			ft_isallalphanum(temp))
		{
			st_redir->fd_des = -2;
			st_redir->fd_file = temp;
		}
	}
}

/*
** Redirection input <>	 @
*/

void	ft_redi_both(t_redir *st_redir, t_tokens *st_tokens)
{
	ft_init_redi(st_redir, 3);
	if (SAME_ARG(PREV, st_tokens))
	{
		st_tokens->prev->is_arg = 1;
		st_redir->fd_red = ft_atoi(PREV->value);
	}
	st_redir->fd_des = -2;
	st_redir->fd_file = get_value_next(NEXT);
}

/*
** Redirection : Here-doc @
*/

void	ft_redi_her(t_redir *st_redir, t_tokens *st_tokens)
{
	char *content;
	char *temp;

	temp = NULL;
	ft_init_redi(st_redir, 4);
	if (PREV && PREV->indx == st_tokens->indx && ft_isallprint(PREV->value))
	{
		st_redir->fd_red = ft_atoi(PREV->value);
		PREV->is_arg = 1;
	}
	if (NEXT && NEXT->value && ft_isallprint(NEXT->value))
	{
		temp = get_value_next(NEXT);
		content = ft_read_heredoc(temp);
		st_redir->fd_file = content;
		st_redir->fd_des = -2;
		free(temp);
	}
}
