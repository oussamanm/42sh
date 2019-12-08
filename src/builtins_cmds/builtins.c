/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:34:51 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/08 21:07:42 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

int			ft_exit_status(char **args)
{
	if (!args || !*args)
		return (0);
	if (*args && *(args + 1))
	{
		ft_putendl_fd("42sh: exit: too many arguments", 2);
		return (-1);
	}
	return (ft_atoi(*args));
}

/*
**	Builten exit : free env , free readline, clear struct t_pipes
*/

int			built_exit(char **args)
{
	int status;

	if ((status = ft_exit_status(args + 1)) == -1)
		return (EXIT_FAILURE);
	if (ft_check_stopped_job())
		return (EXIT_FAILURE);
	save_history(&g_history);
	exit(status);
}

/*
** - import alias content file to list;
*/

void		importaliasfilecontent_1(char *line)
{
	int		j;
	int		i;
	char	*str1;
	char	*str2;

	j = 0;
	while (line[j] && ft_isspace(line[j]))
		j++;
	i = j;
	while (line[j] && line[j] != '=')
		j++;
	str1 = ft_strsub(line, i, j - 1);
	str2 = ft_strsub(line, ++j, ft_strlen(line));
	rm_alias_by_elem_flag(str1);
	if (!str2)
		str2 = ft_strdup("");
	pushtolist(str1, str2, 1);
	ft_strdel(&str1);
	ft_strdel(&str2);
}
