/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 00:57:34 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/08/04 00:57:35 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

char	*ft_remove_strinstr(char *s, int start, int end)
{
	char	*new;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(s);
	if (!(new = ft_memalloc(sizeof(char) * (len - (end - start + 1) + 2))))
		return (NULL);
	ft_bzero(new, len - (end - start + 1) + 2);
	i = -1;
	while (++i < start && s[i])
		new[i] = s[i];
	j = end + 1;
	while (j < len)
		new[i++] = s[j++];
	new[i] = '\0';
	free(s);
	return (new);
}

void	ft_cut_complete(t_cursor *pos, t_select *select, char **s)
{
	int len_sa;

	len_sa = ft_strlen(select->save);
	tputs(tgetstr("cd", NULL), 0, my_outc);
	*s = ft_remove_strinstr(*s, select->start, select->end);
	ft_putstr_term(pos->num_col, *s + pos->index, pos);
}

/*
** - function cut a string from our line and set the cursor in the right
** position after modify.
*/

void	ft_cut(t_cursor *pos, t_select *select, char **s)
{
	ft_get_save(*s, select, pos);
	ft_cut_complete(pos, select, s);
	ft_get_end_of_line_pos(pos, *s, pos->num_col);
	pos->num_lines = ft_get_num_of_lines(pos->num_col, *s, pos->p);
	ft_set_last_position(*pos, pos->num_lines);
}
