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

/*
**	correction map by remove matched Quoting, sub-shell ,
**		or (Dquote, sub-shell) inside quote.
*/

static int	correct_maps(char *maps)
{
	int i;
	int rtn;
	int temp;

	i = -1;
	rtn = 0;
	if (!maps || !(*maps))
		return (0);
	while (maps[++i] > 0)
	{
		temp = correct_maps_(i, &rtn, maps);
		while (temp-- > 0 && ++rtn)
			maps[++i] = -1;
	}
	return (rtn);
}

/*
** Fill maps with symbole : q -> quote, Q -> Dquote, S -> sub-shell
*/

void		fill_maps(char *str_cmd, char **maps, int j, int len_map)
{
	int i;
	int quoted;

	if (!str_cmd || !maps || !*maps)
		return ;
	i = 0;
	quoted = 0;
	while (str_cmd[i])
	{
		if (j >= (len_map - 1) && (len_map = increase_maps(maps)) == -1)
			break ;
		if (str_cmd[i] == '\\' && (str_cmd[i + 1] != '\'' || quoted == 0 || !j))
			i += (str_cmd[i + 1]) ? 1 : 0;
		else if (str_cmd[i] == '"')
			(*maps)[j++] = 'Q';
		else if (str_cmd[i] == '\'' && ((*maps)[j++] = 'q'))
			quoted = (quoted) ? 0 : 1;
		else if (M_SUBSH(str_cmd[i]) && str_cmd[i + 1] == '(' && ++i)
			(*maps)[j++] = 'S';
		else if (str_cmd[i] == ')')
			(*maps)[j++] = 's';
		i += (str_cmd[i] != '\0');
	}
	while (correct_maps(*maps))
		clean_maps(*maps);
}

void		ft_read_subsh(char **line, t_select *select, t_history *his)
{
	if (!line || !(*line))
		return ;
	*line = ft_strjoir(*line, "\n", 1);
	ft_putstr("sub> ");
	ft_read_line(his, select, 5);
	if (g_pos.cmd)
	{
		*line = ft_strjoir(*line, g_pos.cmd, 3);
		g_pos.cmd = NULL;
	}
}

void		ft_read_quote(char **line, int quote,
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
	{
		*line = ft_strjoir(*line, g_pos.cmd, 3);
		g_pos.cmd = NULL;
	}
}

char		*completing_line(char *str_cmds, t_select *select,\
t_history *his)
{
	char	*maps;
	char	*cmd;

	if (!(maps = ft_strnew(MAX_MAPS)))
		return (str_cmds);
	cmd = ft_strdup(str_cmds);
	ft_strdel(&g_pos.cmd);
	fill_maps(cmd, &maps, 0, MAX_MAPS);
	completing_line_(&maps, &cmd, select, his);
	free(maps);
	return (cmd);
}
