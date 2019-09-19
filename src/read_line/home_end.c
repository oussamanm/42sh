/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:09:35 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/06/11 18:09:37 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

/*
** - function set the cursor in the begin of line when the key pressed is "home"
** or in the end of line when the key pressed is "end".
*/

void	ft_home_end(t_cursor *pos, char *s, char *buf)
{
	int num_col;
	int num_lines;

	num_col = ft_get_size_windz();
	num_lines = ft_get_num_of_lines(num_col, s, pos->p);
	if (HOME == CAST(buf))
	{
		ft_move_cursor_zero(*pos);
		pos->x = 8;
		pos->y = 0;
		pos->index = 0;
	}
	if (END == CAST(buf))
	{
		ft_move_cursor_zero(*pos);
		tputs(tgetstr("cd", NULL), 0, my_outc);
		pos->x = pos->p;
		ft_putstr_term(pos->num_col, s, pos);
		pos->x = pos->end[num_lines - 1];
		pos->y = num_lines - 1;
		pos->index = ft_strlen(s);
	}
}
