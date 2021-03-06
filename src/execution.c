/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:42:10 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/10 20:40:35 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
** Execute all cmds
*/

static void		ft_cmds_exec(t_cmds *st_cmds)
{
	t_jobctr	*st_jobctr;

	if (!st_cmds)
		return ;
	st_jobctr = st_cmds->st_jobctr;
	while (st_jobctr)
	{
		logical_ops(st_jobctr->st_logopr);
		st_jobctr = st_jobctr->next;
	}
}

/*
** Execute of Cmd
*/

static void		ft_cmd_exec(char *str_cmd, char **args, char **env)
{
	int		status;

	status = 0;
	if (!args || !args[0])
		exit(EXIT_SUCCESS);
	if (!(status = ft_check_cmd(str_cmd, args)))
	{
		execve(str_cmd, args, env);
		status = EXIT_FAILURE;
	}
	exit(status);
}

/*
** Handle child process by , call redirection and call function execution
*/

void			ft_handle_child(t_pipes *st_pipes, char **environ)
{
	char *str_cmd;

	str_cmd = NULL;
	ft_signal_default();
	if (g_proc_sub && st_pipes->bl_jobctr)
	{
		dup2(open("/dev/null", O_RDONLY), 0);
		if (g_proc_sub == 1)
			signal(SIGINT, SIG_IGN);
	}
	if (ft_check_redi(st_pipes) && parse_redir(st_pipes) == PARSE_KO)
		exit(EXIT_FAILURE);
	if (ft_check_char((st_pipes->args)[0], '/'))
		str_cmd = (st_pipes->args)[0];
	else if (!st_pipes->tmp_env)
	{
		if (!(str_cmd = lookup_hash(st_pipes->args[0])))
			str_cmd = ft_find_path((st_pipes->args)[0], environ);
	}
	else
		str_cmd = ft_find_path((st_pipes->args)[0], environ);
	ft_cmd_exec(str_cmd, st_pipes->args, environ);
}

/*
** Create child proc, check built, call for apply redirect , Execution
*/

int				ft_cmd_fork(int fork_it, t_pipes *st_pipes)
{
	int		pid;
	int		rtn;
	char	**environ;

	pid = 0;
	rtn = 0;
	if (!st_pipes || !st_pipes->st_tokens)
		return (0);
	remove_backslashs(st_pipes->st_tokens);
	tokens_to_args(st_pipes);
	environ = (st_pipes->tmp_env) ? st_pipes->tmp_env : g_environ;
	if (st_pipes->args && ft_check_built(*(st_pipes->args)))
		return (ft_init_built(st_pipes, fork_it, &environ));
	(fork_it) ? signal(SIGCHLD, SIG_DFL) : 0;
	(fork_it && (pid = fork()) == -1) ? ft_err_exit(ERR_FORK) : 0;
	if (pid > 0 && fork_it && !g_proc_sub)
		ft_manage_jobs(pid, st_pipes, &rtn);
	if (pid == 0)
		ft_handle_child(st_pipes, environ);
	else if (fork_it && g_proc_sub && !st_pipes->bl_jobctr)
		waitpid(pid, &rtn, 0);
	(fork_it) ? signal(SIGCHLD, ft_catch_sigchild) : 0;
	if (rtn != EXIT_CMD_NF && st_pipes->args)
		insert_hash(*st_pipes->args, ft_find_path(*st_pipes->args, environ));
	return (rtn);
}

/*
** Config Cmds by : sub_shell - her_doc - Clear lists
*/

int				ft_cmds_setup(t_cmds *st_cmds, int bl_subsh)
{
	if (st_cmds == NULL)
		return (-1);
	ft_update_tokens(st_cmds->st_tokens);
	apply_subsh(st_cmds->st_tokens);
	if (ft_check_token(st_cmds->st_tokens, T_PROC_IN) ||
		ft_check_token(st_cmds->st_tokens, T_PROC_OUT))
		proc_substitution(st_cmds);
	ft_parse_cmd(st_cmds);
	(!bl_subsh) ? ft_apply_her_doc(st_cmds->st_jobctr) : NULL;
	(!g_pos.exit) ? ft_cmds_exec(st_cmds) : 0;
	procsub_close(st_cmds->fd);
	return (0);
}
