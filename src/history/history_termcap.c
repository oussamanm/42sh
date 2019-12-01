/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_termcap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 18:48:28 by aboukhri          #+#    #+#             */
/*   Updated: 2019/12/01 11:38:28 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"

/*
**	move cursor down (number) of times given
*/

void			his_cursor_do(int nbr)
{
	while (nbr-- > 0)
		tputs(tgetstr("do", NULL), 0, my_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, my_outc);
}

/*
**	move cursor up (number) of times given
*/

void			his_cursor_up(t_cursor pos, int nbr)
{
	while (nbr-- > 0)
		tputs(tgetstr("up", NULL), 0, my_outc);
	tputs(tgoto(tgetstr("ch", NULL), 0, pos.p), 0, my_outc);
}

static	void	put_serach_term(char *str, int index, int end, int *x)
{
	if (index < end)
		tputs(tgetstr("us", NULL), 0, my_outc);
	else if (end == -1)
		tputs(tgetstr("ue", NULL), 0, my_outc);
	ft_putchar(str[index]);
	if (*x == g_pos.num_col - 1 || str[index] == '\n')
	{
		if (*x == g_pos.num_col - 1 && str[index] != '\n')
			tputs(tgetstr("do", NULL), 0, my_outc);
		*x = 0;
	}
	else
		*x += 1;
}

/*
**	put line and underline the search string in the line
*/

void			his_putstr_term(int num_col, char *s,
								char *search, t_cursor *pos)
{
	int	i;
	int	x;
	int	end;
	int	len;

	if (!search)
		return ;
	i = -1;
	x = pos->x;
	end = 0;
	len = ft_strlen(search);
	while (s[++i])
	{
		if (end == 0 && ft_strncmp(s + i, search, len) == 0)
			end = i + len;
		if (end > 0 && i >= end)
			end = -1;
		if (s[i] < 0)
			print_tab(num_col, &x);
		else
			put_serach_term(s, i, end, &x);
	}
	tputs(tgetstr("ue", NULL), 0, my_outc);
}
