/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:42:10 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/02 06:41:46 by onouaman         ###   ########.fr       */
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

static void		ft_cmd_exec(char **args, char **env)
{
	char	*str_arg;

	str_arg = NULL;
	if (!args || !args[0])
		exit(EXIT_SUCCESS);
	if (ft_check_char(args[0], '/'))
		str_arg = args[0];
	else
	{
		if (!(str_arg = lookup_hash(args[0])))
			str_arg = ft_find_path(args[0], env);
	}
	if (str_arg != NULL)
	{
		execve(str_arg, args, env);
		ft_strdel(&str_arg);
	}
	exit(EXIT_FAILURE);
}

/*
** Handle child process by , call redirection and call function execution
*/

void			ft_handle_child(t_pipes *st_pipes, char **environ)
{
	ft_signal_default();
	if (g_proc_sub && st_pipes->bl_jobctr)
	{
		dup2(open("/dev/null", O_RDONLY), 0);
		if (g_proc_sub == 1)
			signal(SIGINT, SIG_IGN);
	}
	if (ft_check_redi(st_pipes) && parse_redir(st_pipes) == PARSE_KO)
		exit(EXIT_FAILURE);
	if (lookup_hash(st_pipes->args[0]))
		ft_cmd_exec(st_pipes->args, environ);
	else if (!ft_check_cmd(st_pipes->args[0], environ))
		ft_cmd_exec(st_pipes->args, environ);
	else
		exit(EXIT_CMD_NF);
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
	if (rtn == EXIT_SUCCESS && st_pipes->args)
		insert_hash(*st_pipes->args, ft_find_path(*st_pipes->args, environ));
	return (rtn);
}

/*
** Config Cmds by : - Lexer - Check Syntax - sub_shell - her_doc - Clear lists
*/

int				ft_cmds_setup(char *str_arg, int bl_subsh)
{
	t_cmds		*st_cmds;

	if (str_arg == NULL)
		return (-1);
	st_cmds = ft_new_cmds();
	st_cmds->args = ft_str_split_q(str_arg, " \t\n");
	st_cmds->st_tokens = ft_lexer(st_cmds->args);
	handle_alias(&(st_cmds->st_tokens));
	if (error_syntax_lexer(st_cmds->st_tokens))
	{
		free_list_cmds(st_cmds);
		return ((g_exit_status = 258));
	}
	ft_update_tokens(st_cmds->st_tokens);
	apply_subsh(st_cmds->st_tokens);
	if (ft_check_token(st_cmds->st_tokens, T_PROC_IN) ||
		ft_check_token(st_cmds->st_tokens, T_PROC_OUT))
		proc_substitution(st_cmds);
	ft_parse_cmd(st_cmds);
	(!bl_subsh) ? ft_apply_her_doc(st_cmds->st_jobctr) : NULL;
	(!g_pos.exit) ? ft_cmds_exec(st_cmds) : 0;
	procsub_close(st_cmds->fd);
	free_list_cmds(st_cmds);
	return (0);
}
