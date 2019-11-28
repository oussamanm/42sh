/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 06:25:57 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/26 15:29:34 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include "../includes/read_line.h"
/*
** initail builtens : duplicate STD_* , Call builtens , Resete STD_*
*/

int			ft_init_built(t_pipes *st_pipes, char ***tmp_env)
{
	int i;
	int tmp[3];
	int status;

	i = -1;
	while (++i < 3)
		tmp[i] = dup(i);
	status = ft_call_built(st_pipes, tmp_env);
	i = -1;
	while (++i < 3)
		if (dup2(tmp[i], i) == -1 || close(tmp[i]) == -1)
			ft_putendl_fd("Error in dup or close \n", 2);
	// should add return status of builtens
	return (status);
}

/*
**  Call Builtens (close fds of redirection)
*/

int			ft_call_built(t_pipes *st_pipes, char ***tmp_env)
{
	int		rtn;
	int     status;

	rtn = 0;
	status = 0;
	if (st_pipes == NULL || st_pipes->args == NULL)
		return (-1);
	if (ft_check_redi(st_pipes) && parse_redir(st_pipes) == PARSE_KO)
		return (REDI_KO);
	if (ft_strcmp((st_pipes->args)[0], "exit") == 0)
		built_exit();
	if (ft_strcmp((st_pipes->args)[0], "env") == 0 && (rtn = 1))
		built_env(&(st_pipes->args)[1], tmp_env);
	else if (!ft_strcmp(st_pipes->args[0], "echo"))
/**/	built_echo(st_pipes->st_tokens);
	else if (ft_strcmp((st_pipes->args)[0], "alias") == 0 && (rtn = 1))
/**/	status = ft_buil_alias(st_pipes->st_tokens);
	else if (ft_strcmp((st_pipes->args)[0], "unalias") == 0 && (rtn = 1))
/**/	status = ft_buil_unalias(st_pipes->st_tokens);
	else if (ft_strcmp((st_pipes->args)[0], "export") == 0 && (rtn = 1))
/**/	built_export(st_pipes->st_tokens);
	else if (ft_strcmp((st_pipes->args)[0], "set") == 0 && (rtn = 1))
		built_set();
	else if (ft_strcmp((st_pipes->args)[0], "unset") == 0 && (rtn = 1))
		built_unset(&(st_pipes->args)[1]);
	else if (ft_strcmp((st_pipes->args)[0], "cd") == 0 && (rtn = 1))
		status = built_cd(&(st_pipes->args)[1], *tmp_env);
	else if (ft_strcmp((st_pipes->args)[0], "type") == 0 && (rtn = 1))
		status = built_type(&(st_pipes->args)[1], *tmp_env);
	else if (ft_strcmp((st_pipes->args)[0], "hash") == 0 && (rtn = 1))
		status = hash_table(&(st_pipes->args)[1]);
	else if (ft_strcmp((st_pipes->args)[0], "history") == 0 && (rtn = 1))
		display_his_list(g_history, 1);
	else if (ft_strcmp((st_pipes->args)[0], "fc") == 0 && (rtn = 1))
		fc_built(st_pipes->args + 1, &g_history);
	else if (ft_strcmp((st_pipes->args)[0], "source") == 0 && (rtn = 1))
		ft_buil_updatealias(&(st_pipes->args)[1]);
	else if (!ft_strcmp(st_pipes->args[0], "fg"))
		ft_foreground();
	else if (!ft_strcmp(st_pipes->args[0], "bg"))
		ft_continue();
	else if (!ft_strcmp(st_pipes->args[0], "jobs"))
		ft_jobs_built();
	while (st_pipes->st_redir != NULL)
	{
		if (st_pipes->st_redir->fd_des != -1)
			close(st_pipes->st_redir->fd_des);
		st_pipes->st_redir = st_pipes->st_redir->next;
	}
	return (rtn);
}

/*
**	Check if Command builtens
*/

int			ft_check_built(char *arg)
{
	int		rtn;

	rtn = 0;
	if (arg == NULL)
		return (-1);
	if (!ft_strcmp(arg, "exit") || !ft_strcmp(arg, "env"))
		rtn++;
	else if (!ft_strcmp(arg, "echo"))
		rtn++;
	else if (!ft_strcmp(arg, "export") || !ft_strcmp(arg, "unset") || !ft_strcmp(arg, "set"))
		rtn++;
	else if (!ft_strcmp(arg, "cd") || !ft_strcmp(arg, "type"))
		rtn++;
	else if (!ft_strcmp(arg, "alias") || !ft_strcmp(arg, "unalias"))
		rtn++;
	else if (!ft_strcmp(arg, "source") || !ft_strcmp(arg, "hash"))
		rtn++;
	else if (!ft_strcmp(arg, "history") || !ft_strcmp(arg, "fc"))
		rtn++;
	else if (!ft_strcmp(arg, "fg") || !ft_strcmp(arg, "bg") || !ft_strcmp(arg, "jobs"))
		rtn++;
	return (rtn);
}
