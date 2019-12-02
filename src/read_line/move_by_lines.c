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

int		ft_next_tab(t_cursor *pos, char *s, int save_x, int *bye)
{
	int sp;

	sp = s[pos->index] * -1;
	if ((pos->x >= save_x || pos->x > pos->end[pos->y]) && *bye)
		return (1);
	else if (pos->x + sp > pos->end[pos->y] && !*bye)
	{
		*bye = 1;
		pos->x = 0;
		pos->y++;
	}
	else
		pos->x += sp;
	return (0);
}

void	ft_next_line(t_cursor *pos, char *s)
{
	int save_x;
	int bye;

	save_x = (pos->x > pos->end[pos->y + 1]) ? pos->end[pos->y + 1] : pos->x;
	bye = 0;
	while (s[pos->index])
	{
		if (s[pos->index] < 0 && ft_next_tab(pos, s, save_x, &bye))
			break ;
		if (s[pos->index] > 0)
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
		}
		pos->index++;
	}
}

int		ft_prev_tab(t_cursor *pos, char *s, int save_x, int *bye)
{
	int sp;

	sp = s[pos->index] * -1;
	if (pos->x - sp <= save_x && *bye)
	{
		if (pos->x - sp == save_x || pos->x - sp == pos->p)
			pos->x -= sp;
		else
			pos->x -= sp - 1;
		if (pos->y == 0 && pos->x < pos->p)
			pos->x = pos->p;
		return (1);
	}
	else if ((pos->x == 0 || pos->x - sp < 0) && !*bye)
	{
		*bye = 1;
		pos->y--;
		pos->x = pos->end[pos->y];
	}
	else
	{
		pos->x -= sp;
		(pos->y == 0 && pos->x < pos->p) ? pos->x = pos->p : 0;
	}
	return (0);
}

void	ft_prev_line(t_cursor *pos, char *s)
{
	int save_x;
	int bye;
	int bl;

	save_x = (pos->x > pos->end[pos->y - 1]) ? pos->end[pos->y - 1] : pos->x;
	bye = 0;
	bl = (s[pos->index++] == '\0') ? 1 : 0;
	while (--pos->index >= 0)
	{
		if (s[pos->index] < 0 && ft_prev_tab(pos, s, save_x, &bye))
			break ;
		if (s[pos->index] <= 0)
			continue ;
		if (pos->x == save_x && bye)
			break ;
		if (pos->x == 0 && !bye)
		{
			bye = 1;
			pos->y--;
			pos->x = pos->end[pos->y];
		}
		else
			pos->x--;
	}
	(pos->index == -1 || bl) ? pos->index++ : 0;
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
	ft_get_end_of_line_pos(pos, s, num_col);
	if (ALT_DO == CAST(buf))
	{
		tputs(tgetstr("cd", NULL), 0, my_outc);
		ft_putstr_term(num_col, s + pos->index, pos);
		ft_next_line(pos, s);
		tab_set_last_position(*pos, num_lines);
	}
	if (ALT_UP == CAST(buf) && pos->y != 0)
	{
		tputs(tgetstr("cd", NULL), 0, my_outc);
		ft_putstr_term(num_col, s + pos->index, pos);
		ft_prev_line(pos, s);
		tab_set_last_position(*pos, num_lines);
	}
}
