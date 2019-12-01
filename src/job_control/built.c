/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:32:46 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/11/30 18:04:07 by mfetoui          ###   ########.fr       */
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

	tmp = jobs;
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

int		ft_get_jobs_arg(char **args, int *index)
{
	int i;
	int j;
	int ret;

	if (!args)
		return (-1);
	j = 0;
	ret = -1;
	while (args[j])
	{
		i = 0;
		if (args[j][0] == '-')
		{
			while (args[j][i])
				i++;
			if (args[j][i - 1] == 'p')
				ret = 1;
			else if (args[j][i - 1] == 'l')
				ret = 0;
		}
		else
			*index = ft_atoi(args[j]);
		j++;
	}
	return (ret);
}

void	ft_print_jobinfo(t_job *job, int ar)
{
	ft_putchar('[');
	ft_putnbr(job->index);
	ft_putchar(']');
	(job->p != 0) ? ft_putchar(job->p) : ft_putchar(' ');
	ft_putstr("  ");
	(ar == 0) ? ft_putnbr(job->pgid) : 0;
	(ar == 0) ? ft_putchar(' ') : 0;
	ft_printstatus(job->status);
	ft_putstr("\t\t\t");
	ft_putstr(job->cmd);
	ft_putchar(' ');
	(job->background == 1) ? ft_putchar('&') : 0;
	ft_putchar('\n');
}

void	ft_jobs_built(char **args)
{
	t_list	*tmp;
	t_job	*job;
	int		index;
	int		ar;

	tmp = jobs;
	index = 0;
	ar = ft_get_jobs_arg(args, &index);
	while (tmp)
	{
		job = tmp->content;
		if (index != 0 && job->index != index)
		{
			tmp = tmp->next;
			continue ;
		}
		if (ar != 1)
			ft_print_jobinfo(job, ar);
		else if (ar == 1)
		{
			ft_putnbr(job->pgid);
			ft_putchar('\n');
		}
		tmp = tmp->next;
	}
}

int		ft_bg_content(t_job *job, char *arg)
{
	if (job->status == STOPED && job->p == '+')
	{
		ft_print_backcmd(job);
		job->background = 1;
		ft_run_job(job);
		killpg(job->pgid, SIGCONT);
		return (1);
	}
	else if ((job->status == RUN && job->p == '+') || (job->status == RUN && arg))
	{
		ft_putstr_fd("bash: bg: job ", 2);
		ft_putnbr(job->index);
		ft_putendl_fd(" already in background", 2);
		return (1);
	}
	return (0);
}

void	ft_continue(char *arg)
{
	t_list	*tmp;
	t_job	*job;
	int		index;

	(!jobs) ? ft_putendl_fd("42sh: bg: current: no such job", 2) : 0;
	(arg) ? (index = ft_atoi(arg)) : 0;
	tmp = jobs;
	while (tmp)
	{
		job = tmp->content;
		if (arg && index != job->index)
		{
			tmp = tmp->next;
			(!tmp) ? ft_putendl_fd("42sh: bg: current: no such job", 2) : 0;
			continue ;
		}
		if (ft_bg_content(job, arg))
			break ;
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

void	ft_foreground(char *arg)
{
	t_job	*job;
	t_list	*tmp;
	t_list	*pr;
	int		index;

	if (!jobs)
	{
		ft_putendl_fd("42sh: fg: current: no such job", 2);
		return ;
	}
	(arg) ? (index = ft_atoi(arg)) : 0;
	tmp = jobs;
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
		if (job->status == RUN || job->status == STOPED)
		{
			ft_putendl(job->cmd);
			(arg) ? ft_update_p_fg(job->index) : 0;
			ft_foreg_wait(job, &tmp, &pr);
			break ;
		}
		pr = tmp;
		tmp = tmp ? tmp->next : tmp;
	}
}
