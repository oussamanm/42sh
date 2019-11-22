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
** Remove escaped_character from cmd befor execution
*/

void			remove_backslashs(char **args)
{
	int		index;
	char	*arg;
	int		i;
	int		quoted;

	while (args && *args)
	{
		arg = *args;
		i = -1;
		quoted = 0;
		if (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'')
		{
			args++;
			continue ;
		}
		else if (arg[0] == '"' && arg[ft_strlen(arg) - 1] == '"')
			quoted = 1;
		while (arg[++i] && (index = ft_find_char(&arg[i], '\\')) != -1)
		{
			i += index;
			if (quoted && M_SPEC_CHARC(arg[i + 1]))
				ft_strcpy(&arg[i],&arg[i + 1]);
			else if (!quoted)
				ft_strcpy(&arg[i],&arg[i + 1]);
		}
		if (i > 1 && ft_all_quot(arg))
		{
			*args = ft_strnew(ft_strlen(arg) + 2);
			(*args)[0] = '"';
			ft_strcpy(&(*args)[1], arg);
			(*args)[ft_strlen(*args)] = '"';
		}
		args++;
	}
}
