/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_by_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:41:24 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/12/04 18:45:26 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	num_lines_(int *x, int *y, int end, int c)
{
	if (*x == end || c == '\n')
	{
		*y += 1;
		*x = 0;
	}
	else
		*x += 1;
}

void	move_to_pos(char *s, t_cursor *pos, int col, int line)
{
	int x;
	int y;
	int i;

	i = -1;
	x = pos->p;
	y = 0;
	while (s[++i])
	{
		if (line == y && ((s[i] < 0 && ((s[i] * -1) + x > col ||
		(s[i] * -1) + x > pos->end[y])) || x >= col || x >= pos->end[y]))
		{
			pos->x = x;
			pos->index = i;
			return ;
		}
		(s[i] < 0) ? num_lines_tab(s[i] * -1, pos, &x, &y)
		: num_lines_(&x, &y, pos->end[y], s[i]);
	}
	if (x >= col || x >= pos->end[line])
	{
		pos->x = x;
		pos->index = i - 1;
	}
}

void	move_line(int x, int dir)
{
	if (dir)
		tputs(tgetstr("do", NULL), 0, my_outc);
	else
		tputs(tgetstr("up", NULL), 0, my_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, x), 0, my_outc);
}

void	ft_move_by_lines(t_cursor *pos, char *s, char *buf)
{
	int num_col;
	int num_lines;

	num_col = ft_get_size_windz();
	ft_get_end_of_line_pos(pos, s, num_col);
	num_lines = ft_get_num_of_lines(num_col, s, pos->p);
	pos->num_col = num_col;
	if (ALT_DO == CAST(buf) && pos->y < num_lines - 1)
	{
		pos->y++;
		(pos->x > pos->end[pos->y]) && (pos->x = pos->end[pos->y]);
		move_to_pos(s, pos, pos->x, pos->y);
		move_line(pos->x, 1);
	}
	if (ALT_UP == CAST(buf) && pos->y > 0)
	{
		pos->y--;
		if (pos->x > pos->end[pos->y])
			pos->x = pos->end[pos->y];
		else if (pos->y == 0 && pos->x < pos->p)
			pos->x = pos->p;
		move_to_pos(s, pos, pos->x, pos->y);
		move_line(pos->x, 0);
	}
}
