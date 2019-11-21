/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:32:46 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/09/24 19:32:48 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	ft_stoped(t_job *job)
{
	t_process	*proc;
	t_list		*lst;

	lst = job->proc;
	while (lst)
	{
		proc = lst->content;
		if (proc->status == STOPED)
		{
			job->status = STOPED;
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

char	ft_terminated(t_job *job)
{
	t_process	*proc;
	t_list		*lst;

	lst = job->proc;
	while (lst)
	{
		proc = lst->content;
		if (proc->status != EXITED)
			return (0);
		lst = lst->next;
	}
	job->status = EXITED;
	return (1);
}

void	ft_updatestatus(t_job *job, int status, int pid)
{
	t_list		*proc;
	t_process	*process;

	proc = job->proc;
	while (proc)
	{
		process = proc->content;
		if (pid == process->pid)
		{
			process->status = EXITED;
			if (WIFSTOPPED(status))
				process->status = STOPED;
			if (WIFSIGNALED(status))
				job->sig_term = WTERMSIG(status);
			process->exit_status = status;
		}
		proc = proc->next;
	}
}

int		ft_current_status(t_job *current, int status, int pid)
{
	if (current)
	{
		ft_updatestatus(current, status, pid);
		if (ft_terminated(current) || ft_stoped(current))
		{
			ft_collect_job_status();
			return (1);
		}
	}
	return (0);
}

void	ft_wait(t_job *current)
{
	int		pid;
	int		status;
	t_job	*job;
	t_list	*tmp;

	while (1)
	{
		if ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) < 0)
			break ;
		if (pid == 0 && current)
			continue;
		else if (pid == 0)
			break ;
		tmp = jobs;
		if (ft_current_status(current, status, pid))
			return ;
		while (tmp)
		{
			job = tmp->content;
			ft_updatestatus(job, status, pid);
			tmp = tmp->next;
		}
	}
	ft_collect_job_status();
}
