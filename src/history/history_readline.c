/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:09:57 by aboukhri          #+#    #+#             */
/*   Updated: 2019/11/28 00:32:49 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"

/*
**	clear the line and rewrite it with the command given
*/

void	his_new_line(char *line, char **cmd, t_cursor *pos)
{
	ft_move_cursor_zero(*pos);
	pos->x = 8;
	pos->y = 0;
	tputs(tgetstr("cd", NULL), 0, my_outc);
	ft_putstr_term(pos->num_col, line, pos);
	ft_get_end_of_line_pos(pos, line, pos->num_col);
	pos->num_lines = ft_get_num_of_lines(pos->num_col, line, pos->p);
	pos->index = ft_strlen(line);
	pos->x = pos->end[pos->num_lines - 1];
	pos->y = pos->num_lines - 1;
	*cmd = ft_strdup(line);
}

static	t_info	*his_cmd_pos(t_info *last, int pos, char **cmd, int len)
{
	last = history_index(last, pos, len);
	his_new_line(last->cmd, cmd, &g_pos);
	*cmd = ft_strdup(last->cmd);
	return (last);
}

/*
**	navigate in history dependent on the key given
**	or insert new history in case enter is given
*/

void			history_readline(t_history *history, int key, char **cmd)
{
	static	int		pos;
	static	t_info	*last;
	static	char	*line;

	if (pos == 0 || key == 0)
	{
		ft_strdel(&line);
		last = history->tail;
		pos = history->len + 1;
		if (key == 0)
			return ;
	}
	if (key == UP && pos > 1 && last)
	{
		if ((--pos) == history->len)
		{
			ft_strdel(&line);
			line = ft_strdup(*cmd);
		}
		last = his_cmd_pos(last, pos, cmd, history->len);
	}
	else if (key == DO && pos <= history->len)
	{
		if (++pos == history->len + 1 && line)
			his_new_line(line, cmd, &g_pos);
		else if (last)
			last = his_cmd_pos(last, pos, cmd, history->len);
	}
}
