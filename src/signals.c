/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:35:32 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/07 06:09:40 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

void	ft_catch_sigchild(int sig)
{
	sig = 0;
	ft_wait(NULL);
}

/*
** ft_catch_signal : CTR + c
*/

void	ft_catch_signal(int signal)
{
	UNUSED(signal);
	if (g_sign)
		ft_putchar('\n');
	else
	{
		ft_putstr_term(g_pos.num_col, g_pos.cmd + g_pos.index, &g_pos);
		g_pos.index = 0;
		g_pos.x = 8;
		g_pos.y = 0;
		g_pos.num_col = ft_get_size_windz();
		ft_strdel(&(g_pos.cmd));
		g_pos.cmd = ft_strnew(0);
		if (g_pos.p != 8)
		{
			g_pos.exit = 1;
			ioctl(0, TIOCSTI, "\12");
		}
		else
			ft_putstr("\n\033[0;32m42sh $>\033[0m ");
		g_pos.p = 8;
	}
}

void	call_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_catch_signal);
	signal(SIGWINCH, ft_win_change);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCHLD, ft_catch_sigchild);
}

void	ft_signal_default(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}
