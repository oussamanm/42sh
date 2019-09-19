/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 21:56:04 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/07/18 12:45:48 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

int		ft_check_quot(char *str)
{
	int i;
	int temp;
	int quote;

	i = 0;
	quote = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		if (str[i] == quote)
		{
			if ((temp = ft_find_char(&str[i + 1], quote)) != -1)
			{
				i += (temp + 1);
				quote = 0;
			}
			else
				return (quote);
		}
		i++;
	}
	return (0);
}

void	ft_quotes(char **line, t_select *select, t_history *his)
{
	int		q;

	if ((q = ft_check_quot(*line)) == 0)
		return ;
	while (1337)
	{
		*line = ft_strjoir(*line, "\n", 1);
		if (q == '\'')
		{
			ft_putstr("quote> ");
			ft_read_line(his, select, 7);
		}
		else if (q == '"')
		{
			ft_putstr("dquotes>> ");
			ft_read_line(his, select, 10);
		}
		(!(g_pos.exit) && g_pos.cmd) ? *line = ft_strjoir(*line, g_pos.cmd, 1) : 0;
		if ((g_pos.cmd != NULL && (((q = ft_check_quot(*line)) == 0)
		|| g_pos.cmd[0] == -1)) || g_pos.exit)
			break ;
	}
}
