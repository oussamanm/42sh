/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_cursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:51:04 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/07/07 14:51:06 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	ft_move_left(int n)
{
	while (n--)
		tputs(tgetstr("le", NULL), 0, my_outc);
}

void	ft_move_right(int n)
{
	while (n--)
		tputs(tgetstr("nd", NULL), 0, my_outc);
}

void	ft_movecur_up_and_right(int up, int size)
{
	while (up--)
		tputs(tgetstr("up", NULL), 0, my_outc);
	while (size--)
		tputs(tgetstr("nd", NULL), 0, my_outc);
}

void	ft_right_touch(t_cursor *pos, int size)
{
	if (pos->x == pos->end[pos->y] && pos->index < size)
	{
		pos->index++;
		pos->x = 0;
		pos->y++;
		tputs(tgetstr("do", NULL), 0, my_outc);
	}
	else if (pos->index < size)
	{
		tputs(tgetstr("nd", NULL), 0, my_outc);
		pos->index++;
		pos->x++;
	}
}

/*
** - function move the cursor to the right character or to the left
** character inside the shell line.
*/

void	ft_see_touch(char *buf, char *s, t_cursor *pos)
{
	int		size;

	size = ft_strlen(s);
	if (LE == CAST(buf) && pos->x == 0)
	{
		pos->index--;
		pos->y--;
		pos->x = pos->end[pos->y];
		ft_movecur_up_and_right(1, pos->x);
	}
	else if (LE == CAST(buf) && pos->index != 0)
	{
		pos->index--;
		pos->x--;
		tputs(tgetstr("le", NULL), 0, my_outc);
	}
	else if (RI == CAST(buf))
		ft_right_touch(pos, size);
}
