
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:42:10 by onouaman          #+#    #+#             */
/*   Updated: 2019/09/23 00:58:29 by mfetoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

///******* Function just for Debuging *****/
void	ft_print_pipe(t_pipes *st_pipes)
{
	t_tokens *st_tokens;

	st_tokens = NULL;
	while (st_pipes)
	{
		dprintf(2,"\n\t\t------- Start Pipe-------\n\t\t");
		st_tokens = st_pipes->st_tokens;
		while (st_tokens != NULL)
		{
			dprintf(2, "<%s>  ",st_tokens->value);
			st_tokens = st_tokens->next;
		}
		dprintf(2,"\n\t\t--------------\n");		
		st_pipes = st_pipes->next;
	}
}
void	ft_print_logopr(t_logopr *st_logopr)
{
	t_tokens *st_tokens;

	st_tokens = NULL;
	while (st_logopr)
	{
		dprintf(2,"\n\t------- Start LOG_OPR -------\n\t");
		st_tokens = st_logopr->st_tokens;
		while (st_tokens != NULL)
		{
			dprintf(2, "<%s>  ",st_tokens->value);
			st_tokens = st_tokens->next;
		}
		dprintf(2,"\n\t--------------\n");
		ft_print_pipe(st_logopr->st_pipes);
		st_logopr = st_logopr->next;
	}
}
void	ft_print_jobctr(t_jobctr *st_jobctr)
{
	t_tokens *st_tokens;

	st_tokens = NULL;
	while (st_jobctr)
	{
		dprintf(2,"\n------- Start job_ctr-------\n");
		st_tokens = st_jobctr->st_tokens;
		while (st_tokens != NULL)
		{
			dprintf(2, " <%s>  ",st_tokens->value);
			st_tokens = st_tokens->next;
		}
		dprintf(2,"\n--------------\n");
		ft_print_logopr(st_jobctr->st_logopr);
		st_jobctr = st_jobctr->next;
	}
}
void	ft_print_tokens(t_cmds *st_cmds)
{
	t_jobctr *st_jobctr;

	if (!st_cmds)
		return ;
	st_jobctr = st_cmds->st_jobctr;
	ft_print_jobctr(st_jobctr);
}

///******* End print *****/

/*
 ** Execute Logical Operateur
 */

static void		logical_ops(t_logopr *st_logopr)
{
	int		cmp;
	int		state;

	state = -1;
	while (st_logopr != NULL)
	{
		state = ft_pipe(st_logopr->st_pipes);
		if ((st_logopr->status == 248 && state == 0) ||
				(st_logopr->status == 76 && state == 1))
			st_logopr = st_logopr->next;
		else
		{
			cmp = st_logopr->status;
			st_logopr = st_logopr->next;
			while (st_logopr != NULL)
			{
				if (st_logopr->status != cmp)
				{
					st_logopr = st_logopr->next;
					break;
				}
				st_logopr = st_logopr->next;
			}
		}
	}
}

/*
 ** Execute cmds
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
	(rtn) ? exit(EXIT_FAILURE) : NULL;
	return (rtn);
}

/*
** Trim all args
*/

void			ft_strrtrim(char **args)
{
	int i;

	i = 0;
	if (!args || !*args)
		return ;
	while (args[i])
	{
		args[i] = ft_strtrim_and_free(args[i]);
		i++;
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
		str_arg = ft_find_path(args[0], env);
	if (str_arg != NULL)
	{
		execve(str_arg, args, env);
		ft_strdel(&str_arg);
	}
	exit(EXIT_FAILURE);
}

void			remove_backslashs(char **args)
{
	int		index;
	char	*arg;
	int		i;
	int		quoted;

	while (args && *args)
	{
		arg = *args;
		i = -1;
		quoted = 0;
		if (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'')
		{
			args++;
			continue ;
		}
		else if (arg[0] == '"' && arg[ft_strlen(arg) - 1] == '"')
			quoted = 1;
		while (arg[++i] && (index = ft_find_char(&arg[i], '\\')) != -1)
		{
			i += index;
			if (quoted && M_SPEC_CHARC(arg[i + 1]))
				ft_strcpy(&arg[i],&arg[i + 1]);
			else if (!quoted)
				ft_strcpy(&arg[i],&arg[i + 1]);
		}
		if (i > 1 && ft_all_quot(arg))
		{
			*args = ft_strnew(ft_strlen(arg) + 2);
			(*args)[0] = '"';
			ft_strcpy(&(*args)[1], arg);
			(*args)[ft_strlen(*args)] = '"';
		}
		args++;
	}
}

/*
** Create child proccess , check if builtens , call for apply redirection
*/

int				ft_cmd_fork(int fork_it, t_pipes *st_pipes)
{
	int		pid;
	int		rtn;
	char	**environ;

	pid = 0;
	rtn = 0;

	/// Remove backslashs
	remove_backslashs(st_pipes->args);

	/// Remove Quote
	ft_remove_quot(st_pipes->args);
	
	/// Check if tmp_env exist
	environ = (st_pipes->tmp_env) ? st_pipes->tmp_env : g_environ;
	
	/// Check if Builtens
	if (st_pipes && ft_check_built(st_pipes->args[0]))
		return (ft_init_built(st_pipes, &(st_pipes->tmp_env))); ///  add return to ft_init_built
	/// Fork - Child
	if (fork_it && (pid = fork()) == -1)
		ft_err_exit("Error in Fork new process \n");
	if (pid == 0)
	{
		ft_signal_default();
		/// Apply redirection
		if (ft_check_redi(st_pipes) && ft_parse_redir(st_pipes) == PARSE_KO)
			exit(EXIT_FAILURE);
		if (!ft_strcmp(st_pipes->args[0], "echo"))
			built_echo(st_pipes->args);
		else if (!ft_check_cmd(st_pipes->args[0], environ)) /// Check if cmd exist , permission
			ft_cmd_exec(st_pipes->args, environ);
	}
	g_sign = 1;
	waitpid(pid, &rtn, 0);
	g_sign = 0;
	return (rtn ? 0 : 1);
}

/*
 ** Config Cmds by : - Lexer - Check Syntax - Apply sub_shell - Apply her_doc - Execution - Clear lists
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
	//aliasmatched(st_cmds->args);

	/// Apply Lexer && Check Error Syntax
	if ((st_cmds->st_tokens = ft_lexer(st_cmds->args)) == NULL 
		|| error_syntax_lexer(st_cmds->st_tokens))
	{
		free_list_cmds(st_cmds);
		return (-1);
	}
	/// update token by remove expansions
	ft_update_tokens(st_cmds->st_tokens);

	/// Apply sub_shell
	apply_subsh(st_cmds->st_tokens);

	/// Aplly proc_sub
	if (ft_check_token(st_cmds->st_tokens, T_PROC_IN) || ft_check_token(st_cmds->st_tokens, T_PROC_OUT))
	{
		proc_substitution(st_cmds->st_tokens);
		free_list_cmds(st_cmds);
		return (0);
	}

	/// Fill Lists of lists
	ft_parse_cmd(st_cmds);

	/// Apply here_doc (do not applied in case of comming from SUB_SHELL)
	(!bl_subsh) ? ft_apply_her_doc(st_cmds->st_jobctr) : NULL;

	/// Executions
	ft_cmds_exec(st_cmds);
	/// Clear allocated space
	//free_list_cmds(st_cmds);
	return (1);
}