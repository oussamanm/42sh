/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_srcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:55:28 by mfilahi           #+#    #+#             */
/*   Updated: 2019/12/07 04:22:21 by mfilahi          ###   ########.fr       */
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
	return (EXIT_FAILURE);
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

/*
** - free 2d array;
*/

void	ft_free2d(char **p)
{
	int	i;

	i = 0;
	while (p[i])
		ft_strdel(&p[i++]);
	free(p);
	p = NULL;
}

/*
** - import content from file .42shrc to list
** we can do that with this cmd : source .42shrc.
*/

void	ft_buil_updatealias(char **args)
{
	if (!(ft_strcmp(*args, ".42shrc") == 0))
		print_error("No such file or directory", NULL, *args, 0);
	else
	{
		freealiaslist();
		importaliasfilecontent(NULL);
	}
}
