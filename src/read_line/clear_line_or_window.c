/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_line_or_window.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 05:17:11 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/08/07 05:17:18 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	ft_ctrl_l(t_cursor *pos, char *s)
{
	int save;

	tputs(tgetstr("cl", NULL), 1, my_outc);
	(pos->p == 8) ? ft_putstr("\033[0;32m21sh $>\033[0m ") : 0;
	(pos->p == 9) ? ft_putstr("heredoc> ") : 0;
	(pos->p == 7) ? ft_putstr("quote> ") : 0;
	(pos->p == 10) ? ft_putstr("dquotes>> ") : 0;
	if (ft_strlen(s) != 0)
	{
		save = pos->x;
		pos->x = pos->p;
		ft_putstr_term(pos->num_col, s, pos);
		pos->x = save;
		pos->num_lines = ft_get_num_of_lines(pos->num_col, s, pos->p);
		ft_get_end_of_line_pos(pos, s, pos->num_col);
		ft_set_last_position(*pos, pos->num_lines);
	}
}

char	*ft_clear(t_cursor *pos, char *s, char *buf)
{
	if (CTRL_U == CAST(buf))
	{
		ft_move_cursor_zero(*pos);
		tputs(tgetstr("cd", NULL), 1, my_outc);
		ft_strdel(&s);
		s = ft_strnew(0);
		pos->index = 0;
		pos->x = pos->p;
		pos->y = 0;
	}
	else if (CTRL_L == CAST(buf))
		ft_ctrl_l(pos, s);
	return (s);
}
