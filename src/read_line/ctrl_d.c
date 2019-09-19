/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 17:14:32 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/07/17 17:14:33 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	ft_free_tab(char **tableau)
{
	int i;

	if (!tableau)
		return ;
	i = 0;
	while (tableau[i])
		free(tableau[i++]);
	free(tableau);
}

/*
** - function free all elements of the read line function need when we quit
** from our shell.
*/

int		ft_read_exit(t_cursor *pos, t_history *his, t_select *select, char **s)
{
	if (g_pos.p == 9 || g_pos.p == 10)
	{
		(*s)[0] = -1;
		return (-1);
	}
	if (pos->end)
		free(pos->end);
	if (pos->cmd)
		free(pos->cmd);
	if (select->save)
		free(select->save);
	if (his->history)
		ft_free_tab(his->history);
	ft_disable();
	exit(0);
	return (1);
}

/*
** - function exit from our shell when we have empty line.
** - else the function remove a character from the index of our cursor.
** - return the new line.
*/

char	*ft_ctrl_d(t_cursor *pos, t_history *his, t_select *select, char *s)
{
	char	*new;
	int		len;

	if (!ft_strcmp(s, ""))
		if (ft_read_exit(pos, his, select, &s) == -1)
			return (s);
	len = ft_strlen(s);
	if (pos->index < len && pos->index >= 0)
	{
		tputs(tgetstr("cd", NULL), 0, my_outc);
		if (!(new = ft_memalloc(sizeof(char) * len)))
			return (NULL);
		ft_strncpy(new, s, pos->index);
		ft_strcpy(new + pos->index, s + pos->index + 1);
		ft_putstr_term(pos->num_col, new + pos->index, pos);
		pos->num_lines = ft_get_num_of_lines(pos->num_col, new, pos->p);
		ft_get_end_of_line_pos(pos, new, pos->num_col);
		ft_set_last_position(*pos, pos->num_lines);
	}
	else
		return (s);
	free(s);
	return (new);
}
