/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_substitution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfetoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:07:11 by mfetoui           #+#    #+#             */
/*   Updated: 2019/10/25 12:09:43 by mfetoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*token_implode(t_tokens *st_tokens){

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
		setpgid(0, 0);
		close(fd[!type]);
		dup2(fd[type], type);
		close(fd[type]);
		tmp_cmd[ft_strlen(tmp_cmd) - 1] = 0;
		tmp_cmd = ft_strcpy(tmp_cmd , &tmp_cmd[2]);
		ft_multi_cmd(tmp_cmd, 0);
		exit(0);
	}
	close(fd[type]);
	return (fd[!type]);
}

void	main_proc(t_tokens *st_tokens) {
	int     i;
	int     child;

	i = 0;
	if ((child = fork()) == 0)
	{	
		ft_multi_cmd(token_implode(st_tokens), 0);
		exit(0);
	}
	waitpid(child, NULL, 0);
}

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

void    proc_substitution(t_tokens *st_tokens) {
	t_tokens *head;
	int     *fd;
	int     len;
	int     i;

	head = st_tokens;
	len = count_subs(st_tokens);
	fd = (int *)malloc(sizeof(int) * (len + 1));
	ft_bzero(fd, len);
	i = 0;
	while (st_tokens) {
		if (M_CHECK(st_tokens->token,T_PROC_IN,T_PROC_OUT))
		{
			fd[i] = exec_subs(st_tokens->value, (st_tokens->token == T_PROC_OUT) ? 0 : 1);
			ft_strdel(&st_tokens->value);
			st_tokens->value = ft_strjoir("/dev/fd/", (char [2]){fd[i++] + '0', 0}, 0);
		}
		st_tokens = st_tokens->next;
	}
	main_proc(head);
	i = 0;
	while (i < len)
		close(fd[i++]);
}
