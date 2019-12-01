/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:19:07 by aboukhri          #+#    #+#             */
/*   Updated: 2019/12/01 20:34:12 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"

/*
**	clear the line of cmds and print the new cmd that matches  the search given
*/

void			search_new_line(char *search, char *line,
								char **cmd, t_cursor *pos)
{
	pos->x = 8;
	pos->y = 0;
	tputs(tgetstr("cd", NULL), 0, my_outc);
	his_putstr_term(pos->num_col, line, search, pos);
	ft_get_end_of_line_pos(pos, line, pos->num_col);
	pos->num_lines = ft_get_num_of_lines(pos->num_col, line, pos->p);
	pos->index = ft_strlen(line);
	pos->x = pos->end[pos->num_lines - 1];
	pos->y = pos->num_lines - 1;
	*cmd = ft_strdup(line);
}

/*
**	return the nearest commnad in history that match the search (*s*)
*/

static	char	*history_strstr(t_info *last, char *search)
{
	while (last)
	{
		if (ft_strstr(last->cmd, search))
			return (ft_strdup(last->cmd));
		last = last->prev;
	}
	return (NULL);
}

/*
**	reset the command line after quiting ctrl+r feauture
*/

void			reset_search(char *cmd)
{
	g_pos.x = g_pos.p;
	g_pos.y = 0;
	tputs(tgetstr("cd", NULL), 0, my_outc);
	ft_putstr_term(g_pos.num_col, cmd, &g_pos);
	ft_get_end_of_line_pos(&g_pos, cmd, g_pos.num_col);
	g_pos.index = 0;
	g_pos.x = g_pos.p;
	g_pos.y = 0;
	g_pos.num_lines = ft_get_num_of_lines(g_pos.num_col, cmd, g_pos.p);
	his_cursor_up(g_pos, g_pos.num_lines - 1);
}

/*
**	remove the line and replace it by the new reslut  of the search given
**	or display fialing in case no result found
*/

static	void	his_edit_line(char *search, char *res, char **cmd)
{
	int	down;
	int	up;
	int	p;

	p = 14;
	up = ft_strlen(search);
	if (cmd && *cmd)
		g_pos.num_lines = ft_get_num_of_lines(g_pos.num_col, *cmd, g_pos.p);
	down = g_pos.num_lines - g_pos.y;
	if (res && search && (down = 1))
		search_new_line(search, res, cmd, &g_pos);
	else if (search)
		down = g_pos.num_lines;
	his_cursor_do(down);
	tputs(tgetstr("cd", NULL), 0, my_outc);
	if (!res && up > 0 && (p += 8))
		ft_putstr("failing ");
	up = g_pos.num_lines + ((up + p) / g_pos.num_col);
	ft_putstr("bck-i-search: ");
	ft_putstr(search);
	tputs(tgetstr("us", NULL), 0, my_outc);
	ft_putchar(' ');
	tputs(tgetstr("ue", NULL), 0, my_outc);
	his_cursor_up(g_pos, up);
}

/*
**	history search readline (write, delete, other key=quit)
*/

void			history_search(t_history his, char **s, char buf[6])
{
	char	*search;
	char	*res;
	int		len;

	his_edit_line(NULL, NULL, s);
	search = ft_strnew(1);
	g_pos.r = 1;
	while (read(0, buf, 6))
	{
		len = ft_strlen(search);
		if (DEL == CAST(buf))
			(len > 0) && (search[--len] = '\0');
		else if (ft_isallprint(buf) && (len += 1))
			search = ft_strjoir(search, buf, 1);
		else
		{
			reset_search(*s);
			ft_strdel(&search);
			break ;
		}
		res = (len == 0) ? ft_strnew(1) : history_strstr(his.tail, search);
		his_edit_line(search, res, s);
		ft_bzero(buf, 6);
		ft_strdel(&res);
	}
}
