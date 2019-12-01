/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:09:00 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/21 19:09:05 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Correct token by remove all arg of T_EQUAL : variable = value
*/

void		correct_tokens(t_pipes *st_pipes)
{
	t_tokens	*st_tokens;
	t_tokens	*head;

	if (!st_pipes || !st_pipes->st_tokens)
		return ;
	st_tokens = st_pipes->st_tokens;
	head = st_tokens;
	while (st_tokens && (st_tokens->is_arg == T_EQUAL || st_tokens->token == T_EQUAL))
	{
		st_tokens = NEXT;
		free(head);
		head = st_tokens;
	}
	st_pipes->st_tokens = head;
}

/*
** Remove escaped_character from cmd befor execution
*/

void		remove_backslashs(t_tokens *st_tokens)
{
	int		index;
	char	*arg;
	int		i;

	while (st_tokens)
	{
		if (st_tokens->token == T_TXT || st_tokens->token == T_DQUO)
		{
			arg = st_tokens->value;
			i = -1;
			while (arg[++i] && (index = ft_find_char(&arg[i], '\\')) != -1)
			{
				i += index;
				if (st_tokens->token == T_DQUO && M_SPEC_CHARC(arg[i + 1]))
					ft_strcpy(&arg[i],&arg[i + 1]);
				else if (st_tokens->token == T_TXT)
					ft_strcpy(&arg[i],&arg[i + 1]);
			}
		}
		//ft_all_quot(arg))
		st_tokens = NEXT;
	}
}

/*
**	Function set is_arg variable in list tokens : (is argument of T_EQUAL)
*/

void		set_isarg(t_pipes *st_pipes)
{
	t_tokens *st_tokens;
	int i;

	st_tokens = st_pipes->st_tokens;
	i = st_tokens->indx - 1;
	while (st_tokens)
	{
		if (st_tokens->indx == i)
			st_tokens = st_tokens->next;
		else
		{
			i++;
			if (!ft_is_equal(i, st_tokens))
				break;
			if (!valid_identifier(st_tokens->value))
				return ;
			st_tokens->is_arg = T_EQUAL;
			if (NEXT && NEXT->next && NEXT->next->indx == st_tokens->indx)
				NEXT->next->is_arg = T_EQUAL;
		}
	}
}