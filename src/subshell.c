/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 23:42:21 by onouaman          #+#    #+#             */
/*   Updated: 2019/10/02 23:42:22 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

void		child_subsh(int fds[2], char *cmd)
{
	close(fds[0]);
	if (dup2(fds[1] , 1) == -1)
		ft_putendl_fd("Error in dub STD_OUT in SUB_SHELL", 2);
	char **args;
	int i= 0;
	args = ft_str_split_q(cmd,"\n");
	while (args[i])
	{
		ft_multi_cmd(args[i], 1);
		ft_putchar(-1);
		i++;
	}
	close(fds[1]);
	exit(EXIT_SUCCESS);
}

char		*exec_subsh(char *cmd)
{
	int		fds[2];
	char	buff[11];
	char	*result;
	int		i;

	ft_bzero(fds, 2);
	if (pipe(fds) == -1)
		ft_putendl_fd("Error Create Pipe", 2);

	/// Create child and execute
	if (fork() == 0)
		child_subsh(fds, cmd);
	result = ft_strnew(0);
	close(fds[1]);
	wait(NULL);
	ft_bzero(buff, 11);
	while (read(fds[0] , &buff, 10) > 0)
	{
		result = ft_strjoir(result, buff, 1);
		ft_bzero(buff, 10);
	}
	close(fds[0]);

	/// change '\n' with 'space'
	i = -1;
	while (result[++i])
	{
		if (result[i] == -1 && i)
		{
			result[i -1] = ' ';
			ft_strcpy(&result[i], &result[i + 1]);
		}
	}
	return (result);
}

char		*change_subsh_quot(char *arg)
{
	char	*cmd;
	char	*value;
	int		i;
	int		len;

	if (!arg)
		return (NULL);
	cmd = NULL;
	i = 0;
	len = 0;
	while (arg[i])
	{
		if (arg[i] == '(' && i && M_SUBSH(arg[i - 1]))
		{
			if ((len = find_subsh(&arg[i])) != -1)
				cmd = ft_strsub(arg, i - 1, len + 2);
			if (cmd && (cmd = ft_strcpy(cmd, &cmd[2])))
			{
				cmd[ft_strlen(cmd) - 1] = '\0';
				value = exec_subsh(cmd);
				arg = ft_str_remp(arg, value, i - 1, (ft_strlen(cmd) + 3) * -1);
			}
			ft_strdel(&cmd);
		}
		i++;
	}
	return (arg);
}

void		apply_subsh(t_tokens *st_tokens)
{
	char	*value;
	char	*temp;
	int		i;

	i = 0;
	while (st_tokens)
	{
		value = NULL;
		if (st_tokens->token == T_SUBSHL)
		{
			if ((temp = st_tokens->value) && ft_strcpy(temp, &temp[2]))
				temp[ft_strlen(temp) - 1] = '\0';
			value = exec_subsh(temp);
		}
		else if (st_tokens->token == T_DQUO && st_tokens->value)
		{
			if ((i = ft_find_char(st_tokens->value, '(')) != -1 && i && M_SUBSH(st_tokens->value[i - 1]))
			{
				temp = ft_strdup(st_tokens->value);
				value = change_subsh_quot(temp);
			}
		}
		(value) ? ft_strdel(&st_tokens->value) : NULL;
		st_tokens->value = (value) ? value : st_tokens->value;
		st_tokens = st_tokens->next;
	}
}
