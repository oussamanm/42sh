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

int		ft_jobs_usage(char *str)
{
	ft_putstr_fd("42sh: jobs: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("usage: jobs [-lp] [jobspec ...]", 2);
	return (-1);
}

int		ft_get_jobs_arg(char **args, int *index)
{
	int i;
	int j;
	int ret;

	j = -1;
	ret = -2;
	while (args[++j])
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
			else
				return (ft_jobs_usage(args[j]));
		}
		else
			*index = ft_atoi(args[j]);
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

	tmp = g_jobs;
	index = 0;
	ar = ft_get_jobs_arg(args, &index);
	while (ar != -1 && tmp)
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
