/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_opr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:05:28 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/21 19:05:31 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Get state
*/

int			get_state(int status)
{
	if (status == 32512)
		return (127);
	else if (status == 2)
		return (130);
	else if (status)
		return (1);
	else
		return (0);
}

/*
 ** Execute Logical Operateur
 */

void		logical_ops(t_logopr *st_logopr)
{
	int		cmp;
	int		state;

	state = -1;
	while (st_logopr != NULL)
	{
		if (error_redir(st_logopr->st_tokens))
			state = 1;
		else
			state = ft_pipe(st_logopr->st_pipes);
		g_exit_status = get_state(state);
		state = (state) ? 0 : 1;
		if ((st_logopr->status == T_LOGOPR_OR && state == 0) ||
				(st_logopr->status == T_LOGOPR_AND && state == 1))
			st_logopr = st_logopr->next;
		else
		{
			cmp = st_logopr->status;
			st_logopr = st_logopr->next;
			while (st_logopr != NULL)
			{
				if (st_logopr->status != cmp)
				{
					st_logopr = st_logopr->next;
					break;
				}
				st_logopr = st_logopr->next;
			}
		}
	}
}
