/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:32:46 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/09/24 19:32:48 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

void	ft_jobs_built(void)
{
	t_list	*tmp;
	t_job	*job;

	tmp = jobs;
	while (tmp)
	{
		job = tmp->content;
		ft_putchar('[');
		ft_putnbr(job->index);
		ft_putchar(']');
		(job->p != 0) ? ft_putchar(job->p) : ft_putchar(' ');
		ft_putstr("  ");
		ft_printstatus(job->status);
		ft_putstr("\t\t\t");
		ft_putstr(job->cmd);
		ft_putchar(' ');
		(job->background) ? ft_putchar('&') : 0;
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

void	ft_continue(void)
{
	t_list	*tmp;
	t_job	*job;

	if (!jobs)
	{
		ft_putendl_fd("42sh: bg: current: no such job", 2);
		return ;
	}
	tmp = jobs;
	while (tmp)
	{
		job = tmp->content;
		if (job->status == STOPED)
		{
			ft_print_backcmd(job);
			job->background = 1;
			job->status = RUN;
			killpg(job->pgid, SIGCONT);
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_foreg_wait(t_job *job, t_list *tmp, t_list *pr)
{
	if (tcsetpgrp(0, job->pgid) == -1)
		ft_putendl_fd("Controling terminal ERROR", 2);
	signal(SIGCHLD, SIG_DFL);
	killpg(job->pgid, SIGCONT);
	job->status = RUN;
	g_sign = 1;
	ft_wait(job);
	g_sign = 0;
	(job->sig_term) ? ft_termsig_fore(job->sig_term, job->cmd) : 0;
	(job->status == EXITED) ? ft_remove_node(tmp, pr) : 0;
	if (tcsetpgrp(0, getpgrp()) == -1)
		ft_putendl_fd("Controling terminal ERROR", 2);
	signal(SIGCHLD, ft_catch_sigchild);
}

void	ft_foreground(void)
{
	t_job	*job;
	t_list	*tmp;
	t_list	*pr;

	if (!jobs)
	{
		ft_putendl_fd("42sh: fg: current: no such job", 2);
		return ;
	}
	tmp = jobs;
	pr = NULL;
	while (tmp)
	{
		job = tmp->content;
		if (job->status == STOPED)
		{
			ft_foreg_wait(job, tmp, pr);
			break ;
		}
		pr = tmp;
		tmp = tmp ? tmp->next : tmp;
	}
}
