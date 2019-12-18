/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 08:05:27 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/12/01 08:05:33 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_bg_content(t_job *job, char *arg)
{
	if ((job->status == STOPED && job->p == '+')
		|| (job->status == STOPED && arg))
	{
		ft_print_backcmd(job);
		job->background = 1;
		ft_run_job(job);
		ft_update_p(1);
		killpg(job->pgid, SIGCONT);
		return (1);
	}
	else if ((job->status == RUN && job->p == '+')
		|| (job->status == RUN && arg))
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

	(!g_jobs) ? ft_putendl_fd("42sh: bg: current: no such job", 2) : 0;
	if (arg)
	{
		(arg[0] == '%') ? arg++ : 0;
		(index = ft_atoi(arg)) : 0;
	}
	tmp = g_jobs;
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
