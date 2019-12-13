/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 21:02:13 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/02 06:55:46 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
** Change all Remplaced tokens (value of expansion) to Token_text
*/

void		iniatial_expans_tokens(t_tokens *st_tokens)
{
	if (!st_tokens)
		return ;
	while (st_tokens)
	{
		if (!M_CHECK(st_tokens->token, T_QUO, T_DQUO))
			st_tokens->token = T_TXT;
		st_tokens = NEXT;
	}
}

/*
** Correct indexs of Remplaced Tokens
*/

void		correct_index_tokens(int index, t_tokens *st_tokens)
{
	if (!st_tokens)
		return ;
	while (st_tokens)
	{
		if (st_tokens->indx == 0)
			st_tokens->indx = index;
		else
			st_tokens->indx *= -1;
		st_tokens = st_tokens->next;
	}
}

/*
** Change value of a token (st_remp) to tokens and join theme with princ_Tokens
*/

t_tokens	*linking_tokens(t_tokens *st_remp, t_tokens *st_tokens,
	t_tokens **st_head)
{
	t_tokens	*st_next;
	t_tokens	*st_prev;
	t_tokens	*last_token;

	if (!st_remp || !st_tokens)
		return (NULL);
	st_prev = st_remp->prev;
	st_next = st_remp->next;
	last_token = get_last_token(st_tokens);
	if (st_prev == NULL)
		*st_head = st_tokens;
	else
	{
		st_prev->next = st_tokens;
		st_tokens->prev = st_prev;
	}
	ft_strdel(&st_remp->value);
	free(st_remp);
	(st_next) ? (st_next->prev = last_token) : 0;
	(last_token) ? (last_token->next = st_next) : 0;
	return (last_token);
}

/*
** Change value to tokens and join them with princ_Tokens
*/

t_tokens	*handle_value_expans(char *value, t_tokens *st_token,
	t_tokens **st_head)
{
	t_tokens	*st_tokens;
	t_tokens	*last_token;
	char		**args;

	if (!value || !st_token)
		return (st_token);
	args = ft_str_split_q(value, " \t\n");
	st_tokens = ft_lexer(args);
	ft_strrdel(args);
	if (!st_tokens)
		return (st_token);
	correct_index_tokens(st_token->indx, st_tokens);
	iniatial_expans_tokens(st_tokens);
	last_token = linking_tokens(st_token, st_tokens, st_head);
	return (last_token);
}

/*
** Change expansions with his value
*/

void		handle_expansions(t_tokens **st_tokens)
{
	char		*temp;
	t_tokens	*tokens;

	if (!st_tokens)
		return ;
	temp = NULL;
	tokens = *st_tokens;
	while (tokens)
	{
		if (tokens->token == T_TXT || tokens->token == T_DQUO)
		{
			temp = ft_strdup(tokens->value);
			tokens->value = ft_corr_args(tokens->value);
			if (!ft_strequ(temp, tokens->value))
				tokens = handle_value_expans(tokens->value, tokens,
					st_tokens);
			ft_strdel(&temp);
		}
		tokens = (tokens) ? tokens->next : NULL;
	}
}
