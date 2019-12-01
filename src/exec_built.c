/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 06:25:57 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/28 23:35:36 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include "../includes/read_line.h"
/*
** initail builtens : duplicate STD_* , Call builtens , Resete STD_*
*/

int			ft_init_built(t_pipes *st_pipes, int fork_it, char ***tmp_env)
{
	int i;
	int tmp[3];
	int status;
	int	pid;

	i = -1;
	fork_it = (fork_it && st_pipes->bl_jobctr == 1) ? 1 : 0;
	pid = 0;
	/// Save a copy of default_FileDisc
	if (!fork_it)
		while (++i < 3)
			if ((tmp[i] = dup(i)) == -1)
				ft_putendl_fd("Error in dup, in builtens \n", 2);
	/// Fork in case of built and job_contr (no pipe)
	if (fork_it && ((pid = fork()) == -1))
		ft_err_exit("Error in Fork new process \n");
	if (pid > 0 && fork_it && !g_proc_sub)
		ft_manage_jobs(pid, st_pipes, &status);
	if (pid == 0)
	{
		status = ft_call_built(st_pipes, tmp_env);
		if (fork_it)
			exit((status) ? EXIT_FAILURE : EXIT_SUCCESS);
	}
	else if (fork_it && g_proc_sub && !st_pipes->bl_jobctr)
		waitpid(pid, &status, 0);
	i = -1;
	/// restore default_FileDisc
	if (!fork_it)
		while (++i < 3)
			if (dup2(tmp[i], i) == -1 || close(tmp[i]) == -1)
				ft_putendl_fd("Error in dup or close in builtens \n", 2);
	return (status);
}

/*
**  Call Builtens (close fds of redirection)
*/

int			ft_call_built(t_pipes *st_pipes, char ***tmp_env)
{
	int     status;

	status = 0;
	if (st_pipes == NULL || !st_pipes->args || !(*st_pipes->args))
		return (-1);
	/// Apply redirection 
	if (ft_check_redi(st_pipes) && parse_redir(st_pipes) == PARSE_KO)
		return (REDI_KO);

	if (STR_CMP(*(st_pipes->args), "exit"))
		built_exit();
	else if (STR_CMP(*(st_pipes->args), "echo"))
/**/	status = built_echo(st_pipes->st_tokens);
	else if (STR_CMP(*(st_pipes->args), "alias"))
/**/	status = ft_buil_alias(st_pipes->st_tokens);
	else if (STR_CMP(*(st_pipes->args), "unalias"))
/**/	status = ft_buil_unalias(st_pipes->st_tokens);
	else if (STR_CMP(*(st_pipes->args), "export"))
/**/	built_export(st_pipes->st_tokens);
	else if (STR_CMP(*(st_pipes->args), "set"))
		built_set();
	else if (STR_CMP(*(st_pipes->args), "unset"))
		built_unset(st_pipes->args + 1);
	else if (STR_CMP(*(st_pipes->args), "cd"))
		status = built_cd(st_pipes->args + 1, *tmp_env);
	else if (STR_CMP(*(st_pipes->args), "type"))
		status = built_type(st_pipes->args + 1, *tmp_env);
	else if (STR_CMP(*(st_pipes->args), "hash"))
		status = hash_table(st_pipes->args + 1);
	else if (STR_CMP(*(st_pipes->args), "history"))
		display_his_list(g_history, 1);
	else if (STR_CMP(*(st_pipes->args), "fc"))
		fc_built(st_pipes->args + 1, &g_history);
	else if (STR_CMP(*(st_pipes->args), "source"))
		ft_buil_updatealias(st_pipes->args + 1);
	else if (STR_CMP(*(st_pipes->args), "fg"))
		ft_foreground((st_pipes->args)[1]);
	else if (STR_CMP(*(st_pipes->args), "bg"))
		ft_continue((st_pipes->args)[1]);
	else if (STR_CMP(*(st_pipes->args), "jobs"))
		ft_jobs_built(st_pipes->args);
	/// close file discriptor used by builtens
	while (st_pipes->st_redir != NULL)
	{
		if (st_pipes->st_redir->fd_des != -1)
			close(st_pipes->st_redir->fd_des);
		st_pipes->st_redir = st_pipes->st_redir->next;
	}
	return (status);
}

/*
**	Check if Command builtens
*/

int			ft_check_built(char *arg)
{
	if (arg == NULL)
		return (-1);
	if (!ft_strcmp(arg, "exit") || !ft_strcmp(arg, "echo"))
		return (1);
	else if (!ft_strcmp(arg, "export"))
		return (1);
	else if (!ft_strcmp(arg, "unset") || !ft_strcmp(arg, "set"))
		return (1);
	else if (!ft_strcmp(arg, "cd") || !ft_strcmp(arg, "type"))
		return (1);
	else if (!ft_strcmp(arg, "alias") || !ft_strcmp(arg, "unalias"))
		return (1);
	else if (!ft_strcmp(arg, "source") || !ft_strcmp(arg, "hash"))
		return (1);
	else if (!ft_strcmp(arg, "history") || !ft_strcmp(arg, "fc"))
		return (1);
	else if (!ft_strcmp(arg, "fg") || !ft_strcmp(arg, "bg") || !ft_strcmp(arg, "jobs"))
		return (1);
	return (0);
}
