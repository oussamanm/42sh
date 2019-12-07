/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 21:54:58 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/07 21:55:00 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** trait special case: echo $(<file)
*/

void		spec_case_subshell(char **arg)
{
	t_tokens	*st_tokens;
	t_tokens	*st_head;
	t_tokens	*st_temp;

	if (ft_strlen(*arg) == 0)
		return ;
	st_tokens = ft_new_token();
	st_head = st_tokens;
	args_to_token(&st_head, *arg, 0);
	if (!st_tokens)
		return ;
	if (st_tokens->token == T_RED_IN_S && NEXT &&
		(T_IS_TXT(NEXT->token) || NEXT->token == T_SUBSHL))
	{
		st_temp = NEXT->next;
		while (st_temp && st_temp->indx == NEXT->indx &&
			T_IS_TXT(st_temp->token))
			st_temp = st_temp->next;
		if (st_temp && st_temp->value && st_temp != NEXT->next)
			return ;
		else
			*arg = ft_strjoir("cat ", *arg, 2);
	}
	free_tokens(st_tokens, 1);
}
