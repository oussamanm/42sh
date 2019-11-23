/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:32:46 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/09/24 19:32:48 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

int		ft_termsig_fore(int sig, char *name)
{
	char	*msg;

	msg = ft_strsignal(sig);
	if (msg && sig != 2)
	{
		ft_putstr("42sh : ");
		ft_putstr(msg);
		ft_putstr(" : ");
		ft_putnbr(sig);
		ft_putstr("\t ");
		ft_putendl(name);
	}
	else
		return (0);
	return (1);
}

int		ft_print_termsig_back(int sig, char *name, int index, char p)
{
	char *msg;

	msg = ft_strsignal(sig);
	if (msg)
	{
		ft_putchar('[');
		ft_putnbr(index);
		ft_putchar(']');
		(p != 0) ? ft_putchar(p) : ft_putchar(' ');
		ft_putstr("  ");
		ft_putstr(msg);
		ft_putstr("\t\t\t");
		ft_putendl(name);
	}
	else
		return (0);
	return (1);
}

void	ft_print_backcmd(t_job *job)
{
	ft_putchar('[');
	ft_putnbr(job->index);
	ft_putchar(']');
	(job->p) ? ft_putchar(job->p) : ft_putchar(' ');
	ft_putchar(' ');
	ft_putstr(job->cmd);
	ft_putstr(" &\n");
}

void	ft_print_pid(int index, int pgid)
{
	ft_putchar('[');
	ft_putnbr(index);
	ft_putchar(']');
	ft_putchar(' ');
	ft_putnbr(pgid);
	ft_putchar('\n');
}
