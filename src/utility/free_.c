/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 04:19:32 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/02 04:19:34 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	 free struct t_redir
*/

void		free_list_redir(t_redir *st_redir)
{
	t_redir	*temp;

	while (st_redir)
	{
		temp = st_redir->next;
		/// free file variable
		ft_strdel(&st_redir->fd_file);
		free(st_redir);
		st_redir = temp;
	}
}


void		free_tokens(t_tokens *st_tokens, int free_content)
{
	t_tokens *st_temp;

	if (!st_tokens)
		return ;
	while (st_tokens)
	{
		st_temp = st_tokens;
		if (free_content)
			ft_strdel(&(st_tokens->value));
		st_tokens = st_tokens->next;
		free(st_temp);
	}
}

/*
**	Free table of addresses
*/

void		free_addresses(void *table[MAX_TAB_ADDR])
{
	int i;

	if (!table)
		return ;
	i = 0;
	while (table[i])
	{
		ft_strdel(table[i]);
		i++;
	}
}
