/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:42:41 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/11/29 00:10:59 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	ft_remove_selections(t_cursor *pos, char *s)
{
	int		num_col;
	int		num_lines;
	int		save;

	num_col = ft_get_size_windz();
	num_lines = ft_get_num_of_lines(num_col, s, pos->p);
	ft_move_cursor_zero(*pos);
	tputs(tgetstr("cd", NULL), 0, my_outc);
	save = pos->x;
	pos->x = pos->p;
	ft_putstr_term(num_col, s, pos);
	pos->x = save;
	ft_set_last_position(*pos, num_lines);
}

void	ft_win_change(int sig)
{
	sig = 0;
	if (g_pos.cmd)
	{
		g_pos.num_col = ft_get_size_windz();
		tputs(tgetstr("cl", NULL), 0, my_outc);
		ft_putstr("\033[0;32m42sh $>\033[0m ");
		ft_putstr(g_pos.cmd);
		ft_get_end_of_line_pos(&g_pos, g_pos.cmd, g_pos.num_col);
		g_pos.num_lines = ft_get_num_of_lines(g_pos.num_col, \
		g_pos.cmd, g_pos.p);
		g_pos.index = ft_strlen(g_pos.cmd);
		g_pos.x = g_pos.end[g_pos.num_lines - 1];
		g_pos.y = g_pos.num_lines - 1;
	}
}

void	print_tab(char spaces, int num_col, int *x)
{
	int i;

	i = -1;
	while (++i < spaces)
	{
		if (*x == num_col - 1)
		{
			tputs(tgetstr("do", NULL), 0, my_outc);
			*x = 0;
			break;
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

	//int fd = open("/dev/ttys004", O_WRONLY);
	i = 0;
	x = pos->x;
	// /dprintf(fd,"--- start with x= %d \n",x);
	while (s[i])
	{
		if (s[i] < 0)
		{
			//dprintf(fd, "put : %d | num_col: %d\n", s[i], num_col);
			print_tab(s[i] * -1, num_col, &x);
		}
		else
		{
			ft_putchar(s[i]);
			//dprintf(fd," x= %d , num_col - 1  = %d and \n",x,num_col - 1 );
			if (x == num_col - 1 || s[i] == '\n')
			{
				if (x == num_col - 1 && s[i] != '\n')
				{
			//		dprintf(fd, "down\n");
					tputs(tgetstr("do", NULL), 0, my_outc);
				}
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

void	put_tab(char **s, t_cursor *pos)
{
	int spaces;
	int i;

	//int fd = open("/dev/ttys006", O_WRONLY);
	//dprintf(fd, "|col: %d|\n", pos->x);
	spaces = 8 - (pos->x % 8);
	//dprintf(fd, "|%d|\n", spaces * -1);
	i = -1;
	while (++i < spaces)
	{
		if (pos->x == pos->num_col - 1)
		{
			pos->end[pos->y] = pos->x;
			tputs(tgetstr("do", NULL), 0, my_outc);
			pos->x = 0;
			pos->y++;
			break;
		}
		else
		{
			pos->x++;
			pos->end[pos->y] = pos->x;
		}
	}
	pos->index++;
	*s = ft_strjoir(*s, (char[2]){spaces * -1, '\0'}, 1);
	ft_move_cursor_zero(*pos);
	tputs(tgetstr("cd", NULL), 0, my_outc);
	ft_putstr_term(pos->num_col, *s, pos);
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
		put_tab(s, pos);
		return ;
	}
	while ((ft_isprint(buf[i]) || buf[i] == '\n') && i < 6)
	{
		if (!(*s = ft_putline(buf[i++], *s, pos)))
			return ;
	}
}
