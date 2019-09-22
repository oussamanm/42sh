/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:42:10 by onouaman          #+#    #+#             */
/*   Updated: 2019/07/24 23:42:14 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"


///******* print *****/
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
	/*if (ft_error_redir(st_tokens))



/*
** Check if exist Cmd : check if Ok and permission
*/

int			ft_check_cmd(t_pipes *st_pipes, char **environ)
{
	int		rtn;
	char	*str_arg;
	char	*cmd;

	if (!st_pipes)
		return (0);
	rtn = 0;
	cmd = NULL;
	if (st_pipes->st_tokens)
		cmd = st_pipes->st_tokens->value;
	if (!ft_check_char(cmd, '/'))
		str_arg = ft_find_path(cmd, environ);
	else
	{
		str_arg = ft_strdup(cmd);
		if (access(str_arg, F_OK) != 0 && ++rtn)
			ft_print_error(FIL_NS, NULL, str_arg, 2);
	}
	if (!rtn && str_arg && access(str_arg, X_OK) != 0 && ++rtn)
		ft_print_error(FIL_PD, NULL, str_arg, 2);
	if (rtn == 0 && str_arg == NULL && ++rtn)
		ft_print_error(CMD_NF, "21sh: ", cmd, 0);
	return (rtn);
}

/*
** Execute Cmd
*/

void		ft_cmd_exec(t_pipes *st_pipes, char **env)
{
	char	*str_arg;

	str_arg = NULL;
	if (st_pipes->args == NULL || st_pipes->args[0] == NULL)
		exit(EXIT_FAILURE);
	
	str_arg = ft_find_path(st_pipes->args[0], env);
	if (str_arg != NULL)
	{
		execve(str_arg, st_pipes->args, env);
		ft_strdel(&str_arg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

/*
** Check if cmd is builtens
*/

int			ft_cmd_fork(int fork_it, t_pipes *st_pipes, char ***env)
{
	int	pid;
	int rtn;

	pid = 0;
	rtn = 0;
	/// Fill args from tokens
	ft_tokens_args(st_pipes);
	/// Remove Quote
	ft_remove_quot(st_pipes->args);
	/// Check if Builtens
	if (st_pipes && ft_check_built((st_pipes->args)[0]))
		return (ft_init_built(st_pipes, env)); ///  add return to ft_init_built
	/// Fork - Child
	if (fork_it && (pid = fork()) == -1)
		ft_err_exit("Error in Fork new process \n");
	if (pid == 0)
	{
		ft_signal_default();
		if (ft_check_redi(st_pipes) && ft_parse_redir(st_pipes) == PARSE_KO)
			exit(EXIT_FAILURE);
		if (!ft_strcmp(st_pipes->args[0], "echo"))
			ft_buil_echo(st_pipes->args);
		else if (!ft_check_cmd(st_pipes, *env)) /// Check if cmd and exist and permission
			ft_cmd_exec(st_pipes, *env);
	}
	g_sign = 1;
	wait(&rtn);
	g_sign = 0;
	return (rtn);
}

/*
** Config Cmds by : - Lexer - Check Syntax - apply her_doc - Execution - Clear lists
*/

int			ft_cmds_setup(char *str_arg, char ***environ)
{
	t_cmds		*st_cmds;

	if (str_arg == NULL)
		return (-1);
	st_cmds = ft_new_cmds();

	/// Correction args
	st_cmds->str_cmd = ft_corr_args(st_cmds->str_cmd, *environ);

	/// Fill args
	st_cmds->args = ft_str_split_q(str_arg, " \t\n");

	/// Apply Lexer
	if ((st_cmds->st_tokens = ft_lexer(st_cmds->args)) == NULL)
		return (-1);

	/// Check Error Syntax
	/*if (ft_error_syntax(st_tokens) == 1)
		return (-1);*/

	/// Fill Lists of lists
	ft_parse_cmd(st_cmds);

	//ft_apply_her_doc(st_pipes);

	//ft_print_tokens(st_cmds);
	/// Executions
	ft_cmds_exec(st_cmds, environ);

	/// Clear allocated space
	//ft_clear_cmds(st_cmds);
	return (1);
}

/*
** Execute cmds
*/

void		ft_cmds_exec(t_cmds *st_cmds, char ***environ)
{
	t_jobctr	*st_jobctr;
	UNUSED(environ);

	if (!st_cmds)
		return ;
	st_jobctr = st_cmds->st_jobctr;
	while (st_jobctr)
	{
		//ft_logic_opr(st_jobctr->st_logopr, environ);
		st_jobctr = st_jobctr->next;
	}
}