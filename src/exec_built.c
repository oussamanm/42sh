/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 06:25:57 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/02 06:47:23 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include "../includes/read_line.h"

/*
** Save a copy of fds : STD_OUT, STD_IN, STD_ERR
*/

static void		save_fds(void)
{
	if (dup2(0 , SAVED_FD) == -1)
		ft_putendl_fd("Error in dup, in builtens \n", 2);
}

/*
** restor  fds : STD_OUT, STD_IN, STD_ERR to default
*/

static void		restor_fds(void)
{
	int	i;
	int	fd;
	
	i = -1;
	fd = SAVED_FD;
	if (read(SAVED_FD, NULL, 0) == -1 && write(SAVED_FD, NULL, 0) == -1 && g_tty_name)
		if ((fd = open(g_tty_name, O_RDWR)) == -1)
			fd = SAVED_FD;
	while (++i < 3)
		if (dup2(fd, i) == -1)
			ft_putendl_fd("Error in dup or close in builtens \n", 2);
	close(fd);
}

/*
** initail builtens : duplicate STD_* , Call builtens , Resete STD_*
*/

int			ft_init_built(t_pipes *st_pipes, int fork_it, char ***tmp_env)
{
	int		status;
	int		pid;

	fork_it = (fork_it && st_pipes->bl_jobctr == 1) ? 1 : 0;
	pid = 0;
	if (!fork_it)
		save_fds();
	if (fork_it && ((pid = fork()) == -1))
		ft_err_exit("Error in Fork new process \n");
	if (pid > 0 && fork_it && !g_proc_sub)
		ft_manage_jobs(pid, st_pipes, &status);
	if (pid == 0)
	{
		status = ft_call_built(st_pipes, tmp_env);
		if (fork_it)
			exit((status) ? EXIT_FAILURE : EXIT_SUCCESS);
	}
	else if (fork_it && g_proc_sub && !st_pipes->bl_jobctr)
		waitpid(pid, &status, 0);
	if (!fork_it)
		restor_fds();
	return (status);
}

/*
**  Call Builtens (close fds of redirection)
*/

int			ft_call_built(t_pipes *st_pipes, char ***tmp_env)
{
	int		status;
	int		tmp;

	status = 0;
	tmp = 0;
	if (st_pipes == NULL || !st_pipes->args || !(*st_pipes->args))
		return (-1);
	if (ft_check_redi(st_pipes) && parse_redir(st_pipes) == PARSE_KO)
		return (REDI_KO);
	if ((tmp = builtens_mini(st_pipes, tmp_env)) == -1)
		status = builtens_shell(st_pipes, tmp_env);
	else
		status = tmp;
	while (st_pipes->st_redir != NULL)
	{
		if (st_pipes->st_redir->fd_des != -1)
			close(st_pipes->st_redir->fd_des);
		st_pipes->st_redir = st_pipes->st_redir->next;
	}
	return (status);
}

/*
**	Check if Command builtens
*/

int			ft_check_built(char *arg)
{
	if (arg == NULL)
		return (-1);
	if (!ft_strcmp(arg, "exit") || !ft_strcmp(arg, "echo"))
		return (1);
	else if (!ft_strcmp(arg, "export"))
		return (1);
	else if (!ft_strcmp(arg, "unset") || !ft_strcmp(arg, "set"))
		return (1);
	else if (!ft_strcmp(arg, "cd") || !ft_strcmp(arg, "type"))
		return (1);
	else if (!ft_strcmp(arg, "alias") || !ft_strcmp(arg, "unalias"))
		return (1);
	else if (!ft_strcmp(arg, "source") || !ft_strcmp(arg, "hash"))
		return (1);
	else if (!ft_strcmp(arg, "history") || !ft_strcmp(arg, "fc"))
		return (1);
	else if (!ft_strcmp(arg, "fg") || !ft_strcmp(arg, "bg")
			|| !ft_strcmp(arg, "jobs"))
		return (1);
	return (0);
}
