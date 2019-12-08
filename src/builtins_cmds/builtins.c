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

	ft_putendl("exit");
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
	char	**arr;

	arr = NULL;
	j = 0;
	while (line[j] && ft_isspace(line[j]))
		j++;
	//
	arr = ft_strsplit((line + j), '=');
	rm_alias_by_elem_flag(arr[0]);
	if (!arr[1])
		arr[1] = ft_strdup("");
	pushtolist(arr[0], arr[1], 1);
	ft_free2d(arr);
}
