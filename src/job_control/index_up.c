/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:32:46 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/09/24 19:32:48 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_update_p(void)
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
			job->p = '+';
		if (add == 1)
			job->p = '-';
		if (add > 1)
			job->p = 0;
		add++;
		tmp = tmp->next;
	}
}

int			ft_lst_len(t_list *tmp)
{
	int i;

	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void		ft_update_index(void)
{
	t_list	*tmp;
	t_job	*job;
	int		len;

	tmp = jobs;
	len = ft_lst_len(tmp);
	while (tmp)
	{
		job = tmp->content;
		job->index = len--;
		tmp = tmp->next;
	}
}

int			ft_job_index(void)
{
	t_job *job;

	if (jobs)
	{
		job = jobs->content;
		return (job->index + 1);
	}
	return (1);
}
