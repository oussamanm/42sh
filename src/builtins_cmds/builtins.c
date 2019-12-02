/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:34:51 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/01 23:03:08 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
**	Builten exit : free env , free readline, clear struct t_pipes
*/

void		built_exit(void)
{
	save_history(&g_history);
	exit(0);
}

/*
** - this func work with cd_built
*/

char		*ft_correctpath(char *path, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] &&\
			str[i] == '.' &&\
			str[i + 1] == '.' &&\
			str[i + 2] == '/')
	{
		i += 3;
	}
	if (str[i] && str[i] != '/' && str[i + 1] != '.')
	{
		tmp = str;
		path = ft_strjoir(path, ft_strjoir("/", str + i, 0), 1);
		ft_strdel(&tmp);
	}
	else if ((!str[i] && (ft_strcmp(path, "") == 0)) ||\
	(str[i] == '.' && str[i + 1] == '.' && !str[i + 2] &&\
	(ft_strcmp(path, "") == 0)))
		path = ft_strjoir("/", path, 2);
	return (path);
}

/*
** - import alias content file to list;
*/

void		importaliasfilecontent_1(char *line, char *tmp, int j)
{
	int	i;

	while (line[j] && ft_isspace(line[j]))
		j++;
	i = j;
	while (line[i] && line[i] != '=')
		i++;
	if (line[i] == '=')
	{
		tmp = ft_strsub(line, j, i);
		rm_alias_by_elem_flag(tmp, 0, 0);
		pushtolist(line + j, 1);
		ft_strdel(&tmp);
	}
	(line) ? ft_strdel(&line) : 0;
}
