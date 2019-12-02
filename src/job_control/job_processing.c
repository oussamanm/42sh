/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 00:28:15 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/11/10 00:28:17 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_printstatus(int status)
{
	if (status == STOPED)
		ft_putstr("Stopped");
	if (status == RUN)
		ft_putstr("Running");
	if (status == TERMINATED)
		ft_putstr("Terminated");
	if (status == EXITED)
		ft_putstr("Exited");
}

void	ft_collect_job_status(void)
{
	t_list	*tmp;
	t_job	*job;

	tmp = g_jobs;
	while (tmp)
	{
		job = tmp->content;
		ft_stoped(job);
		ft_terminated(job);
		(job->status == EXITED) ? ft_update_p(1) : 0;
		tmp = tmp->next;
	}
}

void	ft_job_processing(void)
{
	t_list	*tmp;
	t_job	*job;
	t_list	*pr;

	tmp = g_jobs;
	pr = NULL;
	ft_update_p(0);
	ft_update_index();
	while (tmp)
	{
		job = tmp->content;
		if (job->status == STOPED && !job->mark_stop)
		{
			job->mark_stop = 1;
			ft_print_termsig_back(32, job->cmd, job->index, job->p);
		}
		if (job->status == EXITED)
		{
			ft_print_termsig_back(job->sig_term, job->cmd, job->index, job->p);
			ft_update_p(1);
			ft_remove_node(&tmp, &pr);
		}
		pr = tmp;
		tmp = tmp ? tmp->next : tmp;
	}
}
