/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:07:11 by mfetoui           #+#    #+#             */
/*   Updated: 2019/11/23 01:02:25 by mfetoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*token_join(t_tokens *st_tokens){

	char	*str;

	str = ft_strnew(0);
	while (st_tokens){
		str = ft_strjoir(str, ft_strjoir(st_tokens->value, " ", 0), 3);
		st_tokens = st_tokens->next;
	}
	return (str);
}

int     exec_subs(char *cmd, bool type)
 {
	int     fd[2];
	char	*tmp_cmd;

	pipe(fd);
	if (fork() == 0) {
		tmp_cmd = ft_strdup(cmd);
	//	setpgid(0, 0);
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

/*void	main_proc(t_tokens *st_tokens) {
	int     i;
	int     child;

	i = 0;
	if ((child = fork()) == 0)
	{
		ft_multi_cmd(token_implode(st_tokens), 0);
		exit(0);
	}
	waitpid(child, NULL, 0);
}*/

int		count_subs(t_tokens *st_tokens) {
	int	count;

	count = 0;
	while (st_tokens){
		if ((st_tokens->token == T_PROC_IN) || (st_tokens->token == T_PROC_OUT))
			count++;
		st_tokens = st_tokens->next;
	}
	return (count);
}

void	procsub_close(int *fd) {
	int i = 0;

	if (fd == NULL)
		return ;
	while (fd[i] != 0){
		close(fd[i++]);
	}
}

void    proc_substitution(t_cmds *st_cmds) {
	t_tokens *st_tokens;
	t_tokens *head;
	int     len;
	int     i;

	st_tokens = st_cmds->st_tokens;
	head = st_tokens;
	len = count_subs(st_tokens);
	st_cmds->fd = (int *)malloc(sizeof(int) * (len + 1));
	ft_bzero(st_cmds->fd, len);
	i = 0;
	while (st_tokens) {
		if (M_CHECK(st_tokens->token,T_PROC_IN,T_PROC_OUT))
		{
			st_cmds->fd[i] = exec_subs(st_tokens->value, (st_tokens->token == T_PROC_OUT) ? 0 : 1);
			ft_strdel(&st_tokens->value);
			st_tokens->value = ft_strjoir("/dev/fd/", (char [2]){st_cmds->fd[i++] + '0', 0}, 0);
		}
		st_tokens = st_tokens->next;
	}
	st_cmds->args = ft_str_split_q(token_join(head), " \t\n");
}
