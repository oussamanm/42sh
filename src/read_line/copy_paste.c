/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 21:21:36 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/05/10 21:21:38 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

/*
** - function get save of the selection line when we tap COPY or CUT key.
*/

void	ft_get_save(char *s, t_select *select)
{
	int start;
	int end;

	if (select->end >= select->start)
	{
		start = select->start;
		end = select->end;
	}
	else
	{
		start = select->end;
		end = select->start;
	}
	ft_strdel(&select->save);
	select->save = ft_strsub(s, start, end - start + 1);
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

/*
** - function get save from our line when select an element.
** - call funtion ft_cut when we need it.
** - paste string in our line and displat it and move the cursor in the
** position.
*/

void	ft_copy_paste(char *buf, char **s, t_cursor *pos, t_select *select)
{
	int len;
	int len_sa;

	len = ft_strlen(*s);
	if (COPY == CAST(buf) && select->start != -1 && select->end != -1)
		ft_get_save(*s, select);
	if (CUT == CAST(buf) && select->start != -1 && select->end != -1)
		ft_cut(pos, select, s);
	if (PASTE == CAST(buf) && select->save)
	{
		len_sa = ft_strlen(select->save);
		*s = ft_paste_in_str(*s, select, pos->index);
		tputs(tgetstr("cd", NULL), 0, my_outc);
		ft_putstr_term(pos->num_col, *s + pos->index, pos);
		ft_get_end_of_line_pos(pos, *s, pos->num_col);
		pos->index += len_sa;
		ft_get_new_pos(pos, len_sa);
		pos->num_lines = ft_get_num_of_lines(pos->num_col, *s, pos->p);
		ft_set_last_position(*pos, pos->num_lines);
	}
	select->start = -1;
	select->end = -1;
}
