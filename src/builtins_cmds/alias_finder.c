/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_finder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 20:43:06 by mfilahi           #+#    #+#             */
/*   Updated: 2019/12/08 20:43:11 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		iniatail_alias_tokens(t_tokens *st_tokens, int bl)
{
	if (!st_tokens)
		return ;
	while (st_tokens)
	{
		st_tokens->aliased = bl;
		st_tokens = NEXT;
	}
}

char		*get_value_alias(char *key)
{
	t_aliaspkg	*data;
	t_alias		*curr;
	char		*rtn;

	if (!(data = storeaddrstruct(NULL)))
		return (NULL);
	if (!(curr = data->head_ref))
		return (NULL);
	rtn = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->shortcut, key) == 0)
		{
			rtn = curr->cmd;
			break ;
		}
		curr = curr->next;
	}
	return (rtn);
}

/*
** change value of alias to tokens and join it to main_list_tokens
*/

t_tokens	*handle_value_alias(char *value, t_tokens *st_tokens,
	t_tokens **st_head)
{
	t_tokens	*st_token;
	char		**args;

	if (!value || !st_tokens)
		return (st_tokens);
	args = ft_str_split_q(value, " \t\n");
	st_token = ft_lexer(args);
	iniatail_alias_tokens(st_token, 0);
	ft_strrdel(args);
	if (!st_token)
		return (st_tokens);
	linking_tokens(st_tokens, st_token, st_head);
	return (st_token);
}

/*
** Check if alias should change to his value
*/

int			check_alias(t_tokens **st_tokens, t_tokens **st_head,
	t_list **st_list)
{
	char	*value;

	if ((value = get_value_alias((*st_tokens)->value)) &&
		ft_lstfind(*st_list, (*st_tokens)->value) == 0)
	{
		ft_lstadd(st_list, ft_lstnew((*st_tokens)->value,
			ft_strlen((*st_tokens)->value) + 1));
		(*st_tokens) = handle_value_alias(value, (*st_tokens), st_head);
		return (1);
	}
	return (0);
}

/*
** Handler of aliases , change alias with value
*/

void		handle_alias(t_tokens **st_head)
{
	t_tokens	*st_tokens;
	int			bl;
	t_list		*st_list;

	st_tokens = *st_head;
	st_list = NULL;
	bl = 0;
	iniatail_alias_tokens(*st_head, 1);
	while (st_tokens)
	{
		if (st_tokens->aliased == 1)
		{
			ft_lst_free(&st_list);
			st_list = ft_lstnew(NULL, 0);
		}
		if (st_tokens == *st_head && TOKEN == T_TXT)
			bl = 1;
		else if ((OPER_TOKEN(TOKEN) || TOKEN == T_SEMICLN) && NEXT &&
			NEXT->token == T_TXT && (bl = 2))
			st_tokens = NEXT;
		if (bl && (bl = check_alias(&st_tokens, st_head, &st_list)) == 1)
			continue ;
		st_tokens = (st_tokens) ? NEXT : st_tokens;
	}
	ft_lst_free(&st_list);
}
