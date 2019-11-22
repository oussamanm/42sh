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

/*
** Converte Result_cmd to tokens
*/

void	value_to_token(char *value, t_tokens **st_tokens)
{
	char **args;
	int	index;
	int i;
	t_tokens	*save_next;

	if (!st_tokens || !(*st_tokens))
		return ;
	i = 0;
	index = (*st_tokens)->indx;
	args = ft_str_split_q(value, " \n");
	save_next = (*st_tokens)->next;
	while (args[i])
	{
		ft_fill_token(st_tokens, T_TXT, args[i], index);
		index++;
		i++;
	}
	if (i != 0)
	{
		(*st_tokens) = (*st_tokens)->prev;
		free((*st_tokens)->next);
		(*st_tokens)->next = save_next;
		if (save_next)
			save_next->prev = (*st_tokens);
	}
	free(args);
}

/*
** Exection of cmd sub_stitu
*/

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
		if (i != 0)
			ft_putchar(-1);
		ft_multi_cmd(args[i], 1);
		i++;
	}
	close(fds[1]);
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

	ft_bzero(fds, 2);
	if (pipe(fds) == -1)
		ft_putendl_fd("Error Create Pipe", 2);
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
	len = 0;
	arg = ft_strdup(arg);
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
				value = correct_result(value);
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
			ft_strdel(&st_tokens->value);
			/// correction value by remove \n in last
			value = correct_result(value);
			/// split value and fill tokens
			value_to_token(value, &st_tokens);
			ft_strdel(&value);
		}
		else if (st_tokens->token == T_DQUO && ft_strstr(st_tokens->value, "$("))
		{
			value = change_subsh_quot(st_tokens->value);
			(value) ? ft_strdel(&st_tokens->value) : NULL;
			/// split value and fill tokens
			value_to_token(value, &st_tokens);
			ft_strdel(&value);
		}
		st_tokens = st_tokens->next;
	}
}
