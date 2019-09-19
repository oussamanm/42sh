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

void	ft_pos_of_left_select(t_cursor *pos)
{
	if (pos->x == 0 && pos->index != 0)
	{
		pos->y--;
		pos->x = pos->end[pos->y];
	}
	else if (pos->index != 0)
		pos->x--;
}

void	ft_first_left_select(t_cursor *pos, t_select *select, char *s)
{
	if (pos->index != 0)
	{
		select->start = pos->index;
		select->end = pos->index;
		pos->i = pos->index;
		ft_print_with_reverse_mode(s, select->start, select->end, pos);
	}
	else
		ft_putstr_term(pos->num_col, s, pos);
}

void	ft_remove_left(t_cursor *pos, t_select *select, char *s, int *let)
{
	int len;

	len = ft_strlen(s);
	select->end--;
	if (pos->x == 0 && pos->index != 0)
		ft_movecur_up_and_right(1, pos->num_col);
	else
		tputs(tgetstr("le", NULL), 0, my_outc);
	tputs(tgetstr("cd", NULL), 0, my_outc);
	ft_pos_of_left_select(pos);
	ft_putstr_term(pos->num_col, s + select->end + 1, pos);
	if ((select->start == select->end + 1) &&
		(pos->index < len - 1 && pos->index > select->end + 1))
	{
		select->start = -1;
		select->end = -1;
	}
	*let = 1;
}

void	ft_select_left_one(t_cursor *pos, t_select *select, char *s)
{
	if (select->end != 0)
		select->end--;
	pos->i = select->end;
	ft_print_with_reverse_mode(s, select->end, select->start, pos);
}

void	ft_left_selection(char *s, t_cursor *pos, t_select *select)
{
	int len;
	int let;

	let = 0;
	len = ft_strlen(s);
	pos->num_lines = ft_get_num_of_lines(pos->num_col, s, pos->p);
	if (pos->index <= len && pos->index >= 0 && len != 0)
	{
		tputs(tgetstr("cd", NULL), 0, my_outc);
		if (select->end == -1 && select->start == -1)
			ft_first_left_select(pos, select, s);
		else if ((select->start < select->end)
			|| ((select->start == select->end)
				&& (pos->index < len - 1 && pos->index >= select->end)))
			ft_remove_left(pos, select, s, &let);
		else if ((select->start > select->end)
			|| ((select->start == select->end)
				&& (pos->index == len - 1 || pos->index < select->end)))
			ft_select_left_one(pos, select, s);
		ft_get_end_of_line_pos(pos, s, pos->num_col);
		(!let) ? ft_pos_of_left_select(pos) : 0;
		ft_set_last_position(*pos, pos->num_lines);
		(pos->index != 0) ? pos->index-- : 0;
	}
}
