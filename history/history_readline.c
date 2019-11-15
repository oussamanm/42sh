/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:09:57 by aboukhri          #+#    #+#             */
/*   Updated: 2019/10/12 16:21:01 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read_line.h"

static void	new_line(char *line, t_cursor *pos)
{
	ft_move_cursor_zero(*pos);
	tputs(tgetstr("cd", NULL), 0, my_outc);
	ft_putstr_term(pos->num_col, line, pos);
	ft_get_end_of_line_pos(pos, line, pos->num_col);
	pos->num_lines = ft_get_num_of_lines(pos->num_col, line, pos->p);
	pos->index = ft_strlen(line);
	pos->x = pos->end[pos->num_lines - 1];
	pos->y = pos->num_lines - 1;
}

void    history_readline(t_history *history, int key, char *cmd, t_cursor *cursor)
{
    static int pos;
    static t_info *last;
    static char *line;

    if (key == ENTER)
    {
        insert_history(history, cmd);
        history_file(cmd);
        last = history->tail;
        pos = history->len + 1;
    }
    else if (key == UP && pos > 1)
    {
        pos--;
        (pos == history->len) && (line = cmd);
        last = get_history_cmd(last, pos, history->len);
        new_line(last->cmd, cursor);
    }
    else if (key == DO && pos <= history->len)
    {
        pos++;
        if (pos == history->len + 1)
            new_line(line, cursor);
        else
        {
            last = get_history_cmd(last, pos, history->len);
            new_line(last->cmd, cursor);
        }
    }
}

