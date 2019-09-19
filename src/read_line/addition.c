/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:51:04 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/07/07 14:51:06 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

/*
** - function add the character c in the line ( s )
** - dispaly the new char in our shell and set new position of our cursor
** - put the cursor in the right position
*/

char	*ft_line_add(char *s, t_cursor *pos, char c)
{
	char *new;

	if (!(new = ft_memalloc(sizeof(char) * ft_strlen(s) + 2)))
		return (NULL);
	ft_strncpy(new, s, pos->index);
	new[pos->index] = c;
	ft_strcpy(new + pos->index + 1, s + pos->index);
	tputs(tgetstr("cd", NULL), 0, my_outc);
	ft_putstr_term(pos->num_col, new + pos->index, pos);
	pos->index++;
	pos->num_lines = ft_get_num_of_lines(pos->num_col, new, pos->p);
	if (pos->x == pos->num_col - 1)
	{
		pos->x = 0;
		pos->y++;
	}
	else
		pos->x++;
	ft_get_end_of_line_pos(pos, new, pos->num_col);
	ft_set_last_position(*pos, pos->num_lines);
	free(s);
	return (new);
}

char	*ft_inside_line(char *s, t_cursor *pos, char *buf)
{
	int i;

	i = 0;
	while ((ft_isprint(buf[i]) || buf[i] == '\n') && i < 6)
		if (!(s = ft_line_add(s, pos, buf[i++])))
			return (NULL);
	return (s);
}
