/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 18:21:28 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/08/03 18:21:30 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

char	*ft_read_heredoc(char *eol)
{
	char		*line;
	t_select	*select;

	select = NULL;
	line = NULL;
	save_address(&select);
	while (1337)
	{
		ft_putstr("heredoc> ");
		ft_read_line(&g_history, select, 9);
		if (ft_strequ(g_pos.cmd, eol) || (g_pos.cmd != NULL\
			&& g_pos.cmd[0] == -1) || g_pos.exit)
		{
			g_exit_status = (g_pos.exit) ? 1 : 0;
			ft_strdel(&g_pos.cmd);
			history_readline(&g_history, 0, NULL);
			break ;
		}
		(!line) ? (line = ft_strnew(0)) : 0;
		(!g_pos.cmd) ? (g_pos.cmd = ft_strnew(0)) : 0;
		line = ft_strjoir(line, g_pos.cmd, 3);
		g_pos.cmd = NULL;
		line = ft_strjoir(line, "\n", 1);
	}
	return (line);
}
