/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:51:04 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/07/07 14:51:06 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	ft_move_cursor_zero(t_cursor pos)
{
	ft_move_left(pos.x);
	while (pos.y-- > 0)
		tputs(tgetstr("up", NULL), 0, my_outc);
	ft_move_right(pos.p);
}

int		ft_get_num_of_lines(int num_col, char *s, int p)
{
	int num_lines;
	int i;
	int j;

	i = 0;
	num_lines = 1;
	j = p;
	while (s[i])
	{
		if (j == num_col - 1 || s[i] == '\n')
		{
			num_lines++;
			j = 0;
		}
		else
			j++;
		i++;
	}
	return (num_lines);
}

void	ft_get_end_of_line_pos(t_cursor *pos, char *s, int num_col)
{
	int i;
	int x;
	int y;

	i = -1;
	x = pos->p;
	y = 0;
	ft_init_size_end_line(pos);
	while (s[++i])
	{
		if (x == num_col - 1 || s[i] == '\n')
		{
			pos->end[y] = x;
			x = 0;
			y++;
		}
		else
			x++;
	}
	pos->end[y] = x;
}

/*
** - function set the cursor to right position after printing the line.
*/

void	ft_set_last_position(t_cursor pos, int num_lines)
{
	int y;
	int real_pos;

	y = num_lines - 1;
	real_pos = pos.end[num_lines - 1];
	while (pos.y < y--)
		tputs(tgetstr("up", NULL), 0, my_outc);
	if (real_pos > pos.x)
		while (real_pos-- > pos.x)
			tputs(tgetstr("le", NULL), 0, my_outc);
	else if (real_pos < pos.x)
		while (real_pos++ < pos.x)
			tputs(tgetstr("nd", NULL), 0, my_outc);
}
