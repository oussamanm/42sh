/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 21:56:04 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/04/24 21:56:07 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	ft_print_with_reverse_mode(char *s, int start, int end, t_cursor *pos)
{
	int x;

	x = pos->x;
	while (s[pos->i])
	{
		if (start <= pos->i && pos->i <= end)
		{
			ft_putstr("\033[0;32m");
			tputs(tgetstr("mr", NULL), 0, my_outc);
			ft_putchar(s[pos->i]);
			tputs(tgetstr("me", NULL), 0, my_outc);
			ft_putstr("\033[0m");
		}
		else
			ft_putchar(s[pos->i]);
		if (x == pos->num_col - 1 || s[pos->i] == '\n')
		{
			if (x == pos->num_col - 1 && s[pos->i] != '\n')
				tputs(tgetstr("do", NULL), 0, my_outc);
			x = 0;
		}
		else
			x++;
		pos->i++;
	}
}

void	ft_pos_of_right_select(t_cursor *pos)
{
	if (pos->x == pos->end[pos->y])
	{
		pos->x = 0;
		pos->y++;
	}
	else
		pos->x++;
}

void	ft_first_right_select(t_cursor *pos, t_select *select, char *s)
{
	select->start = pos->index;
	select->end = pos->index;
	ft_print_with_reverse_mode(s, pos->index, pos->index, pos);
	pos->index++;
}

void	ft_remove_right(t_cursor *pos, t_select *select, char *s, int *let)
{
	if (select->end != 0)
	{
		pos->index++;
		if (pos->x == pos->end[pos->y])
			tputs(tgetstr("do", NULL), 0, my_outc);
		else
			tputs(tgetstr("nd", NULL), 0, my_outc);
	}
	else
		pos->x--;
	tputs(tgetstr("cd", NULL), 0, my_outc);
	select->end++;
	pos->i = pos->index;
	ft_pos_of_right_select(pos);
	ft_print_with_reverse_mode(s, select->end, select->start, pos);
	if (select->end - 1 == select->start)
	{
		select->start = -1;
		select->end = -1;
	}
	*let = 1;
}

void	ft_selection(char *s, t_cursor *pos, char *buf, t_select *select)
{
	int len;
	int let;

	len = ft_strlen(s);
	pos->num_lines = ft_get_num_of_lines(pos->num_col, s, pos->p);
	pos->i = pos->index;
	if (SEL_RI == CAST(buf) && pos->index < len && !(let = 0))
	{
		if (select->end == -1 && select->start == -1)
			ft_first_right_select(pos, select, s);
		else if (select->start < select->end ||
		(select->start == select->end && pos->index > select->end))
		{
			select->end++;
			ft_print_with_reverse_mode(s, pos->index, pos->index++, pos);
		}
		else if (select->start > select->end ||
			(select->start == select->end && pos->index < select->end))
			ft_remove_right(pos, select, s, &let);
		ft_get_end_of_line_pos(pos, s, pos->num_col);
		(let) ? 0 : ft_pos_of_right_select(pos);
		ft_set_last_position(*pos, pos->num_lines);
	}
	else if (SEL_LE == CAST(buf) && pos->index >= 0)
		ft_left_selection(s, pos, select);
}
