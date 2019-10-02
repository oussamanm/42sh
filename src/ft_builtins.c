/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:34:51 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/03 04:16:23 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
**	Builten exit : free env , free readline, clear struct t_pipes
*/

void		ft_built_exit(t_pipes *st_pipes, char ***tmp_env)
{
	UNUSED(st_pipes);
	UNUSED(tmp_env);
	/// Clear environ globale and temp
 	//ft_strrdel(*env);
	ft_clear_readline_struct();
	//ft_clear_cmds(st_pipes);
	exit(0);
}
