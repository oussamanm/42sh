/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:32:46 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/09/24 19:32:48 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

void	ft_foreground_job(t_job *job)
{
	if (tcsetpgrp(0, job->pgid) == -1)
		ft_putendl("Can't set controling terminal to the child process");
	g_sign = 1;
	ft_wait(job);
	g_sign = 0;
	(job->sig_term != 0) ? ft_termsig_fore(job->sig_term, job->cmd) : 0;
}

void	ft_manage_jobs(int pid, t_pipes *st_pipes, int *rtn)
{
	t_job		*job;
	t_process	*process;
	int			add;

	add = 0;
	job = ft_inisial_job();
	job->cmd = ft_cmd_value(st_pipes->st_tokens, job->cmd);
	job->pgid = pid;
	setpgid(job->pgid, pid);
	job->status = RUN;
	ft_fill_process(pid, job);
	if (!st_pipes->bl_jobctr)
		ft_foreground_job(job);
	else
	{
		job->background = 1;
		ft_print_pid(job->index, job->pgid);
		add = 1;
	}
	if (tcsetpgrp(0, getpid()) == -1)
		ft_putendl("Can't set the controling terminal to the parent process");
	process = job->proc->content;
	*rtn = process->exit_status;
	(job->status == STOPED || add) ? ft_add_job(job) : 0;
}

void	ft_pipe_job_man(t_job *job, t_pipes *st_pipes, int *status, int add)
{
	t_process	*p;
	t_list		*proc;

	p = NULL;
	proc = job->proc;
	if (!st_pipes->bl_jobctr)
	{
		if (tcsetpgrp(0, job->pgid) == -1)
			ft_putendl("Can't set controling terminal to the child process");
		g_sign = 1;
		ft_wait(job);
		g_sign = 0;
		(job->sig_term != 0) ? ft_termsig_fore(job->sig_term, job->cmd) : 0;
	}
	if (tcsetpgrp(0, getpid()) == -1)
		ft_putendl("Can't set the controling terminal to the parent process");
	while (proc)
	{
		p = proc->content;
		*status = p->exit_status;
		proc = proc->next;
	}
	(job->status == STOPED || add) ? ft_add_job(job) : 0;
}

void	ft_single_proc(t_job *job, t_pipes *st_pipes, int pid, int *add)
{
	job->cmd = ft_cmd_value(st_pipes->st_tokens, job->cmd);
	if (st_pipes->next)
		job->cmd = ft_strjoir_rtn(job->cmd, " | ", 1);
	if (job->pgid == -1)
	{
		job->pgid = pid;
		if (st_pipes->bl_jobctr)
		{
			ft_print_pid(job->index, job->pgid);
			*add = 1;
			job->background = 1;
		}
	}
	setpgid(job->pgid, pid);
	job->status = RUN;
	ft_fill_process(pid, job);
}
