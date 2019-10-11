/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_h.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 02:18:45 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/06 02:18:46 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


/*
** Fill t_tokens :
*/

void		ft_fill_token(t_tokens **st_tokens, int token,
	char *value, int indx)
{
	t_tokens	*prev;

	(*st_tokens)->token = token;
	(*st_tokens)->value = value;
	(*st_tokens)->indx = indx;
	(*st_tokens)->next = ft_new_token();
	prev = (*st_tokens);
	(*st_tokens) = (*st_tokens)->next;
	(*st_tokens)->prev = prev;
}

/*
**  append - to redirection if separated :
*/

void		ft_upd_token(t_tokens *st_tokens, int token, char *value)
{
	if (st_tokens == NULL)
		return ;
	st_tokens->token = token;
	if (st_tokens->value != NULL)
		ft_strdel(&(st_tokens->value));
	st_tokens->value = ft_strdup(value);
}


/*
** Duplicate token and alloc next if exist
*/

void		ft_dup_token(t_tokens **st_token, t_tokens *st_src, int token)
{
	t_tokens *st_temp;

	st_temp = NULL;
	if (!st_token || !st_src)
		return ;
	(*st_token)->token = st_src->token;
	(*st_token)->value = st_src->value;
	(*st_token)->indx = st_src->indx;
	(*st_token)->is_arg = st_src->is_arg;
	if (st_src->next && st_src->next->token != token)
	{
		if (M_CHECK(token, T_LOGOPR_AND, T_LOGOPR_AND) &&
			M_CHECK(st_src->next->token, T_LOGOPR_AND, T_LOGOPR_OR))
			return ;
		(*st_token)->next = ft_new_token();
		st_temp = *st_token;
		*st_token = (*st_token)->next;
		(*st_token)->prev = st_temp;
	}
}

/*
** Convert Tokens to args
*/

void		ft_tokens_args(t_pipes *st_pipe)
{
	t_tokens	*st_tokens;
	int			len;
	int			i;

	if (!st_pipe)
		return ;
	i = 0;
	st_tokens = st_pipe->st_tokens;
	len = ft_count_tokens(st_pipe->st_tokens);
	st_pipe->args = ft_strr_new(len);
	while (st_tokens)
	{
		if (st_tokens->is_arg != T_EQUAL)
		{
			st_pipe->args[i++] = ft_strdup(st_tokens->value);
		}
		st_tokens = st_tokens->next;
	}
}

/*
** Count tokens
*/

int			ft_count_tokens(t_tokens *st_tokens)
{
	int		rtn;

	rtn = 0;
	if (!st_tokens)
		return (0);
	while (st_tokens)
	{
		rtn++;
		st_tokens = st_tokens->next;
	}
	return (rtn);
}

/*
** Check if exist token in list tokens
*/

int			ft_check_token(t_tokens *st_tokens, int token)
{
	if (!st_tokens)
		return (0);
	while (st_tokens)
	{
		if (st_tokens->token == token)
			return (1);
		st_tokens = st_tokens->next;
	}
	return (0);
}
