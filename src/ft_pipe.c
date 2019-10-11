/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:40:16 by onouaman          #+#    #+#             */
/*   Updated: 2019/07/24 23:40:17 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	ft_close_pipes : close all pipes created  :
*/

void			ft_close_pipes(t_pipes *st_pipes)
{
	while (st_pipes != NULL)
	{
		if (st_pipes->fds[0] != 0)
			close(st_pipes->fds[0]);
		if (st_pipes->fds[1] != 0)
			close(st_pipes->fds[1]);
		st_pipes = st_pipes->next;
	}
}

/*
**	ft_create_pipes : create all pipes needed :
*/

void			ft_create_pipes(t_pipes *st_pipes)
{
	t_pipes *st_head;
	int		fds[2];

	st_head = st_pipes;
	while (st_pipes->next != NULL)
	{
		if (pipe(fds) == -1)
			ft_err_exit("Error in Pipe Function \n");
		if (st_pipes == st_head)
			st_pipes->fds[0] = fds[0];
		st_pipes->fds[1] = fds[1];
		if (st_pipes->next != NULL)
			st_pipes->next->fds[0] = fds[0];
		st_pipes = st_pipes->next;
		if (st_pipes->next == NULL)
			st_pipes->fds[1] = fds[1];
	}
}

/*
**	ft_apply_pipe_h : helper function (norme) :
*/

static void		ft_apply_pipe_h(t_pipes *st_pipes, t_pipes *st_head, int i)
{
	if (dup2(st_pipes->fds[i], i) == -1)
		ft_putendl_fd("Error in dub STD_", 2);
	ft_close_pipes(st_head);
	ft_cmd_fork(0, st_pipes);
	exit(0);
}

/*
**	ft_apply_pipe : PIPE :
*/

int				ft_apply_pipe(t_pipes *st_pipes)
{
	t_pipes	*st_head;
	int		status;

	status = 0;
	st_head = st_pipes;
	ft_create_pipes(st_pipes);
	while (st_pipes != NULL)
	{
		if (fork() == 0)
		{
			if (st_pipes->next != NULL)
			{
				if (st_pipes != st_head && dup2(st_pipes->fds[0], 0) == -1)
					ft_putendl_fd("Error in dub STD_IN", 2);
				ft_apply_pipe_h(st_pipes, st_head, 1);
			}
			else if (st_pipes->next == NULL)
				ft_apply_pipe_h(st_pipes, st_head, 0);
			exit(EXIT_FAILURE);
		}
		st_pipes = st_pipes->next;
	}
	ft_close_pipes(st_head);
	while (st_head)
	{
		wait(&st_head->status);
		status = st_head->status;
		st_head = st_head->next;
	}
	return ((status) ? 0 : 1);
}

/*
** exec pipe
*/

int				ft_pipe(t_pipes *st_pipe)
{
	int status;

	status = 0;
	if (!st_pipe)
		return (-1); /// Check this status
	/// if exist pipe
	if (st_pipe && st_pipe->next)
		status = ft_apply_pipe(st_pipe);
	else
		status = ft_cmd_fork(1, st_pipe);
	return (status);
}