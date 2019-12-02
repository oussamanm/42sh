/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 08:03:48 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/12/01 08:03:50 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

void	ft_run_job(t_job *job)
{
	t_process	*process;
	t_list		*proc;

	proc = job->proc;
	job->status = RUN;
	while (proc)
	{
		process = proc->content;
		process->status = RUN;
		proc = proc->next;
	}
}

void	ft_update_p_fg(int index)
{
	t_list	*tmp;
	t_job	*job;
	int		add;

	tmp = g_jobs;
	add = 0;
	while (tmp)
	{
		job = tmp->content;
		if (add == 0)
			job->p = '-';
		if (job->index == index)
			job->p = '+';
		else if (add >= 1)
			job->p = 0;
		add++;
		tmp = tmp->next;
	}
}

void	ft_foreg_wait(t_job *job, t_list **tmp, t_list **pr)
{
	if (tcsetpgrp(0, job->pgid) == -1)
		ft_putendl_fd("Controling terminal ERROR", 2);
	signal(SIGCHLD, SIG_DFL);
	killpg(job->pgid, SIGCONT);
	ft_run_job(job);
	job->background = -1;
	g_sign = 1;
	ft_wait(job);
	g_sign = 0;
	(job->sig_term) ? ft_termsig_fore(job->sig_term, job->cmd) : 0;
	if (job->status == EXITED)
	{
		(job->p == '+') ? ft_update_p(1) : 0;
		ft_remove_node(tmp, pr);
	}
	if (tcsetpgrp(0, getpgrp()) == -1)
		ft_putendl_fd("Controling terminal ERROR", 2);
	signal(SIGCHLD, ft_catch_sigchild);
}

int		ft_fg_content(t_job *job, char *arg, t_list **tmp, t_list **pr)
{
	if (job->status == RUN || job->status == STOPED)
	{
		ft_putendl(job->cmd);
		(arg) ? ft_update_p_fg(job->index) : 0;
		ft_foreg_wait(job, tmp, pr);
		return (1);
	}
	return (0);
}

void	ft_foreground(char *arg)
{
	t_job	*job;
	t_list	*tmp;
	t_list	*pr;
	int		index;

	(!g_jobs) ? ft_putendl_fd("42sh: fg: current: no such job", 2) : 0;
	(arg) ? (index = ft_atoi(arg)) : 0;
	tmp = g_jobs;
	pr = NULL;
	while (tmp)
	{
		job = tmp->content;
		if (arg && index != job->index)
		{
			pr = tmp;
			tmp = tmp->next;
			(!tmp) ? ft_putendl_fd("42sh: fg: current: no such job", 2) : 0;
			continue ;
		}
		if (ft_fg_content(job, arg, &tmp, &pr))
			break ;
		pr = tmp;
		tmp = tmp ? tmp->next : tmp;
	}
}
