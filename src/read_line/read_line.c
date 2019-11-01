/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 21:36:54 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/07/18 12:31:36 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

/*
** - function clear the our line from the selection.
** - move the cursor in the last of the line.
*/

void	ft_enter(t_cursor *pos, char *s, t_select *select)
{
	if (select->start != -1 && select->end != -1)
	{
		ft_remove_selections(pos, s);
		select->start = -1;
		select->end = -1;
	}
	ft_putstr_term(pos->num_col, s + pos->index, pos);
	ft_putchar('\n');
}

void	ft_clear_selection(t_select *select, t_cursor *pos, char *s, char *buf)
{
	ft_remove_selections(pos, s);
	if (CAST(buf) != COPY && CAST(buf) != CUT && CAST(buf) != PASTE)
	{
		select->start = -1;
		select->end = -1;
	}
}

char	*ft_call_complete(t_select *select, char *s, char *buf)
{
	if (LE == CAST(buf) || RI == CAST(buf))
		ft_see_touch(buf, s, &g_pos);
	else if (SEL_RI == CAST(buf) || SEL_LE == CAST(buf))
		ft_selection(s, &g_pos, buf, select);
	else if (COPY == CAST(buf) || PASTE == CAST(buf) || CUT == CAST(buf))
		ft_copy_paste(buf, &s, &g_pos, select);
	else if (CTRL_U == CAST(buf) || CTRL_L == CAST(buf))
		s = ft_clear(&g_pos, s, buf);
	else if (g_pos.index != (int)ft_strlen(s))
		s = ft_inside_line(s, &g_pos, buf);
	else
		ft_print_touch_and_join(&g_pos, buf, &s);
	return (s);
}

/*
** - function call the functions needed to edit our line.
*/

char	*ft_key_call_func(t_history *his, t_select *select, char *s, char *buf)
{
	if (CAST(buf) != SEL_RI && CAST(buf) != SEL_LE
	&& select->start != -1 && select->end != -1)
		ft_clear_selection(select, &g_pos, s, buf);
	if (TAB == CAST(buf))
		s = ft_auto_completion(&g_pos, his, s);
	else if (CTRL_D == CAST(buf))
		s = ft_ctrl_d(&g_pos, his, select, s);
	else if (ALT_UP == CAST(buf) || ALT_DO == CAST(buf))
		ft_move_by_lines(&g_pos, s, buf);
	else if (HOME == CAST(buf) || END == CAST(buf))
		ft_home_end(&g_pos, s, buf);
	else if (RI_WOR == CAST(buf) || LE_WOR == CAST(buf))
		ft_move_by_word(&g_pos, s, buf);
	else if (DEL == CAST(buf))
		s = ft_delcolomn(s, &g_pos);
	else if (UP == CAST(buf) || DO == CAST(buf))
		ft_print_history(his, buf, &s, &g_pos);
	else
		s = ft_call_complete(select, s, buf);
	return (s);
}

/*
** - function filter the keys tap by the user and call all functions
** needed to edit the line returned to our shell.
*/

char	*ft_read_line(t_history *his, t_select *select, int p)
{
	char	buf[6];

	ft_initial(p);
	ft_bzero(buf, 6);
	ft_enable();
	while (read(0, buf, 6) > 0)
	{
		if (ENTER == CAST(buf))
		{
			ft_enter(&g_pos, g_pos.cmd, select);
			break ;
		}
		if (!(g_pos.cmd = ft_key_call_func(his, select, g_pos.cmd, buf))
			|| g_pos.cmd[0] == -1)
			break ;
		ft_bzero(buf, 6);
	}
	ft_disable();
	free(g_pos.end);
	//(g_pos.cmd[0] != -1) ? g_pos.cmd = ft_strtrim_and_free(g_pos.cmd) : 0;
	return (g_pos.cmd);
}
