/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:34:51 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/19 19:08:29 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
** Get state
*/

int		get_state(int status)
{
	if (status > 255)
		return (status / 256);
	else if (status > 0 && status < 32)
		return (status + 128);
	else if (status)
		return (1);
	else
		return (0);
}

int			ft_exit_status(char **args)
{
	int i;

	i = -1;
	if (!args[0])
		return (0);
	while (args[0][++i])
		if (!ft_isdigit(args[0][i]))
			return (-1);
	if (*args && *(args + 1))
	{
		ft_putendl_fd("42sh: exit: too many arguments", 2);
		return (-22);
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
		print_error("numeric argument required", "exit : ", args[1], 0);
	if (status == -22 || ft_check_stopped_job())
		return (EXIT_FAILURE);
	ft_putendl_fd("exit", 1);
	save_history(&g_history);
	free_hash_and_alias();
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
