/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:07:11 by mfetoui           #+#    #+#             */
/*   Updated: 2019/11/26 16:10:26 by mfetoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Close pipe file descriptors at the end
*/

void	procsub_close(int *fd) {
	int i = 0;

	if (fd == NULL)
		return ;
	while (fd[i] != 0){
		close(fd[i++]);
	}
}

/*
** Count number of process substitutions
*/

int		procsub_count(t_tokens *st_tokens) {
	int	count;

	count = 0;
	while (st_tokens){
		if ((st_tokens->token == T_PROC_IN) || (st_tokens->token == T_PROC_OUT))
			count++;
		st_tokens = st_tokens->next;
	}
	return (count);
}

/*
** Execute process substitution, and return the pipe file descritor 
*/

int     procsub_fd(char *cmd, bool type) {
	int     fd[2];
	char	*tmp_cmd;

	if (pipe(fd) == -1)
		ft_putstr_fd( "broken pipe", 2);
	if (fork() == 0) {
		tmp_cmd = ft_strdup(cmd);
		close(fd[!type]);
		dup2(fd[type], type);
		close(fd[type]);
		tmp_cmd[ft_strlen(tmp_cmd) - 1] = 0;
		ft_strcpy(tmp_cmd , &tmp_cmd[2]);
		g_proc_sub = 1;
		ft_multi_cmd(tmp_cmd , 1);
		exit(0);
	}
	close(fd[type]);
	return (fd[!type]);
}

/*
** Execute process substitution when found,
** and join the file descriptor number with '/dev/fd/'
*/

void    proc_substitution(t_cmds *st_cmds) {
	t_tokens *st_tokens;
	int     len;
	int     i;

	st_tokens = st_cmds->st_tokens;
	len = procsub_count(st_tokens);
	st_cmds->fd = (int *)malloc(sizeof(int) * (len + 1));
	ft_bzero(st_cmds->fd, (len + 1)* sizeof(int));
	i = 0;
	while (st_tokens) {
		if (M_CHECK(st_tokens->token, T_PROC_IN, T_PROC_OUT))
		{
			st_cmds->fd[i] = procsub_fd(st_tokens->value, (st_tokens->token == T_PROC_OUT) ? 0 : 1);
			ft_strdel(&st_tokens->value);
			st_tokens->value = ft_strjoir("/dev/fd/", ft_itoa(st_cmds->fd[i++]), 0);
		}
		st_tokens = st_tokens->next;
	}
}
