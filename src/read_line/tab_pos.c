/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 23:34:18 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/12/01 23:34:19 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	new_pos_tab(char *s, int len, t_cursor *pos)
{
	int sp;
	int i;

	i = -1;
	while (s[++i] && i < len)
	{
		if (s[i] < 0)
		{
			sp = s[i] * -1;
			if (pos->x + sp > pos->end[pos->y])
			{
				pos->y++;
				pos->x = 0;
			}
			else
				pos->x += sp;
		}
		else
			ft_get_new_pos(pos, 1);
	}
}

void	tab_set_last_position(t_cursor pos, int num_lines)
{
	int y;

	y = num_lines - 1;
	while (pos.y < y--)
		tputs(tgetstr("up", NULL), 0, my_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, pos.x), 0, my_outc);
}

void	ft_go_to_left(t_cursor *pos, char *s)
{
	int sp;

	pos->index--;
	sp = s[pos->index] * -1;
	if (sp > 0)
	{
		ft_move_left(sp);
		pos->x -= sp;
	}
	else
	{
		pos->x--;
		tputs(tgetstr("le", NULL), 0, my_outc);
	}
}

void	ft_go_to_right(t_cursor *pos, char *s)
{
	int sp;

	sp = s[pos->index] * -1;
	if (sp > 0)
	{
		pos->index++;
		if (pos->x + sp > pos->num_col - 1)
		{
			pos->x = 0;
			pos->y++;
			tputs(tgetstr("do", NULL), 0, my_outc);
		}
		else
		{
			pos->x += sp;
			ft_move_right(sp);
		}
	}
	else
		ft_right_touch(pos, ft_strlen(s));
}

void	tab_mode(char **s)
{
	char buf[6];

	ft_bzero(buf, 6);
	read(0, buf, 6);
	ft_print_touch_and_join(&g_pos, buf, s);
}
