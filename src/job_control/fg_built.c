/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 08:03:48 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/12/02 16:50:58 by aboukhri         ###   ########.fr       */
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
		(process->status != EXITED) ? process->status = RUN : 0;
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
	t_process *process;

	process = job->proc->content;
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
	if (ft_inter_back(job->proc) || job->status == STOPED)
		ft_putchar('\n');
	if (job->status == EXITED)
	{
		ft_remove_node(tmp, pr);
		ft_update_p(1);
	}
	if (tcsetpgrp(0, g_shellpid) == -1)
		ft_putendl_fd("Controling terminal ERROR", 2);
	signal(SIGCHLD, ft_catch_sigchild);
}

int		ft_fg_content(t_job *job, char *arg, t_list **tmp, t_list **pr)
{
	if ((job->status == RUN || job->status == STOPED) && (job->p == '+' || arg))
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
	(arg && arg[0] == '%') ? arg++ : 0;
	(arg) ? index = ft_atoi(arg) : 0;
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
