/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:32:46 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/09/24 19:32:48 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char 			*ft_cmd_value(t_tokens *st_tokens, char *cmd)
{
	while (st_tokens)
	{
		cmd = ft_strjoir_rtn(cmd, st_tokens->value, 1);
		cmd = ft_strjoir_rtn(cmd, " ", 1);
		st_tokens = st_tokens->next;
	}
	return (cmd);
}

t_job	*ft_inisial_job(void)
{
	t_job *job;

	job = ft_memalloc(sizeof(t_job));
	job->pgid = -1;
	job->index = ft_job_index();
	job->background = -1;
	job->proc = NULL;
	job->status = 0;
	job->mark_stop = 0;
	job->sig_term = 0;
	job->p = '+';
	job->cmd = ft_strdup("");
	return (job);
}

void	ft_fill_process(int pid, t_job *job)
{
	t_process	*process;
	t_list		*tmp;

	process = ft_memalloc(sizeof(t_process));
	process->pid = pid;
	process->status = RUN;
	process->exit_status = 0;
	tmp = job->proc;
	if (!job->proc)
	{
		job->proc = ft_lstnew(NULL, sizeof(t_process));
		job->proc->content = process;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_lstnew(NULL, sizeof(t_process));
		tmp->next->content = process;
	}
}
