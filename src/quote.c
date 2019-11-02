/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 21:19:47 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/01 21:19:50 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	ft_remove_quot : Remove Quote from args :
*/

void			ft_remove_quot(char **args)
{
	int		j;
	int		i;
	char	*arg;

	if (args == NULL)
		return ;
	i = -1;
	while (args[++i] != NULL)
	{
		arg = args[i];
		j = -1;
		if ((arg[0] == '\'' || arg[0] == '"') && arg[ft_strlen(arg) - 1] == arg[0])
		{
			ft_strcpy(arg, &arg[1]);
			arg[ft_strlen(arg) - 1] = 0;
		}
	}
}


/*
**	ft_update_tokens : update token by remove quotes
*/

void			ft_update_tokens(t_tokens *st_tokens)
{
	char		*temp;
	t_tokens	*st_temp;

	st_temp = st_tokens;
	while (st_temp)
	{
		if (st_temp->token == T_QUO || st_temp->token == T_DQUO)
		{
			temp = ft_strsub(st_temp->value, 1, ft_strlen(st_temp->value) - 2);
			ft_strdel(&(st_temp->value));
			st_temp->value = temp;
		}
		st_temp = st_temp->next;
	}
}
