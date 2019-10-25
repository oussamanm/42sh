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

static int     exec_subs(char *cmd, bool type, t_env *env) {
	int     fd[2];

	pipe(fd);
	if (fork() == 0) {
		setpgid(0, 0);
		close(fd[!type]);
		dup2(fd[type], type);
		close(fd[type]);
		exec_pipe(cmd, env);
	}
	close(fd[type]);
	return (fd[!type]);
}

static void    main_proc(char *cmd, int *fd, t_env *env) {
	pid_t   child;
	int     i;

	i = 0;
	if ((child = fork()) == 0) {
		while (fd[i] > 0)
			cmd = ft_strjoin(cmd, ft_chrjoin(" /dev/fd/", fd[i++] + '0'));
		exec_pipe(cmd, env);
	}
	waitpid(child, NULL, 0);
}

void    proc_substitution(char *cmd,  t_env *env) {
	char    **input;
	int     *fd;
	int     len;
	int     type;
	int     i;

	input = ft_strsplit(cmd, ' ');
	len = ft_dbl_strlen(input);
	fd = (int *)malloc(sizeof(int) * len);
	ft_bzero(fd, len);
	i = 1;
	while (i < len) {
		if (input[i][0] == '<')
			type = 1;
		else if (input[i][0] == '>')
			type = 0;
		input[i] += 2;
		input[i][ft_strlen(input[i]) - 1] = '\0';

		fd[i - 1] = exec_subs(input[i], type, env);
		i++;
	}

	main_proc(input[0], fd, env);

	i = 0;
	while (i < len - 1) {
		close(fd[i++]);
	}
}
