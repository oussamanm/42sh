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

/*
** Check if exist redirection
*/

int			ft_check_redi(t_pipes *st_pipes)
{
	t_tokens	*st_temp;

	if (st_pipes == NULL || st_pipes->st_tokens == NULL)
		return (-1);
	st_temp = st_pipes->st_tokens;
	while (st_temp)
	{
		if (st_temp->token < 0)
			return (1);
		st_temp = st_temp->next;
	}
	return (0);
}

/*
** Execute Command			: O
** return i = -1 : command not found | i == -2 : ERR in EXECUTABLE
*/

int			ft_cmd_exec(t_pipes *st_pipes, char **env)
{
	char	*str_arg;
	int		i;

	str_arg = NULL;
	i = 0;
	if (st_pipes->args == NULL || st_pipes->args[0] == NULL)
		return (-2);
	if (!ft_check_char(st_pipes->args[0], '/'))
		str_arg = ft_find_path((st_pipes->args)[0], env);
	else
	{
		str_arg = ft_strdup(st_pipes->args[0]);
		if (access(str_arg, F_OK) != 0 && ++i)
			ft_print_error(FIL_NS, NULL, str_arg, 2);
	}
	if (!i && str_arg && access(str_arg, X_OK) != 0 && ++i)
		ft_print_error(FIL_PD, NULL, str_arg, 2);
	if (i == 0 && str_arg != NULL)
	{
		execve(str_arg, st_pipes->args, env);
		ft_strdel(&str_arg);
		exit(0);
	}
	return ((i == 0) ? -1 : -2);
}

/*
** Check if cmd is builtens and splite			: O
*/

void		ft_split_cmd(int fork_it, t_pipes *st_pipes, char ***env)
{
	int	pid;

	pid = 0;
	ft_remove_quot(st_pipes->args);
	if (st_pipes != NULL && ft_check_built((st_pipes->args)[0]))
	{
		ft_init_built(st_pipes, env);
		return ;
	}
	if (fork_it == 1 && (pid = fork()) == -1)
		ft_err_exit("Error in Fork new process \n");
	if (pid == 0)
	{
		ft_signal_default();
		if (ft_check_redi(st_pipes) && ft_parse_cmd(st_pipes) == PARSE_KO)
			exit(0);
		if (!ft_strcmp(st_pipes->args[0], "echo"))
			ft_buil_echo(st_pipes->args);
		else if (ft_cmd_exec(st_pipes, *env) == -1)
			ft_print_error(CMD_NF, "21sh: ", (st_pipes->args)[0], 0);
		exit(0);
	}
	g_sign = 1;
	wait(NULL);
	g_sign = 0;
}

/*
** Apply here_doc if exist			: O
*/

void		ft_apply_her_doc(t_pipes *st_pipes)
{
	t_tokens	*st_temp;
	t_redir		*st_redir;

	if (st_pipes == NULL)
		return ;
	st_temp = NULL;
	while (st_pipes)
	{
		if (st_pipes->st_tokens)
			st_temp = st_pipes->st_tokens;
		while (st_temp != NULL)
		{
			if (st_temp->token == T_RED_HER_D)
			{
				st_redir = ft_new_redir();
				st_pipes->st_redir = st_redir;
				ft_redi_her(st_redir, st_temp);
			}
			st_temp = st_temp->next;
		}
		st_pipes = st_pipes->next;
	}
}

/*
** Check if there is a pipe , split and fill args, check error lexer :
*/

int			ft_call_cmdss(char *str_arg, char ***environ)
{
	char		**args_pipe;
	t_pipes		*st_pipes;

	if (str_arg == NULL)
		return (-1);
	args_pipe = ft_str_split_q(str_arg, "|");
	if (!*args_pipe)
	{
		ft_strrdel(args_pipe);
		return (-1);
	}
	st_pipes = ft_strr_list(args_pipe);
	(args_pipe) ? free(args_pipe) : NULL;
	if (ft_error_syn(st_pipes) == 1)
		return (-1);
	ft_apply_her_doc(st_pipes);
	if (st_pipes != NULL && st_pipes->next != NULL)
		ft_apply_pipe(st_pipes, environ);
	else
		ft_split_cmd(1, st_pipes, environ);
	ft_clear_cmds(st_pipes);
	return (1);
}
