/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_complition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 21:45:50 by onouaman          #+#    #+#             */
/*   Updated: 2019/10/12 17:54:10 by mfetoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

int			get_last_flag(int *maps)
{
	int i;

	if (!maps)
		return (0);
	i = 0;
	while (maps[i])
		i++;
	return (i - 1);
}

int			find_flag(int *maps, int flag)
{
	int index;

	index = 0;
	if (!maps || !*maps)
		return (-1);
	while (*maps)
	{
		if (*maps == flag)
			return (index);
		index++;
		maps++;
	}
	return (-1);
}

void		clean_maps(int *maps)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!maps || find_flag(maps, -1) == -1)
		return ;
	while (maps[i])
	{
		if (maps[i] != -1)
			maps[j++] = maps[i];
		i++;
	}
	ft_bzero(&maps[j], 1000 - j - 1);
}

int			count_key(int *maps, int key)
{
	int i;

	i = 0;
	if (!maps || !*maps)
		return (0);
	while (maps[i] == key)
		i++;
	return (i);
}

int			closed_dquot(int *maps)
{
	int i;

	if (!maps)
		return (-1);
	i = 0;
	while (maps[i])
	{
		if (maps[i] == 'S')
			return (-1);
		else if (maps[i] == 'Q')
			return (i);
		i++;
	}
	return (0);
}

int			correct_maps(int *maps)
{
	int i;
	int quoted[2];
	int rtn;
	int temp;

	i = -1;
	rtn = 0;
	ft_bzero(quoted, sizeof(int) * 2);
	while (maps[++i] > 0)
	{
		temp = 0;
		if (MATCH_CLOSED(maps[i], maps[i + 1]) && ++rtn)
			bchar(&maps[i], sizeof(int) * 2, -1);
		else if (maps[i] == 'Q')
		{
			if (!quoted[1])
			{
				temp = count_key(&maps[i + 1], 'q');
				temp = (temp == 0) ? closed_dquot(&maps[i + 1]) : temp;
			}
			quoted[1] = (quoted[1]) ? 0 : 1;
		}
		else if (maps[i] == 'q' && !quoted[1])
		{
			if ((temp = find_flag(&maps[i + 1], 'q')) == -1)
				temp = (!quoted[0]) ? get_last_flag(&maps[i]) : temp;
			quoted[0] = (quoted[0]) ? 0 : 1;
		}
		else if (maps[i] == 'S')
			ft_bzero(quoted, sizeof(int) * 2);
		while (temp-- > 0 && ++rtn)
			maps[++i] = -1;
	}
	return (rtn);
}

void		fill_maps(char *str_cmd, int *maps, int j)
{
	int i;
	int quoted;

	if (!str_cmd || !maps)
		return ;
	i = 0;
	quoted = 0;
	while (str_cmd[i])
	{
		if (str_cmd[i] == '\\' &&
			(str_cmd[i + 1] != '\'' || quoted == 0 || !j))/*|| (j && maps[j - 1] != 'q')))*/
		{
			i += (str_cmd[i + 1]) ? 1 : 0;
		}
		else if (str_cmd[i] == '"')
			maps[j++] = 'Q';
		else if (str_cmd[i] == '\'')
		{
			quoted = (quoted) ? 0 : 1;
			maps[j++] = 'q';
		}
		else if (M_SUBSH(str_cmd[i]) && str_cmd[++i] == '(')
			maps[j++] = 'S';
		else if (str_cmd[i] == ')')
			maps[j++] = 's';
		i += (str_cmd[i] != '\0');
	}
	while (correct_maps(maps))
		clean_maps(maps);
}

static void	ft_read_subsh(char **line, t_select *select, t_history *his)
{
	if (!line || !(*line))
		return ;
	*line = ft_strjoir(*line, "\n", 1);
	ft_putstr("sub> ");
	ft_read_line(his, select, 5);
	if (g_pos.cmd)
		*line = ft_strjoir(*line, g_pos.cmd, 3);
}

static void	ft_read_quote(char **line, int quote,
	t_select *select, t_history *his)
{
	if (!line || !(*line))
		return ;
	*line = ft_strjoir(*line, "\n", 1);
	if (quote == '\'')
	{
		ft_putstr("quote> ");
		ft_read_line(his, select, 7);
	}
	else if (quote == '"')
	{
		ft_putstr("dquotes>> ");
		ft_read_line(his, select, 10);
	}
	if (!g_pos.exit && g_pos.cmd)
		*line = ft_strjoir(*line, g_pos.cmd, 3);
}

void		compliting_line(char **str_cmds, t_select *select, t_history *his)
{
	int	*maps;
	int	i;
	int	index;

	if (!(maps = (int *)malloc(sizeof(int) * MAX_MAPS)))
		return ;
	ft_bzero(maps, MAX_MAPS);
	fill_maps(*str_cmds, maps, 0);
	i = get_last_flag(maps);
	while (i >= 0 && !g_pos.exit)
	{
		if (maps[i] == 'Q' || maps[i] == 'q' || maps[i] == 'S')
		{
			index = ft_strlen(*str_cmds);
			if (maps[i] == 'S')
				ft_read_subsh(str_cmds, select, his);
			else
				ft_read_quote(str_cmds, (maps[i] == 'Q') ? '"' : '\'', select, his);
			fill_maps(&(*str_cmds)[index], maps, i + 1);
			i = get_last_flag(maps);
			continue ;
		}
		i--;
	}
	free(maps);
}
