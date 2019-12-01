/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 21:21:36 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/12/01 17:33:26 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

/*
** - function get save of the selection line when we tap COPY or CUT key.
*/

void	ft_get_save(char *s, t_select *select, t_cursor *pos)
{
	select->start = pos->index;
	select->end = ft_strlen(s) - 1;
	ft_strdel(&select->save);
	select->save = ft_strsub(s, pos->index, ft_strlen(s));
}

/*
** function remove the selection :
** - first move the cursor in the index 0 and clear from the cursor position.
** - display our line without reverse video.
** - set our cursor in the right position.
*/

void	ft_remove_selection(t_cursor *pos, char *s)
{
	int x_save;

	x_save = pos->x;
	ft_move_cursor_zero(*pos);
	tputs(tgetstr("cd", NULL), 0, my_outc);
	ft_putstr(s);
	pos->x = x_save;
	ft_set_last_position(*pos, pos->num_lines);
}

/*
** - function add string inside our line start from the index geven
** in parameters
*/

char	*ft_paste_in_str(char *s, t_select *select, int index)
{
	int		i;
	int		j;
	int		len;
	char	*fr;

	i = 0;
	j = 0;
	len = ft_strlen(s) + ft_strlen(select->save);
	fr = ft_strnew(len + 1);
	while (i < index)
	{
		fr[i] = s[i];
		i++;
	}
	while (select->save[j])
		fr[i++] = select->save[j++];
	while (i < len)
		fr[i++] = s[index++];
	fr[i] = '\0';
	free(s);
	return (fr);
}

/*
** - save the next position of the cursor when we add a string in our line.
*/

void	ft_get_new_pos(t_cursor *pos, int len_sa)
{
	while (len_sa--)
	{
		if (pos->x == pos->end[pos->y])
		{
			pos->y++;
			pos->x = 0;
		}
		else
			pos->x++;
	}
}

void	new_pos_tab(char *s, int len, t_cursor *pos)
{
	int sp;
	int i;

	i = -1;
	while (s[++i] && i < len)
	{
		if (s[i] < 0)
		{
			sp = s[i] * -1;
			if (pos->x + sp > pos->end[pos->y])
			{
				pos->y++;
				pos->x = 0;
			}
			else
				pos->x += sp;
		}
		else
		{
			if (pos->x == pos->end[pos->y])
			{
				pos->y++;
				pos->x = 0;
			}
			else
				pos->x++;
		}
	}
}

/*
** - function get save from our line when select an element.
** - call funtion ft_cut when we need it.
** - paste string in our line and displat it and move the cursor in the
** position.
*/


void	tab_set_last_position(t_cursor pos, int num_lines)
{
	int y;
	//int real_pos;

	y = num_lines - 1;
	//real_pos = pos.p;
	while (pos.y < y--)
		tputs(tgetstr("up", NULL), 0, my_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, pos.x), 0, my_outc);
	/*if (real_pos > pos.x)
		while (real_pos-- > pos.x)
			tputs(tgetstr("le", NULL), 0, my_outc);
	else if (real_pos < pos.x)
		while (real_pos++ < pos.x)
			tputs(tgetstr("nd", NULL), 0, my_outc);*/
}

void	ft_copy_paste(char *buf, char **s, t_cursor *pos, t_select *select)
{
	int len;
	int len_sa;
	//int index;

	len = ft_strlen(*s);
	if (COPY == CAST(buf))
		ft_get_save(*s, select, pos);
	if (CUT == CAST(buf))
		ft_cut(pos, select, s);
	if (PASTE == CAST(buf) && select->save)
	{
		len_sa = ft_strlen(select->save);
		*s = ft_paste_in_str(*s, select, pos->index);
		tputs(tgetstr("cd", NULL), 0, my_outc);
		ft_putstr_term(pos->num_col, *s + pos->index, pos);
		ft_get_end_of_line_pos(pos, *s, pos->num_col);
		pos->num_lines = ft_get_num_of_lines(pos->num_col, *s, pos->p);
		update_tab_str(s, pos);
		new_pos_tab(*s + pos->index, len_sa, pos);
		pos->index += len_sa;
		tab_set_last_position(*pos, pos->num_lines);
		
	}
}
