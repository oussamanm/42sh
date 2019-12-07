/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 21:36:54 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/12/04 01:26:40 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

/*
** - function clear the our line from the selection.
** - move the cursor in the last of the line.
*/

void	ft_enter(t_cursor *pos, char *s)
{
	ft_putstr_term(pos->num_col, s + pos->index, pos);
	ft_putchar('\n');
}

char	*ft_call_complete(t_select *select, char *s, char *buf)
{
	if (LE == CAST(buf) || RI == CAST(buf))
		ft_see_touch(buf, s, &g_pos);
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
	if (CTRL_D == CAST(buf))
		s = ft_ctrl_d(&g_pos, his, select, s);
	else if (CTRL_T == CAST(buf))
		tab_mode(&s);
	else if (ALT_UP == CAST(buf) || ALT_DO == CAST(buf))
		ft_move_by_lines(&g_pos, s, buf);
	else if (HOME == CAST(buf) || END == CAST(buf))
		ft_home_end(&g_pos, s, buf);
	else if (RI_WOR == CAST(buf) || LE_WOR == CAST(buf))
		ft_move_by_word(&g_pos, s, buf);
	else if (DEL == CAST(buf))
		s = ft_delcolomn(s, &g_pos);
	else if (UP == CAST(buf) || DO == CAST(buf))
		history_readline(his, CAST(buf), &s);
	else
		s = ft_call_complete(select, s, buf);
	return (s);
}

/*
** - function filter the keys tap by the user and call all functions
** needed to edit the line returned to our shell.
*/

int		ft_calling_center(t_history *his, t_select *select, char *buf)
{
	g_pos.num_lines = ft_get_num_of_lines(g_pos.num_col, g_pos.cmd, g_pos.p);
	ft_get_end_of_line_pos(&g_pos, g_pos.cmd, g_pos.num_col);
	if (!(g_pos.cmd = ft_key_call_func(his, select, g_pos.cmd, buf))
		|| g_pos.cmd[0] == EXIT_CLD)
		return (1);
	return (0);
}

char	*ft_read_line(t_history *his, t_select *select, int p)
{
	char	buf[6];
	int 	crash;
	
	crash = 0;
	// crash = open("/tmp/crash.fifo", O_RDONLY);
	ft_initial(p);
	ft_bzero(buf, 6);
	ft_enable();
	while (read(crash, buf, 6) > 0)
	{
		if (CTRL_R == CAST(buf))
		{
			ft_bzero(buf, 6);
			history_search(*his, &g_pos.cmd, buf);
		}
		if (ENTER == CAST(buf))
		{
			ft_enter(&g_pos, g_pos.cmd);
			break ;
		}
		if (ft_calling_center(his, select, buf))
			break ;
		ft_bzero(buf, 6);
	}
	ft_disable();
	free(g_pos.end);
	// if (crash != 0)
	// 	close(crash);
	convert_neg_to_tab(&g_pos.cmd);
	return (g_pos.cmd);
}
