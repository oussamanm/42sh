/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_by_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 21:36:54 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/03/07 16:51:15 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	ft_get_new_pos_r(t_cursor *pos, int len_move)
{
	while (len_move--)
	{
		if (pos->x == 0)
		{
			pos->y--;
			pos->x = pos->end[pos->y];
		}
		else
			pos->x--;
	}
}

int		ft_len_next_word(t_cursor *pos, char *s)
{
	int i;
	int len;

	i = pos->index;
	len = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\n')
	{
		len++;
		i++;
	}
	while (s[i] && (s[i] == ' ' || s[i] == '\n'))
	{
		len++;
		i++;
	}
	return (len);
}

int		ft_len_last_word(t_cursor *pos, char *s)
{
	int i;
	int len;

	i = pos->index;
	len = 0;
	while (i >= 0 && s[i] != ' ' && s[i] != '\n')
	{
		len++;
		i--;
	}
	while (i >= 0 && (s[i] == ' ' || s[i] == '\n'))
	{
		len++;
		i--;
	}
	while (i >= 0 && s[i] != ' ' && s[i] != '\n')
	{
		len++;
		i--;
	}
	return (len - 1);
}

/*
** -function move the cursor to the next word or to last word.
*/

void	ft_move_by_word(t_cursor *pos, char *s, char *buf)
{
	int num_col;
	int num_lines;
	int len_move;

	num_col = ft_get_size_windz();
	num_lines = ft_get_num_of_lines(num_col, s, pos->p);
	len_move = 0;
	if (RI_WOR == CAST(buf))
	{
		len_move = ft_len_next_word(pos, s);
		tputs(tgetstr("cd", NULL), 0, my_outc);
		ft_putstr_term(num_col, s + pos->index, pos);
		ft_get_new_pos(pos, len_move);
		ft_set_last_position(*pos, num_lines);
		pos->index += len_move;
	}
	if (LE_WOR == CAST(buf))
	{
		len_move = ft_len_last_word(pos, s);
		tputs(tgetstr("cd", NULL), 0, my_outc);
		ft_putstr_term(num_col, s + pos->index, pos);
		ft_get_new_pos_r(pos, len_move);
		ft_set_last_position(*pos, num_lines);
		pos->index -= len_move;
	}
}
