/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 19:26:08 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/07 18:03:20 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	 Clear struct t_tokens
*/

void		ft_clear_tokens(t_tokens *st_tokens)
{
	t_tokens *st_temp;

	if (!st_tokens)
		return ;
	while (st_tokens)
	{
		st_temp = st_tokens;
		ft_strdel(&(st_tokens->value));
		st_tokens = st_tokens->next;
		(st_temp != NULL) ? free(st_temp) : NULL;
	}
}

/*
**	 Clear struct t_pipes
*/

void		ft_clear_cmds(t_pipes *st_pipes)
{
	t_pipes *st_temp;
	t_redir	*st_red;

	while (st_pipes)
	{
		st_temp = st_pipes;
		if (st_pipes->st_redir)
		{
			st_red = st_pipes->st_redir;
			while (st_red)
			{
				if (st_red)
					free(st_red);
				st_red = st_red->next;
			}
		}
		ft_strrdel(st_pipes->args);
		ft_strdel(&(st_pipes->cmd));
		ft_clear_tokens(st_pipes->st_tokens);
		st_pipes = st_pipes->next;
		free(st_temp);
	}
}
