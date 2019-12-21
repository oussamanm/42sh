/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_opr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:05:28 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/02 12:43:46 by mfetoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"



/*
** Execute Logical Operateur
*/

static void		apply_logic(t_logopr **st_logopr, int state)
{
	int		cmp;

	if (((*st_logopr)->status == T_LOGOPR_OR && state == 0) ||
			((*st_logopr)->status == T_LOGOPR_AND && state == 1))
		*st_logopr = (*st_logopr)->next;
	else
	{
		cmp = (*st_logopr)->status;
		*st_logopr = (*st_logopr)->next;
		while (*st_logopr != NULL)
		{
			if ((*st_logopr)->status != cmp)
			{
				*st_logopr = (*st_logopr)->next;
				break ;
			}
			*st_logopr = (*st_logopr)->next;
		}
	}
}

void			logical_ops(t_logopr *st_logopr)
{
	int		state;

	state = -1;
	while (st_logopr != NULL)
	{
		if (error_redir(st_logopr->st_tokens))
			state = 1;
		else
			state = ft_pipe(st_logopr->st_pipes);
		g_exit_status = state;
		state = (state) ? 0 : 1;
		apply_logic(&st_logopr, state);
	}
}
