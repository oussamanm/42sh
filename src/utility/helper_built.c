/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 03:35:59 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/02 03:36:05 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
**	call builtens
*/

int			builtens_mini(t_pipes *st_pipes, char ***tmp_env)
{
	int		status;

	status = 0;
	if (STR_CMP(*(st_pipes->args), "exit"))
		status = built_exit(st_pipes->args);
	else if (STR_CMP(*(st_pipes->args), "echo"))
		status = built_echo(st_pipes->st_tokens);
	else if (STR_CMP(*(st_pipes->args), "alias"))
		status = ft_buil_alias(st_pipes->st_tokens);
	else if (STR_CMP(*(st_pipes->args), "unalias"))
		status = ft_buil_unalias(st_pipes->st_tokens);
	else if (STR_CMP(*(st_pipes->args), "export"))
		status = built_export(st_pipes->st_tokens);
	else if (STR_CMP(*(st_pipes->args), "set"))
		built_set(g_intern, st_pipes->args + 1);
	else if (STR_CMP(*(st_pipes->args), "unset"))
		status = built_unset(st_pipes->args + 1);
	else if (STR_CMP(*(st_pipes->args), "cd"))
		status = built_cd(st_pipes->args + 1, *tmp_env);
	else
		return (-1);
	return (status);
}

int			builtens_shell(t_pipes *st_pipes, char ***tmp_env)
{
	int status;

	status = 0;
	if (STR_CMP(*(st_pipes->args), "type"))
		status = built_type(st_pipes->args + 1, *tmp_env);
	else if (STR_CMP(*(st_pipes->args), "hash"))
		status = hash_table(st_pipes->args + 1);
	else if (STR_CMP(*(st_pipes->args), "history"))
		display_his_list(g_history, 1);
	else if (STR_CMP(*(st_pipes->args), "fc"))
		fc_built(st_pipes->args + 1, &g_history, *tmp_env);
	else if (STR_CMP(*(st_pipes->args), "source"))
		ft_buil_updatealias(st_pipes->args + 1);
	else if (STR_CMP(*(st_pipes->args), "fg"))
		ft_foreground((st_pipes->args)[1]);
	else if (STR_CMP(*(st_pipes->args), "bg"))
		ft_continue((st_pipes->args)[1]);
	else if (STR_CMP(*(st_pipes->args), "jobs"))
		ft_jobs_built(st_pipes->args);
	return (status);
}
