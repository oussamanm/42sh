/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:32:46 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/09/24 19:32:48 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_free_job(t_job *job)
{
	t_list	*lst;
	t_list	*to_del;

	lst = job->proc;
	while (lst)
	{
		ft_memdel(&lst->content);
		to_del = lst;
		lst = lst->next;
		free(to_del);
	}
	ft_strdel(&job->cmd);
	free(job);
}

void	ft_remove_node(t_list *tmp, t_list *pr)
{
	if (pr == NULL)
	{
		tmp = tmp->next;
		ft_free_job(jobs->content);
		free(jobs);
		jobs = tmp;
	}
	else
	{
		pr->next = tmp->next;
		ft_free_job(tmp->content);
		free(tmp);
		tmp = pr;
	}
}

void	ft_add_job(t_job *job)
{
	(!jobs) ? (jobs = ft_lstnew(NULL, sizeof(t_job))) :
	(ft_lstadd(&jobs, ft_lstnew(NULL, sizeof(t_job))));
	jobs->content = job;
	ft_update_p();
}

void	ft_lstadd_last(t_list **alst, t_list *new, t_process *proc)
{
	t_list *tmp;

	tmp = *alst;
	while (*alst != NULL)
	{
		*alst = (*alst)->next;
	}
	*alst = new;
	(*alst)->content = proc;
	*alst = tmp;
}
