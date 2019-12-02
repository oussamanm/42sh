/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:42:41 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/12/01 11:38:00 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	ft_win_change(int sig)
{
	sig = 0;
	if (g_pos.cmd)
	{
		g_pos.num_col = ft_get_size_windz();
		tputs(tgetstr("cl", NULL), 0, my_outc);
		ft_putstr_fd("\033[0;32m42sh $>\033[0m ", 2);
		ft_putstr_term(g_pos.num_col, g_pos.cmd, &g_pos);
		ft_get_end_of_line_pos(&g_pos, g_pos.cmd, g_pos.num_col);
		g_pos.num_lines = ft_get_num_of_lines(g_pos.num_col, \
		g_pos.cmd, g_pos.p);
		g_pos.index = ft_strlen(g_pos.cmd);
		g_pos.x = g_pos.end[g_pos.num_lines - 1];
		g_pos.y = g_pos.num_lines - 1;
	}
}

void	print_tab(int num_col, int *x)
{
	int i;
	int spaces;

	i = -1;
	spaces = 8 - (*x % 8);
	while (++i < spaces)
	{
		if (*x == num_col - 1)
		{
			tputs(tgetstr("do", NULL), 0, my_outc);
			*x = 0;
			break ;
		}
		else
		{
			ft_putchar(' ');
			*x += 1;
		}
	}
}

void	ft_putstr_term(int num_col, char *s, t_cursor *pos)
{
	int i;
	int x;

	i = 0;
	x = pos->x;
	while (s[i])
	{
		if (s[i] < 0)
			print_tab(num_col, &x);
		else
		{
			ft_putchar(s[i]);
			if (x == num_col - 1 || s[i] == '\n')
			{
				if (x == num_col - 1 && s[i] != '\n')
					tputs(tgetstr("do", NULL), 0, my_outc);
				x = 0;
			}
			else
				x++;
		}
		i++;
	}
}

/*
** - function print and join the enter characters set the new cursor
** parameters.
*/

char	*ft_putline(char c, char *s, t_cursor *pos)
{
	char *new;
	char buff[2];

	buff[0] = c;
	buff[1] = '\0';
	ft_putchar(buff[0]);
	if (pos->x == pos->num_col - 1 || c == '\n')
	{
		pos->end[pos->y] = pos->x;
		if (c != '\n')
			tputs(tgetstr("do", NULL), 0, my_outc);
		pos->x = 0;
		pos->y++;
	}
	else
	{
		pos->x++;
		pos->end[pos->y] = pos->x;
	}
	pos->index++;
	new = ft_strjoin(s, buff);
	ft_strdel(&s);
	return (new);
}

/*
** - function filter the key pressed by the user and call the function
** ft_putline.
*/

void	ft_print_touch_and_join(t_cursor *pos, char *buf, char **s)
{
	int i;

	i = 0;
	if (ft_strcmp(buf, "\t") == 0)
	{
		*s = put_tab(*s, pos);
		return ;
	}
	while ((ft_isprint(buf[i]) || buf[i] == '\n') && i < 6)
	{
		if (!(*s = ft_putline(buf[i++], *s, pos)))
			return ;
	}
}
