/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:42:41 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/07/07 14:42:43 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

/*
** - function stock the line returned by the read line function.
*/

void	ft_stock_history(char **history, char *line, int his_count)
{
	int i;

	i = 1;
	if (!line || !history)
		return ;
	if (his_count < MAX_HISTORY)
	{
		free(history[his_count]);
		history[his_count] = ft_strdup(line);
	}
	else
	{
		free(history[0]);
		while (i < MAX_HISTORY)
		{
			history[i - 1] = history[i];
			i++;
		}
		history[MAX_HISTORY - 1] = ft_strdup(line);
	}
}

/*
** -function clear the displayed line and print the old line stocked in
** the history table .
** -set the new position parameters of the cursor.
*/

void	ft_print_history(t_history *his, char *buf, char **s, t_cursor *pos)
{
	char *tp;

	if (!(*s) || (UP == CAST(buf) && his->his_count == 0)
		|| (DO == CAST(buf) && !his->history[his->his_count + 1]))
		return ;
	ft_move_cursor_zero(*pos);
	tputs(tgetstr("cd", NULL), 0, my_outc);
	if (UP == CAST(buf))
	{
		his->his_count--;
		ft_stock_history(his->history, *s, his->his_count + 1);
	}
	else
		his->his_count++;
	pos->x = pos->p;
	ft_putstr_term(pos->num_col, his->history[his->his_count], pos);
	ft_get_end_of_line_pos(pos, his->history[his->his_count], pos->num_col);
	tp = his->history[his->his_count];
	pos->num_lines = ft_get_num_of_lines(pos->num_col, tp, pos->p);
	pos->index = ft_strlen(his->history[his->his_count]);
	pos->x = pos->end[pos->num_lines - 1];
	pos->y = pos->num_lines - 1;
	ft_strdel(s);
	*s = ft_strdup(his->history[his->his_count]);
}
