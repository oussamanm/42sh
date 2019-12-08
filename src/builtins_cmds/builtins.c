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
	arr = ft_strsplit((line + j), '=');
	rm_alias_by_elem_flag(arr[0]);
	if (!arr[1])
		arr[1] = ft_strdup("");
	pushtolist(arr[0], arr[1], 1);
	ft_free2d(arr);
}
