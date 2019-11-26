/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:34:51 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/26 01:59:40 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
**	Builten exit : free env , free readline, clear struct t_pipes
*/

void		built_exit(t_pipes *st_pipes, char ***tmp_env)
{

	UNUSED(st_pipes);
	UNUSED(tmp_env);
	/// Clear environ globale and temp
 	//ft_strrdel(*env);
	// ft_clear_readline_struct();
	//free_list_cmds(st_pipes);
	// here free of hash and alias
	//ft_read_exit()??
	save_history(&g_history);
	free_hash_and_alias();
	exit(0);
}
