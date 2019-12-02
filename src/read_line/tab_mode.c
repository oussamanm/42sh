/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:16:46 by aboukhri          #+#    #+#             */
/*   Updated: 2019/12/01 18:59:48 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	convert_neg_to_tab(char **s)
{
	int i;

	if (!s || !*s)
		return ;
	i = -1;
	while (s[0][++i])
	{
		if (s[0][i] < 0)
			s[0][i] = '\t';
	}
}

void	convert_tab_to_neg(char **s)
{
	int i;

	if (!s || !*s)
		return ;
	i = -1;
	while (s[0][++i])
	{
		if (s[0][i] == '\t')
			s[0][i] = -1;
	}
}

void	ft_without_tab(t_cursor *pos, int *x, int *y)
{
	if (*x == pos->end[*y])
	{
		*x = 0;
		*y += 1;
	}
	else
		*x += 1;
}

void	update_tab_str(char **s, t_cursor *pos)
{
	int x;
	int y;
	int i;
	int sp;

	x = pos->p;
	y = 0;
	i = -1;
	while (s[0][++i])
	{
		if (s[0][i] < 0)
		{
			sp = 8 - (x % 8);
			s[0][i] = sp * -1;
			if (x + sp > pos->end[y])
			{
				x = 0;
				y++;
			}
			else
				x += sp;
		}
		else
			ft_without_tab(pos, &x, &y);
	}
}

char	*put_tab(char *s, t_cursor *pos)
{
	char	*new;
	int		spaces;

	spaces = 8 - (pos->x % 8);
	if (!(new = ft_memalloc(sizeof(char) * ft_strlen(s) + 2)))
		return (NULL);
	ft_strncpy(new, s, pos->index);
	new[pos->index] = spaces * -1;
	ft_strcpy(new + pos->index + 1, s + pos->index);
	tputs(tgetstr("cd", NULL), 0, my_outc);
	ft_putstr_term(pos->num_col, new + pos->index, pos);
	pos->index++;
	pos->num_lines = ft_get_num_of_lines(pos->num_col, new, pos->p);
	if (pos->x + spaces > pos->num_col - 1)
	{
		pos->end[pos->y] = pos->x;
		pos->x = 0;
		pos->y++;
	}
	else
		pos->x += spaces;
	ft_get_end_of_line_pos(pos, new, pos->num_col);
	ft_set_last_position(*pos, pos->num_lines);
	free(s);
	return (new);
}
