/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 23:42:21 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/25 03:01:53 by mfetoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
** Exection of cmd sub_stitu
*/

void		child_subsh(int fds[2], char *cmd)
{
	char	**args;
	int		i;

	i = 0;
	ft_signal_default();
	close(fds[0]);
	if (dup2(fds[1], 1) == -1)
		ft_putendl_fd("Error in dub STD_OUT in SUB_SHELL", 2);
	close(fds[1]);
	args = ft_str_split_q(cmd, "\n");
	while (args[i])
	{
		if (i != 0)
			ft_putchar(-1);
		g_proc_sub = 2;
		spec_case_subshell(&(args[i]));
		ft_multi_cmd(args[i], 1);
		i++;
	}
	exit(EXIT_SUCCESS);
}

/*
** exection subshell : by create a pipe line and Read from child process
*/

char		*exec_subsh(char *cmd)
{
	int		fds[2];
	char	buff[11];
	char	*result;
	pid_t	pid;
	int		status;

	ft_bzero(fds, 2);
	status = -1;
	if (pipe(fds) == -1)
		ft_putendl_fd("Error Create Pipe", 2);
	signal(SIGCHLD, SIG_DFL);
	g_sign = 1;
	((pid = fork()) == 0) ? child_subsh(fds, cmd) : NULL;
	waitpid(pid, &status, 0);
	g_sign = 0;
	signal(SIGCHLD, ft_catch_sigchild);
	g_pos.exit = (WIFSIGNALED(status)) ? 1 : 0;
	close(fds[1]);
	result = ft_strnew(0);
	ft_bzero(buff, 11);
	while (read(fds[0], &buff, 10) > 0 &&
		(result = ft_strjoir(result, buff, 1)))
		ft_bzero(buff, 10);
	close(fds[0]);
	return (result);
}

/*
** change new_line with space , or remove last \n in case of one cmd
*/

char		*correct_result(char *result)
{
	int i;

	i = -1;
	if (!result)
		return (NULL);
	while (result[++i])
	{
		if (result[i] == -1 && i)
		{
			result[i - 1] = ' ';
			ft_strcpy(&result[i], &result[i + 1]);
		}
		else if (i == 0 && result[i] == -1)
			result[i] = '\0';
		else if (result[i] == '\n' && result[i + 1] == '\0')
			result[i] = 0;
	}
	return (result);
}

/*
** loop on all sub_stut
*/

char		*change_subsh_quot(char *arg)
{
	char	*cmd;
	char	*value;
	int		i;
	int		len;

	cmd = NULL;
	i = 0;
	arg = ft_strdup(arg);
	while (arg[i])
	{
		if (!(M_SUBSH(arg[i]) && arg[i + 1] == '(') && ++i)
			continue ;
		if ((len = find_subsh(&arg[i + 1])) != -1)
			cmd = ft_strsub(arg, i, len + 2);
		if (cmd && (cmd = ft_strcpy(cmd, &cmd[2])))
		{
			cmd[ft_strlen(cmd) - 1] = '\0';
			value = exec_subsh(cmd);
			value = correct_result(value);
			arg = ft_str_remp(arg, value, i, (int )(ft_strlen(cmd) + 3) * -1);
			ft_strdel(&cmd);
			continue ;
		}
		ft_strdel(&cmd);
		i += (arg && arg[i]) ? 1 : 0;
	}
	return (arg);
}

/*
** Apply sub_shell and change value in tokens
*/

void		apply_subsh(t_tokens *st_tokens)
{
	char	*value;
	char	*temp;

	while (st_tokens)
	{
		value = NULL;
		if (st_tokens->token == T_SUBSHL)
		{
			if ((temp = st_tokens->value) && ft_strcpy(temp, &temp[2]))
				temp[ft_strlen(temp) - 1] = '\0';
			value = exec_subsh(temp);
			ft_strdel(&st_tokens->value);
			value = correct_result(value);
			value_to_token(value, &st_tokens);
			ft_strdel(&value);
		}
		else if (st_tokens->token == T_DQUO &&
			ft_strstr(st_tokens->value, "$("))
		{
			value = change_subsh_quot(st_tokens->value);
			(value) ? ft_strdel(&st_tokens->value) : NULL;
			st_tokens->value = value;
		}
		st_tokens = st_tokens->next;
	}
}
