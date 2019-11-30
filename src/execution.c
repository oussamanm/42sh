/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:42:10 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/26 16:01:37 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
** Check if exist Cmd : check if Ok and permission
*/

int				ft_check_cmd(char *cmd, char **environ)
{
	int			rtn;
	char		*path_exec;
	struct stat	st_stat;

	if (!cmd)
		return (0);
	rtn = 0;
	if (!ft_check_char(cmd, '/'))	/// case of cmd
		path_exec = ft_find_path(cmd, environ);
	else							/// case of PATH exec
	{
		path_exec = ft_strdup(cmd);
		if (access(cmd, F_OK) != 0 && ++rtn)
			print_error(FIL_NS, NULL, cmd, 0);
		else if (!lstat(cmd, &st_stat) && S_ISDIR(st_stat.st_mode) && ++rtn)
			print_error(IS_DIR, NULL, cmd, 0);
	}
	if (!rtn && path_exec && (access(path_exec, X_OK) ||
		access(path_exec, R_OK)) && ++rtn)
		print_error(FIL_PD, NULL, cmd, 0);
	if (!rtn && (!path_exec || !ft_strlen(path_exec)) && ++rtn)
		print_error(CMD_NF, NULL, cmd, 0);
	free(path_exec);
	return (rtn);
}

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
		exit(EXIT_FAILURE);
	if (ft_check_char(args[0], '/'))
		str_arg = args[0];
	else
	{
		/// Check if exist in HASH_TABLE
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
** Create child proccess , check if builtens , call for apply redirection , Execution
*/

int				ft_cmd_fork(int fork_it, t_pipes *st_pipes)
{
	int		pid;
	int		rtn;
	char	**environ;

	pid = 0;
	rtn = 0;
	if (!st_pipes || !st_pipes->st_tokens)
		return (1);
	
	/// Remove backslashs from tokens
	remove_backslashs(st_pipes->st_tokens);

	/// Fill args without T_EQUAL , T_SUBSHL,
	tokens_to_args(st_pipes);

	/// Check if tmp_env exist
	environ = (st_pipes->tmp_env) ? st_pipes->tmp_env : g_environ;

	/// Check if Builtens
	if (st_pipes->args && ft_check_built(*(st_pipes->args)))
		return (ft_init_built(st_pipes, &(st_pipes->tmp_env)) ? 0 : 1);

	(fork_it) ? signal(SIGCHLD, SIG_DFL) : 0;
	
	/// Fork - Child
	if (fork_it && (pid = fork()) == -1)
		ft_err_exit("Error in Fork new process \n");
	if (pid == 0)
	{
		ft_signal_default();
		if (g_proc_sub && st_pipes->bl_jobctr)
		{
			dup2(open("/dev/null", O_RDONLY), 0);
			if (g_proc_sub == 1)
				signal(SIGINT, SIG_IGN);
		}
		/// Apply redirection
		if (ft_check_redi(st_pipes) && parse_redir(st_pipes) == PARSE_KO)
			exit(EXIT_FAILURE);
		/// execution
		if (!ft_check_cmd(st_pipes->args[0], environ)) /// Check if cmd exist , permission
			ft_cmd_exec(st_pipes->args, environ);
		else
			exit(EXIT_FAILURE);
	}
	else if (fork_it && !g_proc_sub)
		ft_manage_jobs(pid, st_pipes, &rtn);
	else if (fork_it && g_proc_sub && !st_pipes->bl_jobctr)
		waitpid(pid, &rtn, 0);
	(fork_it) ? signal(SIGCHLD, ft_catch_sigchild) : 0;
	/// insertion in hash_table in case of exit_proccess = SUCCESS
	if (rtn == EXIT_SUCCESS && st_pipes->args)
		insert_hash(*st_pipes->args, ft_find_path(*st_pipes->args, environ));
	return (rtn ? 0 : 1);
}

/*
 ** Config Cmds by : - Lexer - Check Syntax - Apply sub_shell - Apply her_doc - Clear lists
 */

int				ft_cmds_setup(char *str_arg, int bl_subsh)
{
	t_cmds		*st_cmds;

	if (str_arg == NULL)
		return (-1);
	st_cmds = ft_new_cmds();
	/// Fill args
	st_cmds->args = ft_str_split_q(str_arg, " \t\n");

	/// Check if cmd is alias and change it
	st_cmds->args = aliasmatched(st_cmds->args);

	/// Apply Lexer && Check Error Syntax
	if ((st_cmds->st_tokens = ft_lexer(st_cmds->args)) == NULL || error_syntax_lexer(st_cmds->st_tokens))
	{
		free_list_cmds(st_cmds);
		return (-1);
	}
	/// update token by remove quotes 
	ft_update_tokens(st_cmds->st_tokens);

	/// Apply sub_shell 
	apply_subsh(st_cmds->st_tokens);
	
	/// Aplly proc_sub 
	if (ft_check_token(st_cmds->st_tokens, T_PROC_IN) || ft_check_token(st_cmds->st_tokens, T_PROC_OUT))
		proc_substitution(st_cmds);
	
	/// Fill Lists of lists 
	ft_parse_cmd(st_cmds);

	/// Apply here_doc (do not applied in case of comming from SUB_SHELL) ???? check if st_tokens exist
	(!bl_subsh) ? ft_apply_her_doc(st_cmds->st_jobctr) : NULL;

	/// Executions * (apply execution if (Ctr + c) doesn't pressed)  *** (!g_pos.exit) ? 
	ft_cmds_exec(st_cmds);

	procsub_close(st_cmds->fd);
	
	/// Clear allocated space
	free_list_cmds(st_cmds);

	return (1);
}
