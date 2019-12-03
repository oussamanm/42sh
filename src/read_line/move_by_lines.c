/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_by_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:41:24 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/12/02 21:55:55 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

/*int		ft_next_tab(t_cursor *pos, char *s, int save_x, int *bye)
{
	int sp;

	sp = s[pos->index] * -1;
	if ((pos->x >= save_x || pos->x > pos->end[pos->y]) && *bye)
		return (1);
	else if (pos->x + sp > pos->end[pos->y] && !*bye)
	{
		*bye = 1;
		pos->x = 0;
		pos->y++;
	}
	else
		pos->x += sp;
	return (0);
}

void	ft_next_line(t_cursor *pos, char *s)
{
	int save_x;
	int bye;

	save_x = (pos->x > pos->end[pos->y + 1]) ? pos->end[pos->y + 1] : pos->x;
	bye = 0;
	while (s[pos->index])
	{
		if (s[pos->index] < 0 && ft_next_tab(pos, s, save_x, &bye))
			break ;
		if (s[pos->index] > 0)
		{
			if (pos->x == pos->end[pos->y] && !bye)
			{
				bye = 1;
				pos->x = 0;
				pos->y++;
			}
			else if (pos->x == save_x && bye)
				break ;
			else
				pos->x++;
		}
		pos->index++;
	}
}*/

/*int		ft_prev_tab(t_cursor *pos, char *s, int save_x, int *bye)
{
	int sp;

	sp = s[pos->index] * -1;
	if (pos->x - sp <= save_x && *bye)
	{
		if (pos->x - sp == save_x || pos->x - sp == pos->p)
			pos->x -= sp;
		else
			pos->x -= sp - 1;
		if (pos->y == 0 && pos->x < pos->p)
			pos->x = pos->p;
		return (1);
	}
	else if ((pos->x == 0 || pos->x - sp < 0) && !*bye)
	{
		*bye = 1;
		pos->y--;
		pos->x = pos->end[pos->y];
	}
	else
	{
		pos->x -= sp;
		(pos->y == 0 && pos->x < pos->p) ? pos->x = pos->p : 0;
	}
	return (0);
}

void	ft_prev_line(t_cursor *pos, char *s)
{
	int save_x;
	int bye;
	int bl;

	save_x = (pos->x > pos->end[pos->y - 1]) ? pos->end[pos->y - 1] : pos->x;
	bye = 0;
	bl = (s[pos->index++] == '\0') ? 1 : 0;
	while (--pos->index >= 0)
	{
		if (s[pos->index] < 0 && ft_prev_tab(pos, s, save_x, &bye))
			break ;
		if (s[pos->index] <= 0)
			continue ;
		if (pos->x == save_x && bye)
			break ;
		if (pos->x == 0 && !bye)
		{
			bye = 1;
			pos->y--;
			pos->x = pos->end[pos->y];
		}
		else
			pos->x--;
	}
	(pos->index == -1 || bl) ? pos->index++ : 0;
}*/

/*
** -function move the cursor to the next line when we press
** ALT down or the last when we press ALT Up.
*/


void	convert_to_z(char **s)
{
	int i;

	if (!s || !*s)
		return ;
	i = -1;
	while (s[0][++i])
	{
		if (s[0][i] < 0)
			s[0][i] = 'z';
	}
}

void	ft_next_line(t_cursor *pos, char *s)
{
	int sv;
	int cpt;
	int bye;
	int fd = open("/dev/ttys001", O_WRONLY);
	char *line;
	
	if (pos->x > pos->end[pos->y + 1])
		sv = pos->end[pos->y + 1];
	else
		sv = pos->x;
	bye = 0;
	while (s[pos->index])
	{
		if (s[pos->index] < 0)
		{
			cpt = s[pos->index] * -1;
			if (pos->x == sv && bye)
			{
				line = ft_strdup(s + pos->index);
				convert_to_z(&line);
				dprintf(fd, "|%s|\n", line);
				//pos->index++;
				break;
			}
			if (pos->x + cpt > sv && bye)
			{
				line = ft_strdup(s + pos->index);
				convert_to_z(&line);
				dprintf(fd, "|%s|\n", line);
				//pos->index++;
				break ;
			}
			if (pos->x + cpt > pos->end[pos->y])
			{
				pos->x = 0;
				pos->y++;
				bye = 1;
			}
			else
				pos->x += cpt;
		}
		else
		{
			if (pos->x == sv && bye)
			{
				line = ft_strdup(s + pos->index);
				convert_to_z(&line);
				dprintf(fd, "|%s|\n", line);
				break ;
			}
			if (pos->x == pos->end[pos->y] && !bye)
			{
				bye = 1;
				pos->x = 0;
				pos->y++;
			}
			else
				pos->x++;
		}
		pos->index++;
	}
}


void	ft_prev_line(t_cursor *pos, char *s)
{
	int sv;
	int cpt;
	int bye;
	int fd = open("/dev/ttys001", O_WRONLY);
	//char *line;

	if (pos->x > pos->end[pos->y - 1])
		sv = pos->end[pos->y - 1];
	else if (pos->y - 1 == 0 && pos->x < pos->p)
	{
		sv = pos->p;
	}
	else
		sv = pos->x;
	bye = 0;
	cpt = 0;
	while (pos->index >= 0)
	{
		dprintf(fd, "index: %d|X: %d|Y: %d|SV :%d|CPT %d\n", pos->index, pos->x, pos->y, sv, cpt);
		if (s[pos->index] < 0)
		{
			cpt = s[pos->index] * -1;
			if (pos->x <= sv && bye)
			{
				break ;
			}
			//if (pos->x - cpt < 0)

			if (pos->x == 0 && !bye)
			{
				bye = 1;
				pos->y--;
				pos->x = pos->end[pos->y];
				//pos->index--;
			}
			else
				pos->x -= cpt;
		}
		else
		{
			if (pos->x <= sv && bye)
			{
				//ft_putnbr_fd(pos->index, fd);
				break ;
			}
			if (pos->x == 0 && !bye)
			{
				ft_putendl_fd("hello", fd);
				bye = 1;
				pos->y--;
				pos->x = pos->end[pos->y];
			}
			else
				pos->x--;
		}
		pos->index--;
	}
	(pos->index == -1) && (pos->index = 0);
	//ft_putnbr_fd(pos->index, fd);
}



void	move_line(int x, int dir)
{
	if (dir)
		tputs(tgetstr("do", NULL), 0, my_outc);
	else
		tputs(tgetstr("up", NULL), 0, my_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, x), 0, my_outc);
}

void	ft_move_by_lines(t_cursor *pos, char *s, char *buf)
{
	int num_col;
	int num_lines;

	num_col = ft_get_size_windz();
	ft_get_end_of_line_pos(pos, s, num_col);
	num_lines = ft_get_num_of_lines(num_col, s, pos->p);
	
	if (ALT_DO == CAST(buf) && pos->y < num_lines - 1)
	{
		/*tputs(tgetstr("cd", NULL), 0, my_outc);
		ft_putstr_term(num_col, s + pos->index, pos);*/
		ft_next_line(pos, s);
		move_line(pos->x, 1);
	}
	if (ALT_UP == CAST(buf) && pos->y > 0)
	{
		/*tputs(tgetstr("cd", NULL), 0, my_outc);
		ft_putstr_term(num_col, s + pos->index, pos);*/
		ft_prev_line(pos, s);
		//int fd = open("/dev/ttys001", O_WRONLY);
		//ft_putnbr_fd(pos->index, fd);
		move_line(pos->x, 0);
	}
}
