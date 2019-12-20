/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:21:54 by aboukhri          #+#    #+#             */
/*   Updated: 2019/12/19 19:54:15 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

/*
**	get the value of history index given with their completion
*/

static	char	*history_expansion_value(t_history his, char *str, int index)
{
	t_info	*last;
	char	*plus;
	char	*value;

	last = (his.len - index < index - 1) ? his.tail : his.head;
	if (!(last = history_index(last, index, his.len)))
		return (NULL);
	value = ft_strdup(last->cmd);
	if ((plus = str_notnumber(str)))
		value = ft_strjoir(value, plus, 1);
	return (value);
}

/*
**	get expansions one by one and return false if no expansion left
*/

static	int		get_next_expansion(char *cmd, char **exp, int *i)
{
	int	bg;
	int	q;
	int s;

	s = 0;
	q = 0;
	bg = *i;
	if (!cmd[*i])
		return (0);
	while (cmd[*i])
	{
		if (cmd[*i] == '\'')
			q = (!q) ? 1 : 0;
		if (cmd[*i + 1] == '!' && (cmd[*i] == '\\'
		|| (cmd[*i] == '!' && *i == bg)) && (*i += 2))
			continue ;
		if (cmd[*i] == '!' && !q && !s && *i > bg)
			break ;
		(cmd[*i] == '!' && ft_isalpha(cmd[*i + 1])) && (s = 1);
		(is_shell_delimiter(cmd[*i]) || ft_isspace(cmd[*i])) && (s = 0);
		*i += 1;
	}
	*exp = ft_strsub(cmd, bg, *i - bg);
	return (1);
}

static	char	*command_expansion(t_history his, char *exp)
{
	int		index;
	t_info	*res;

	if (!exp || !his.head || !his.tail)
		return (NULL);
	if (exp[0] == '!' && his.tail)
		return (ft_strjoin(his.tail->cmd, exp + 1));
	else if (ft_isdigit(exp[0]))
		return (history_expansion_value(his, exp, ft_atoi(exp)));
	else if (exp[0] == '-' && ft_isdigit(exp[1]))
	{
		index = his.len + 1 - ft_atoi(exp + 1);
		return (history_expansion_value(his, exp + 1, index));
	}
	else if (exp[0] && ft_isprint(exp[0]) &&
			(res = history_keyword(his.tail, exp, 0)))
		return (ft_strdup(res->cmd));
	return (NULL);
}

/*
**	get history cmds by ! expansion keyword
*/

static	char	*parse_expansion(t_history his, char *s, char **cmd)
{
	char	*exp;
	int		i;
	char	*str;

	if (s[0] == '!' && is_shell_delimiter(s[1]))
	{
		ft_strdel(cmd);
		return (ft_strdup("!"));
	}
	else if (s[0] != '!' || ft_isspace(s[1]) || !s[1])
		*cmd = ft_strjoir(*cmd, s, 1);
	else if (s[0] == '!')
	{
		i = 0;
		exp = shift_expansion(s, &i);
		if (!(str = command_expansion(his, exp + 1)))
		{
			ft_strdel(cmd);
			return (exp);
		}
		*cmd = ft_strjoir(*cmd, str, 3);
		(i < (int)ft_strlen(s)) && (*cmd = ft_strjoir_rtn(*cmd, s + i, 1));
		ft_strdel(&exp);
	}
	return (NULL);
}

char			*history_expansion(t_history his, char *keyword)
{
	char	*split;
	char	*err;
	char	*cmd;
	int		i;

	cmd = ft_strnew(1);
	split = NULL;
	err = NULL;
	i = 0;
	while (get_next_expansion(keyword, &split, &i))
	{
		err = parse_expansion(his, split, &cmd);
		ft_strdel(&split);
		if (err)
			break ;
	}
	if (!cmd)
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(err, 2);
		ft_putendl_fd(": event not found", 2);
		history_readline(&g_history, 0, NULL);
	}
	ft_strdel(&err);
	return (cmd);
}
