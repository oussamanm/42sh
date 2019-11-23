/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_srcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:55:28 by mfilahi           #+#    #+#             */
/*   Updated: 2019/11/23 15:55:42 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** - print error message related to unalias options;
*/

int		alias_invalid_option(char *str)
{
	print_error("invalid option ", "unalias: ", str, 0);
	print_error("[-a] [name[=value] ... ]", NULL, "unalias: usage: ", 0);
	return (1);
}

/*
** - handle qoutes for matched alias;
*/

char	*handleqoutes(char *str)
{
	char	*tmp;
	int		i;
	int		j;
	int		a;

	if (str[0] != '\'' && str[0] != '"')
		return (str);
	else
	{
		j = 0;
		while (str[j] && (str[j] == '\'' || str[j] == '"'))
			j++;
		a = str[j - 1];
		i = j - 1;
		while (str[++i] && str[i] != a)
			;
	}
	tmp = str;
	str = ft_strsub(str, j, i - j);
	ft_strdel(&tmp);
	return (str);
}