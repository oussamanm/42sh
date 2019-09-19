/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_by_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:41:24 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/06/11 19:41:31 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	ft_next_line(t_cursor *pos, char *s)
{
	int save_x;
	int bye;

	save_x = (pos->x > pos->end[pos->y + 1]) ? pos->end[pos->y + 1] : pos->x;
	bye = 0;
	while (s[pos->index])
	{
		if (pos->x == pos->end[pos->y] && !bye)
		{
			bye = 1;
			pos->x = 0;
			pos->y++;
		}
		else if (pos->x == save_x && bye)
			break ;
		else
			pos->x++;
		pos->index++;
	}
}

void	ft_last_line(t_cursor *pos)
{
	int save_x;
	int bye;

	save_x = (pos->x > pos->end[pos->y - 1]) ? pos->end[pos->y - 1] : pos->x;
	bye = 0;
	while (pos->index > 0)
	{
		if (pos->x == 0 && !bye)
		{
			bye = 1;
			pos->y--;
			pos->x = pos->end[pos->y];
		}
		else if (pos->x == save_x && bye)
			break ;
		else
			pos->x--;
		pos->index--;
	}
}

/*
** -function move the cursor to the next line when we press
** ALT down or the last when we press ALT Up.
*/

void	ft_move_by_lines(t_cursor *pos, char *s, char *buf)
{
	int num_col;
	int num_lines;

	num_col = ft_get_size_windz();
	num_lines = ft_get_num_of_lines(num_col, s, pos->p);
	if (ALT_DO == CAST(buf))
	{
		tputs(tgetstr("cd", NULL), 0, my_outc);
		ft_putstr_term(num_col, s + pos->index, pos);
		ft_next_line(pos, s);
		ft_set_last_position(*pos, num_lines);
	}
	if (ALT_UP == CAST(buf))
	{
		tputs(tgetstr("cd", NULL), 0, my_outc);
		ft_putstr_term(num_col, s + pos->index, pos);
		ft_last_line(pos);
		ft_set_last_position(*pos, num_lines);
	}
}
